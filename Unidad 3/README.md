# Unidad 3 Protocolos Binarios

## **Introducción**

En esta unidad seguiremos profundizando en la integración de dispositivos periféricos a las aplicaciones interactivas, pero esta vez, usando protocolos binarios.

## **Propósitos de aprendizaje**

Integrar aplicaciones interactivas y periféricos utilizando protocolos seriales binarios.

## **Trayecto de actividades**

### **Ejercicio 1: introducción a los protocolos binarios - caso de estudio**

¿Cómo se ve un protocolo binario? Para explorar este concepto te voy a mostrar una hoja de datos de un [sensor](http://www.chafon.com/) comercial que usa un protocolo de comunicación binario. 

![wall-mounted-uhf-rfid-fixed-reader-500x500 jpg](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/f187f79d-406f-4afb-8880-ea5a42fec268)

La idea es que tu explores su hoja de datos ([datasheet](https://drive.google.com/file/d/1uDtgNkUCknkj3iTkykwhthjLoTGJCcea/view?pli=1)), tanto como sea posible, invitándote a que observes con detenimiento hasta la página 5.

el documento hoja de datos que se menciona tiene el siguiente contenido hasta la pagina 5:

**UHF RFID Reader UHFReader18 User's Manual V2.0**

1. COMMUNICATION INTERFACE SPECIFICATION

The reader communicates with host (MCU，MPU，Controller) using serial communication interface RS232 or RS485 and complete corresponding operation according to the host command. The communication parameter is 57600bps 1 start bit, 8 data bits, 1 stop bit without parity check bit. In the process of serial communication, the least significant bit of one byte is transmitted first and the least significant byte of command data sequence is transmitted first.

2. PROTOCOL DESCRIPTION

A communication procedure is sponsored by the host sending commands and data to the reader and the reader returns the result status and data to host after command execution.
Reader receives a command executes a command, only the reader complete the implementation of a command, to receive the next command. During the implementation of the command in the reader, if sending commands to the reader, the command will be lost.
The following table shows the process of the host computer command:

| HOST | DIRECTION | READER |
|:--:|:--:|:--:|
|Command Data Block | → | |

The interval between two consecutive bytes in the command data block should be less than 15ms. During command data block sending, synchronization will lost if the host receives any data from the reader and the host should stop command sending and restart the communication after 15ms.
The reader completes command execution in inventory ScanTime (not including host sending data time)
except inventory command after receiving host command and returns the results. During the period, it doesn’t process any host data. The feedback of command execution results is as follows:

| READER | DIRECTION | READER |
|:--:|:--:|:--:|
|Command Data Block | → | |

The interval between two consecutive bytes in the response data block should be less than 15ms.

5. DATA BLOCK FORMAT

3.1 COMMAND DATA BLOCK

| | | | | | |
|:--:|:--:|:--:|:--:|:--:|:--:|
| Len | Adr | Cmd | Data[] | LSB-CRC16 | MSB-CRC16 |

COMMENT：

| | LENGTH(Byte) |COMMENT |
|:--:|:--:|:--:|
|Len | 1 | Command data block length 1 byte (not including itself). Value range is 4~96. The number of Len equals the length of Data [] plus 4. |
|Adr | 1 | Reader address, 1 byte. Value range is 0~254. Only will the reader conforming to the address response the command data block. Value 255 is broadcasting address. All the readers will response to the command data block with a broadcasting address. The default value shall be zero. |
|Cmd | 1 | Operation command symbol, 1 byte.|
|Data[] | Variable | Operation command parameters. There is no parameter if the LEN item equals 4. |
|LSB-CRC16| 1 |CRC-16 LSB. CRC-16 checksum, 2 bytes with least significant byte first. |
|MSB-CRC16| 1 |CRC-16 MSB.|

3.2 RESPONSE DATA BLOCK

| | | | | | | |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| Len | Adr | reCmd | Status | Data[] | LSB-CRC16 | MSB-CRC16|

COMMENT：

| | LENGTH(Byte) | COMMENT|
|:--:|:--:|:--:|
|Len| 1| Response data block length 1 byte (not including itself). The number of Len equals the length of Data [] plus 5.|
|Adr| 1| Reader address, 1 byte. Value rang is 0~254.|
|reCmd| 1| Response command symbol, 1 byte. If the command is unrecognized, the reCmd is 0x00. |
|Status| 1| Result status value, 1byte. Refer to following table for details.|
|Data[]| Variable | Response data. There is no this item if Len equals 5.|
|LSB-CRC16| 1 |CRC16 LSB .CRC-16 checksum, 2 bytes with least significant byte first. |
|MSB-CRC16| 1 | CRC16 MSB|

The default value of the reader address is 0x00. The host may change it by using reader-defined command “Write Adr”.
Cyclic Redundancy Check (CRC) computation includes all data from Len. A reference CRC computation program is presented as follow:

C-Example:

```c
#define PRESET_VALUE 0xFFFF
#define POLYNOMIAL 0x8408

unsigned int uiCrc16Cal(unsigned char const * pucY, unsigned char ucX)
{
unsigned char ucI,ucJ;
unsigned short int uiCrcValue = PRESET_VALUE;

  for(ucI = 0; ucI &lt; ucX; ucI++)
  {
  uiCrcValue = uiCrcValue ^ *(pucY + ucI);
      for(ucJ = 0; ucJ &lt; 8; ucJ++)
      {
      if(uiCrcValue &amp; 0x0001)
      {
      uiCrcValue = (uiCrcValue &gt;&gt; 1) ^ POLYNOMIAL;
      }
      else
      {
      uiCrcValue = (uiCrcValue &gt;&gt; 1);
      }
    }
  }
  return uiCrcValue;
}
```

Este material se centra en un caso de estudio específico: un lector UHF RFID. los puntos clave de la implementación especifica para este dispositivo puede variar segun el dispositivo, el manual, el fabricante, etc. Para éste especificamente contiene:

1. **Especificación de la interfaz de comunicación**: El lector se comunica con un host (como un microcontrolador o una unidad de procesamiento) utilizando una interfaz de comunicación serie RS232 o RS485. Utiliza una velocidad de comunicación de 57600 bps con una configuración de 1 bit de inicio, 8 bits de datos y 1 bit de parada, sin bits de paridad.

   Las interfaces de comunicación serie RS232 y RS485 son estándares utilizados para la comunicación de datos serie entre dispositivos electrónicos. Aquí te explico cada uno de ellos:

   1.1. **RS232 (Recommended Standard 232)**:
   - Es un estándar de comunicación serie que define la conexión y la señalización entre equipos de datos.
   - Fue ampliamente utilizado en dispositivos informáticos y periféricos, como módems, impresoras, terminales y dispositivos de comunicación serial.
   - Utiliza voltajes diferenciales para representar los bits de datos, control y señales de sincronización.
   - La interfaz RS232 utiliza señales de voltaje positivas y negativas en un rango de -15V a +15V para representar datos.
   - Tiene una distancia de transmisión limitada, generalmente de hasta 15 metros, y requiere cables específicos con conectores DB9 o DB25.

     1.2. **RS485 (Recommended Standard 485)**:
   - Es un estándar de comunicación serie que permite la transmisión de datos en redes de bus multipunto.
   - Se utiliza comúnmente en aplicaciones industriales y de automatización, como sistemas de control de procesos, sistemas de seguridad, sistemas de control de acceso, entre otros.
   - Utiliza voltajes diferenciales para la transmisión de datos, lo que permite una mayor inmunidad al ruido y una mayor distancia de transmisión en comparación con RS232.
   - La interfaz RS485 puede soportar múltiples dispositivos conectados en un bus de comunicación, lo que facilita la comunicación entre varios dispositivos en un entorno industrial.
   - Puede alcanzar distancias de transmisión de hasta varios kilómetros, dependiendo de la velocidad de transmisión y la calidad del cableado.
   - Utiliza conectores de tornillo o bornes de conexión para facilitar la conexión de los dispositivos.

    En resumen, RS232 es un estándar de comunicación serie utilizado principalmente en aplicaciones de corta distancia, mientras que RS485 es más adecuado para aplicaciones de larga distancia y entornos industriales que requieren comunicación multipunto. Ambos estándares son importantes en diferentes contextos y tienen sus propias ventajas y limitaciones.

2. **Descripción del protocolo**: El proceso de comunicación implica que el host envíe comandos y datos al lector, y el lector devuelve el estado del resultado y los datos al host después de ejecutar el comando. La comunicación sigue un formato específico de bloques de datos para comandos y respuestas.

3. **Formato del bloque de datos**:
   - **Bloque de datos del comando**: Contiene información como la longitud, dirección del lector, comando operativo y datos asociados.
   - **Bloque de datos de respuesta**: Similar al bloque de datos del comando, pero también incluye un estado de resultado y datos de respuesta.

4. **Cálculo de la comprobación de redundancia cíclica (CRC)**: Se proporciona un ejemplo en lenguaje C para calcular el CRC-16 de los datos, lo que ayuda a garantizar la integridad de la comunicación.

Durante la lectura, intenta dar respuestas a las siguientes preguntas:
- ¿Cómo se ve un protocolo binario?
- ¿Puedes describir las partes de un mensaje?
- ¿Para qué sirve cada parte del mensaje?

basados en el material del manual del dispositivo. Las partes en el protocolo binario trabajan juntas para facilitar una comunicación confiable entre el host y el lector, asegurando que los comandos se ejecuten correctamente y que las respuestas sean precisas.

1. **¿Cómo se ve un protocolo binario?**
   Un protocolo binario se presenta en forma de bloques de datos estructurados. Cada bloque contiene información específica que se utiliza para la comunicación entre dispositivos. En el caso del lector UHF RFID, el protocolo binario se compone de bloques de datos tanto para comandos enviados desde el host al lector como para respuestas enviadas desde el lector al host.

2. **¿Puedes describir las partes de un mensaje?**
   El mensaje en este contexto se refiere a los bloques de datos que se intercambian entre el host y el lector. Estos bloques de datos tienen varias partes:
   - **Longitud (Len)**: Indica la longitud total del bloque de datos.
   - **Dirección del lector (Adr)**: Especifica la dirección del lector al que se envía el comando o desde el que se recibe la respuesta.
   - **Comando (Cmd o reCmd)**: Representa el comando que se debe ejecutar en el lector o la respuesta del lector al comando recibido.
   - **Datos (Data[])**: Contiene los parámetros o la información asociada al comando enviado o la respuesta recibida.
   - **Checksum CRC-16 (LSB-CRC16 y MSB-CRC16)**: Es un valor de comprobación de redundancia cíclica (CRC) que se utiliza para verificar la integridad de los datos transmitidos.

3. **¿Para qué sirve cada parte del mensaje?**
   - **Longitud**: Indica la cantidad de bytes que componen el bloque de datos.
   - **Dirección del lector**: Permite al lector identificar si el comando se dirige a él o si la respuesta es para el host.
   - **Comando**: Es la instrucción que el lector debe ejecutar o la respuesta que proporciona al comando recibido.
   - **Datos**: Proporciona la información necesaria para ejecutar el comando o devuelve los resultados solicitados.
   - **Checksum CRC-16**: Se utiliza para garantizar que los datos transmitidos no se hayan corrompido durante la comunicación, proporcionando un mecanismo de detección de errores.


**PERO!!** En un contexto general:

1. **¿Cómo se ve un protocolo binario?**
   - Un protocolo binario es un conjunto de reglas y formatos utilizados para la comunicación de datos entre dispositivos electrónicos.
   - Los datos se transmiten en forma de secuencias de bits (0s y 1s) en lugar de caracteres legibles por humanos, como en los protocolos ASCII.
   - Un protocolo binario define la estructura de los mensajes, incluidos los encabezados, los datos y, a veces, los códigos de control de errores.

2. **¿Puedes describir las partes de un mensaje?**
   - Encabezado: Es la parte inicial del mensaje que contiene información sobre la naturaleza y la longitud del mensaje. Puede incluir también información de control, como la dirección del destinatario o el tipo de datos que se envían.
   - Cuerpo de datos: Es la parte central del mensaje que contiene la información real que se está transmitiendo, como valores numéricos, datos de sensor, comandos, etc.
   - Código de comprobación de errores: Opcionalmente, un mensaje binario puede incluir un código de comprobación de errores para detectar errores de transmisión y garantizar la integridad de los datos.

3. **¿Para qué sirve cada parte del mensaje?**
   - Encabezado: Sirve para identificar y controlar el flujo de datos, incluyendo información relevante para la interpretación del mensaje por parte del receptor, como la dirección del destinatario o el tipo de datos que se están enviando.
   - Cuerpo de datos: Contiene la información principal que se está transmitiendo entre los dispositivos, como lecturas de sensores, comandos de control, mensajes de estado, etc.
   - Código de comprobación de errores: Sirve para detectar errores de transmisión que pueden ocurrir durante la comunicación, como errores de transmisión, ruido en la línea, etc. Ayuda a garantizar la integridad de los datos y la fiabilidad de la comunicación.

En resumen, un protocolo binario se compone de un encabezado que proporciona información sobre el mensaje, un cuerpo de datos que contiene la información principal y opcionalmente un código de comprobación de errores para garantizar la integridad de los datos. Cada parte del mensaje cumple una función específica en el proceso de comunicación entre dispositivos electrónicos.


Opcion 1 Ejercicio 4

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/78072cb9-b09c-4bbc-b7d2-5d2861a03d58)
