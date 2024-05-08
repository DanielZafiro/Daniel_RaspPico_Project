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
   - **Encabezado:** Es la parte inicial del mensaje que contiene información sobre la naturaleza y la longitud del mensaje. Puede incluir también información de control, como la dirección del destinatario o el tipo de datos que se envían.
   - **Cuerpo de datos:** Es la parte central del mensaje que contiene la información real que se está transmitiendo, como valores numéricos, datos de sensor, comandos, etc.
   - **Código de comprobación de errores:** Opcionalmente, un mensaje binario puede incluir un código de comprobación de errores para detectar errores de transmisión y garantizar la integridad de los datos.

3. **¿Para qué sirve cada parte del mensaje?**
   - Encabezado: Sirve para identificar y controlar el flujo de datos, incluyendo información relevante para la interpretación del mensaje por parte del receptor, como la dirección del destinatario o el tipo de datos que se están enviando.
   - Cuerpo de datos: Contiene la información principal que se está transmitiendo entre los dispositivos, como lecturas de sensores, comandos de control, mensajes de estado, etc.
   - Código de comprobación de errores: Sirve para detectar errores de transmisión que pueden ocurrir durante la comunicación, como errores de transmisión, ruido en la línea, etc. Ayuda a garantizar la integridad de los datos y la fiabilidad de la comunicación.

En resumen, un protocolo binario se compone de un encabezado que proporciona información sobre el mensaje, un cuerpo de datos que contiene la información principal y opcionalmente un código de comprobación de errores para garantizar la integridad de los datos. Cada parte del mensaje cumple una función específica en el proceso de comunicación entre dispositivos electrónicos.

---

### **Ejercicio 2: experimento**

En [este](https://www.arduino.cc/reference/en/language/functions/communication/serial/) enlace vas a mirar los siguientes métodos. Te pediré que, por favor, los tengas a mano porque te servirán para resolver problemas. Además, en este punto, hagamos un repaso de las funciones que han apoyado la comunicación seral:

> [!TIP]
> 
> `Serial.available()`
>
> `Serial.read()`
> 
> `Serial.readBytes(buffer, length)`
>
> `Serial.write()`

Nótese que la siguiente función no está en la lista de repaso:

> [!WARNING]
> 
> **`Serial.readBytesUntil()`**


¿Sospecha por qué se ha excluido? La razón es porque en un protocolo binario usualmente no tiene un carácter de FIN DE MENSAJE, como si ocurre con los protocolos ASCII, donde usualmente el último carácter es el `\n`.

- `Serial.available()`: Esta función devuelve el número de bytes disponibles para leer en el búfer de entrada.

- `Serial.read()`: Lee el siguiente byte de datos del puerto serie (el primer byte disponible).

- `Serial.readBytes(buffer, length)`: Lee caracteres desde el búfer del puerto serie en un arreglo de bytes hasta que se lee el número especificado de caracteres.

- `Serial.write()`: Envía datos binarios a través del puerto serie.

Y la funcion excluida: La razón es porque en un protocolo binario usualmente no tiene un carácter de FIN DE MENSAJE, como si ocurre con los protocolos ASCII, donde usualmente el último carácter es el `\n`.

- `Serial.readBytesUntil()`: Lee caracteres desde el búfer del puerto serie en un arreglo de bytes hasta que se lee un carácter delimitador o hasta que se alcanza el tamaño máximo del búfer.

---

### Ejercicio 3: **¿Qué es el *endian*?**

Cuando trabajamos con protocolos binarios es necesario transmitir variables que tienen una longitud mayor a un byte. Por ejemplo, los números en punto flotante cumplen con el [estándar IEEE754](https://www.h-schmidt.net/FloatConverter/IEEE754.html) y se representan con 4 bytes.

Algo que debemos decidir al trabajar con números como los anteriormente descritos es el orden en el cual serán transmitidos sus bytes. En principio tenemos dos posibilidades: i) transmitir primero el byte de menor peso (*little endian*) o transmitir primero el byte de mayor peso (*big endian*). Por lo tanto, al diseñar un protocolo binario se debe escoger una de las dos posibilidades.

La presentación trabajada en clase sobre como se determinan los numeros para cumplir las reglas se encuentra a continuación:

[02 Sistemas numéricos_v22_sol.pdf](https://upbeduco-my.sharepoint.com/:b:/g/personal/vera_perez_upb_edu_co/EfFkGLGlfolCneLd-WE-LlwByt-a6iWAQafw40zuGaZC-Q?e=IRCh2t)

En el contexto de la informática y la comunicación de datos, el término "endian" se refiere al orden en el que se almacenan los bytes de datos en la memoria de un sistema computacional. Hay dos formas principales de ordenar los bytes: "big endian" y "little endian".

- **Big Endian**: En este formato, el byte más significativo (el byte de mayor peso) se almacena en la dirección de memoria más baja (el primer byte), mientras que el byte menos significativo (el byte de menor peso) se almacena en la dirección de memoria más alta (el último byte).

- **Little Endian**: En este formato, el byte menos significativo se almacena en la dirección de memoria más baja (el primer byte), mientras que el byte más significativo se almacena en la dirección de memoria más alta (el último byte).

La elección entre big endian y little endian es crucial cuando se trabaja con datos que abarcan múltiples bytes, como números enteros de más de un byte, números en punto flotante, etc. La forma en que se almacenan estos datos determinará cómo se interpretan correctamente cuando se transmiten o se leen en diferentes sistemas.

Por ejemplo, si un sistema envía datos en formato big endian y otro sistema espera recibirlos en formato little endian, los datos pueden interpretarse incorrectamente debido a que los bytes se interpretarán en orden inverso.

Por lo tanto, al diseñar un protocolo binario, es importante especificar explícitamente qué formato endian se utilizará para garantizar la interoperabilidad entre diferentes sistemas.


---

### **Ejercicio 4: transmitir números en punto flotante**

> [!IMPORTANT]  
> 💡 **¡Desempolva ScriptCommunicator!**
>
> Para este ejercicio vas a necesitar una herramienta que te permita ver los bytes que se están transmitiendo sin interpretarlos como caracteres ASCII. Usa **ScriptCommunicator** en los sistemas operativos Windows o Linux y **CoolTerm** en el sistema operativo MacOS (te soporta la arquitectura Mx).

¿Cómo transmitir un número en punto flotante? Veamos dos alternativas:

Opción 1:

- En esta opción, el número en punto flotante `num` se transmite directamente como un puntero a un array de bytes (`uint8_t *`) utilizando `Serial.write()`.
  
- No se utiliza un buffer explícito, sino que se transmite directamente la representación en bytes del número en punto flotante.

```c
void setup() {
    Serial.begin(115200);
}

void loop() {
    // 45 60 55 d5
    // https://www.h-schmidt.net/FloatConverter/IEEE754.html
    static float num = 3589.3645;

    if(Serial.available()){
        if(Serial.read() == 's'){
            Serial.write ( (uint8_t *) &num,4);
        }
    }
}
```


Opción 2. Aquí primero se copia la información que se desea transmitir a un buffer o arreglo:

- Aquí se utiliza un buffer explícito `arr` para almacenar la representación en bytes del número en punto flotante.

- Se copia la representación en bytes del número en punto flotante desde la memoria donde se almacena `num` al buffer `arr` utilizando `memcpy()`.

- Luego, se transmite el contenido del buffer `arr` utilizando `Serial.write()`.

```c
void setup() {
    Serial.begin(115200);
}

void loop() {
// 45 60 55 d5// https://www.h-schmidt.net/FloatConverter/IEEE754.htmlstatic
float num = 3589.3645;
static uint8_t arr[4] = {0};

if(Serial.available()){
if(Serial.read() == 's'){
            memcpy(arr,(uint8_t *)&num,4);
            Serial.write(arr,4);
        }
    }
}
```

La principal diferencia radica en cómo se gestiona la transmisión de los bytes que representan el número en punto flotante: directamente desde la memoria del número (`Opción 1`) o a través de un buffer intermedio (`Opción 2`).

Preguntas:

- ¿En qué *endian* estamos transmitiendo el número?

Ambas opciones no especifican explícitamente el endian en el que se está transmitiendo el número en punto flotante. El endian dependerá del endian nativo del microcontrolador o del sistema en el que se está ejecutando el código.

En la mayoría de los casos, el endian utilizado será el endian nativo del microcontrolador o del sistema. Por ejemplo:

- Si el microcontrolador o sistema utiliza little endian, entonces los bytes se transmitirán en little endian.
- Si el microcontrolador o sistema utiliza big endian, entonces los bytes se transmitirán en big endian.

Para determinar el endian utilizado en tu sistema específico, puedes consultar la documentación del microcontrolador o del sistema, o realizar pruebas prácticas para verificar el orden en el que se transmiten los bytes. Si necesitas que los bytes se transmitan en un endian específico, deberás realizar conversiones explícitas para asegurarte de que se transmitan en el orden correcto. Esto puede ser especialmente importante si estás transmitiendo datos entre sistemas con diferentes endians.

Opcion 1 Ejercicio 4
![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/78072cb9-b09c-4bbc-b7d2-5d2861a03d58)

- La representación hexadecimal de 3589.3645 en el estándar IEEE754 es `45 60 55 d5`.
- Al probar el código de la opción 1, la secuencia de bytes recibida a través de la comunicación serial fue `d5 55 60 45`.

en ambas opciones, la secuencia de bytes recibida sigue siendo `d5 55 60 45`, lo que sugiere que el endian utilizado es **little endian**, ya que los bytes se están transmitiendo en orden inverso al esperado.

Dado que tanto la Opción 1 como la Opción 2 están produciendo el mismo resultado, es probable que el microcontrolador o el sistema en el que estás ejecutando el código utilice little endian por defecto para la transmisión de datos a través de la comunicación serial.

nota: Si se necesita que los bytes se transmitan en big endian, deberiamos realizar una conversión explícita para invertir el orden de los bytes antes de enviarlos a través de la comunicación serial. Por ejemplo, se podría invertir el orden de los bytes en el buffer antes de transmitirlos.

- Y si queremos transmitir en el *endian* contrario, ¿Cómo se modifica el código?

Pausa… A continuación, te dejo una posible solución a la pregunta anterior.

```c
void setup() {
    Serial.begin(115200);
}

void loop() {
    // Número en punto flotante que se desea transmitir
    // 45 60 55 d5
    // https://www.h-schmidt.net/FloatConverter/IEEE754.htmlstatic
    float num = 3589.3645;
    
    // Buffer para almacenar la representación en bytes del número
    static uint8_t arr[4] = {0};

    if (Serial.available()) {
        if (Serial.read() == 's') {
            // Copiar la representación de bytes del número al buffer
            memcpy(arr, (uint8_t *)&num, 4);
            
            // Invertir el orden de los bytes en el buffer antes de transmitirlos
            for (int8_t i = 3; i >= 0; i--) { // Iteramos desde el último byte hasta el primero
                Serial.write(arr[i]); // Transmitimos los bytes en orden inverso (big endian)
            }
        }
    }
}

```

Basados en la Opcion 1 para transmitir en el endian contrario **Inviritiendo el orden de lo bytes antes de transmitirilos**:

```cpp
void setup() {
    Serial.begin(115200);
}

void loop() {
    // 45 60 55 d5
    // https://www.h-schmidt.net/FloatConverter/IEEE754.htmlstatic

    static float num = 3589.3645;

    if (Serial.available()) {
        if (Serial.read() == 's') {
            // Invertir el orden de los bytes antes de transmitirlos
            uint8_t bytes[sizeof(float)]; // Creamos un buffer para almacenar los bytes del número
            memcpy(bytes, (uint8_t *)&num, sizeof(float)); // Copiamos la representación de bytes del número al buffer
            for (int i = 0; i < sizeof(float) / 2; i++) { // Iteramos sobre la mitad del tamaño del número
                uint8_t temp = bytes[i]; // Guardamos el byte actual en una variable temporal
                bytes[i] = bytes[sizeof(float) - i - 1]; // Intercambiamos el byte actual con su correspondiente opuesto en el buffer
                bytes[sizeof(float) - i - 1] = temp; // Asignamos el byte opuesto al lugar del byte actual
            }
            Serial.write(bytes, sizeof(float)); // Transmitimos los bytes invertidos
        }
    }
}

```

Basados en la Opcion 2 para transmitir en el endian contrario **Copiando la representacion de bytes a un buffer y luego invirtiendolos en el buffer**:

```cpp
void setup() {
    Serial.begin(115200);
}

void loop() {
     // 45 60 55 d5
     // https://www.h-schmidt.net/FloatConverter/IEEE754.htmlstatic

    static float num = 3589.3645;
    static uint8_t arr[sizeof(float)] = {0};

    if (Serial.available()) {
        if (Serial.read() == 's') {
            // Copiar la representación de bytes a un buffer
            memcpy(arr, (uint8_t *)&num, sizeof(float));
            // Invertir el orden de los bytes en el buffer
            for (int i = 0; i < sizeof(float) / 2; i++) {
                uint8_t temp = arr[i];
                arr[i] = arr[sizeof(float) - i - 1];
                arr[sizeof(float) - i - 1] = temp;
            }
            // Transmitir los bytes invertidos
            Serial.write(arr, sizeof(float));
        }
    }
}

```

---

### **Ejercicio 5: envía dos números en punto flotante**

Ahora te voy a pedir que practiques. La idea es que transmitas dos números en punto flotante en ambos *endian*.

Para enviar dos números en punto flotante en ambos endian, podemos utilizar un enfoque similar al utilizado en el ejercicio 4, pero esta vez vamos a enviar dos números en lugar de uno. 

- El codigo primero transmite los bytes en el orden original (little endian) y luego los transmite nuevamente en el orden inverso (big endian).

asumimos que estamos trabajando en un entorno donde se utiliza **little endian por defecto**. Si necesitaramos adaptar el código para trabajar en un entorno con big endian por defecto, simplemente intercambiariamos el orden de los bucles que transmiten los bytes en big endian y los bytes en little endian.

```cpp
void setup() {
    Serial.begin(115200);
}

void loop() {
    // Dos números en punto flotante que se desean transmitir
    float num1 = 3589.3645;
    float num2 = -1234.5678;
    
    // Buffer para almacenar la representación en bytes de los números
    static uint8_t arr1[4] = {0};
    static uint8_t arr2[4] = {0};

    if (Serial.available()) {
        if (Serial.read() == 's') {
            // Copiar la representación de bytes de los números al buffer
            memcpy(arr1, (uint8_t *)&num1, 4);
            memcpy(arr2, (uint8_t *)&num2, 4);
            
            // Transmitir los bytes en orden original (little endian)
            Serial.write(arr1, 4);
            Serial.write(arr2, 4);
            
            // Invertir el orden de los bytes antes de transmitirlos (big endian)
            for (int8_t i = 3; i >= 0; i--) {
                Serial.write(arr1[i]);
            }
            for (int8_t i = 3; i >= 0; i--) {
                Serial.write(arr2[i]);
            }
        }
    }
}

```

---

### En este punto me pregunto 
  - ¿Por qué son importantes los protocolos binarios a diferencia de los protocolos ASCII? 
  - ¿Cuál es más utilizado? 
  - ¿Por qué es importante saber utilizar los dos?
  - siento que los protocolos binarios son más complicados que los ASCII

  Los protocolos binarios son importantes en comparación con los protocolos ASCII por varias razones:

1. **Eficiencia en el ancho de banda**: Los protocolos binarios transmiten datos en su forma cruda, es decir, en forma de bytes, lo que significa que no hay necesidad de codificar los datos en caracteres ASCII. Esto reduce la sobrecarga de la comunicación y puede ser más eficiente en términos de ancho de banda, especialmente cuando se transmiten grandes cantidades de datos.

2. **Mayor rango de valores**: Los protocolos binarios pueden representar un rango más amplio de valores numéricos y estructuras de datos complejas en comparación con los protocolos ASCII, que están limitados a caracteres imprimibles y algunos caracteres especiales.

3. **Velocidad de transmisión**: Debido a su formato crudo, los protocolos binarios pueden ser procesados más rápidamente por los dispositivos receptores en comparación con los protocolos ASCII, que requieren un paso adicional de codificación y decodificación.

4. **Seguridad**: Los protocolos binarios pueden ofrecer un mayor nivel de seguridad al transmitir datos, ya que la información se envía de forma más directa y no está sujeta a la interpretación errónea de caracteres especiales.

Sin embargo, los protocolos ASCII también tienen sus propias ventajas:

1. **Interoperabilidad**: Los protocolos ASCII son más fáciles de leer e interpretar para los humanos, lo que los hace ideales para la comunicación entre dispositivos heterogéneos y para la depuración de comunicaciones.

2. **Facilidad de implementación**: Debido a su simplicidad, los protocolos ASCII son más fáciles de implementar y depurar en comparación con los protocolos binarios, que requieren una gestión más cuidadosa de los bytes y bits.

3. **Compatibilidad**: Algunos sistemas heredados o dispositivos pueden requerir comunicación en formato ASCII debido a limitaciones de hardware o software.

Es importante saber utilizar ambos tipos de protocolos porque cada uno tiene sus propias aplicaciones y ventajas. Los protocolos binarios son ideales cuando se requiere eficiencia en el ancho de banda, velocidad y seguridad, mientras que los protocolos ASCII son útiles para la interoperabilidad, la facilidad de implementación y la compatibilidad con sistemas heredados. La elección del protocolo adecuado dependerá de los requisitos específicos de aplicación en desarrollo y del entorno en el que se esté trabajando. Aunque los protocolos binarios pueden parecer más complicados, con práctica y comprensión de los conceptos subyacentes, se pueden utilizar eficazmente para satisfacer las necesidades de la aplicación.

---

### Ejercicio 6: **aplicación interactiva**

En este punto, te pido que repases, bien sea desde lo expuesto en la unidad anterior o remitiéndose a la documentación de C# de Microsoft, para qué sirven los siguientes tres fragmentos de código y qué están haciendo:

```csharp
SerialPort _serialPort =new SerialPort();
_serialPort.PortName = "/dev/ttyUSB0";
_serialPort.BaudRate = 115200;
_serialPort.DtrEnable =true;
_serialPort.Open();
```

```csharp
byte[] data = { 0x01, 0x3F, 0x45};
_serialPort.Write(data,0,1);
```

```csharp
byte[] buffer =new byte[4];
.
.
.

if(_serialPort.BytesToRead >= 4){

    _serialPort.Read(buffer,0,4);
for(int i = 0;i < 4;i++){
        Console.Write(buffer[i].ToString("X2") + " ");
    }
}
```

> [!IMPORTANT]
> 💡 **A PRACTICAR**
>
> Inventa una aplicación en Unity que utilice TODOS los métodos anteriores. Ten presente que necesitarás, además, inventar también la aplicación del microcontrolador.

---

### **Ejercicio 7: RETO**

Vas a enviar 2 números en punto flotante desde un microcontrolador a una aplicación en Unity usando comunicaciones binarias. Además, inventa una aplicación en Unity que modifique dos dimensiones de un *game object* usando los valores recibidos.

> [!TIP]
> 💡 Te voy a dejar una ayuda. Revisar el siguiente fragmento de código… ¿Qué hace?


```csharp
byte[] buffer = new byte[4];
.
.
.
if(_serialPort.BytesToRead >= 4){
  _serialPort.Read(buffer,0,4);
  Console.WriteLine(System.BitConverter.ToSingle(buffer,0));
```

> [!IMPORTANT]
> 💡 Presta especial atención **System.BitConverter.ToSingle**. Ahora, te pediré que busques en la documentación de Microsoft de C# qué más te ofrece System.BitConverter.

**Descirpción de la solución de este ejercicio de practica:**

**Aplicación en Unity:** 

**Descripción**: Una aplicación de monitoreo y control remoto para un sistema de iluminación inteligente. La aplicación permite al usuario ajustar el brillo de una lámpara LED utilizando controles deslizantes en la interfaz de usuario de Unity. La aplicación se comunica con un microcontrolador simulado que controla la lámpara LED.

**Funcionalidades**:
1. La aplicación muestra un control deslizante para ajustar el brillo de la lámpara LED.
2. Cuando el usuario ajusta el control deslizante, la aplicación envía el valor de brillo al microcontrolador simulado a través de comunicación serie.
3. El microcontrolador simulado recibe el valor de brillo y controla la lámpara LED para ajustar su intensidad luminosa.
4. El microcontrolador simulado envía de vuelta a la aplicación el estado actual de la lámpara LED.
5. La aplicación muestra el estado actual de la lámpara LED en la interfaz de usuario.

### Microcontrolador simulado:

**Descripción**: Un microcontrolador simulado que recibe comandos de brillo de la lámpara LED y devuelve el estado actual de la misma.

**Funcionalidades**:
1. El microcontrolador simulado espera comandos de brillo enviados desde la aplicación Unity a través de comunicación serie.
2. Cuando recibe un comando de brillo, el microcontrolador simulado ajusta la intensidad luminosa de la lámpara LED simulada.
3. El microcontrolador simulado envía de vuelta a la aplicación Unity el estado actual de la lámpara LED, incluyendo su brillo actual.

### Implementación en Unity:

1. Configura un objeto `SerialPort` en Unity para establecer una conexión serie con el microcontrolador simulado.
2. Implementa un control deslizante en la interfaz de usuario de Unity para permitir al usuario ajustar el brillo de la lámpara LED.
3. Utiliza el método `SerialPort.Write()` para enviar el valor de brillo al microcontrolador simulado.
4. Utiliza el método `SerialPort.Read()` para recibir el estado actual de la lámpara LED desde el microcontrolador simulado.
5. Actualiza la interfaz de usuario de Unity para mostrar el estado actual de la lámpara LED.

>[!NOTE]
>
>El proyecto en unity se puede abrir en la carpeta con el nombre Ejercicio 7 unit 3 App interactiva en la version del editor 2022.3.21.f1

Asi se ve la interfaz de unity para el usuario:

https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/ca0d88cb-4bc1-4fb1-af8b-5d25643e8f7e

Este es el bloque de codigo para el slider:

```csharp
using UnityEngine;
using UnityEngine.UI;
using System.IO.Ports; // Para la comunicación serial
using TMPro; // Importa el espacio de nombres TMPro para usar el tipo TextMeshProUGUI


public class SliderController : MonoBehaviour
{
    public Slider slider;
    public TextMeshProUGUI valueText;
    public Light lampLight;

    SerialPort serialPort;

    void Start()
    {
        // Inicializar el puerto serial
        serialPort = new SerialPort("COM4", 9600); 
        serialPort.Open();
    }

    void Update()
    {
        // Mostrar el valor del slider en el texto
        valueText.text = slider.value.ToString("F2");

        // Controlar la intensidad de la luz según la posición del slider
        float intensity = slider.value; // Suponiendo que el slider va de 0 a 1
        lampLight.intensity = intensity * 1; // 


        // Enviar el valor por el puerto serial
        float sliderValue = slider.value;
        serialPort.WriteLine(sliderValue.ToString("F2"));
    }

    void OnDestroy()
    {
        // Cerrar el puerto serial cuando el objeto se destruye
        if (serialPort != null && serialPort.IsOpen)
        {
            serialPort.Close();
        }
    }
}
```

Este es el bloque de codigo para el botón:

```csharp
using UnityEngine;
using UnityEngine.UI;
using TMPro; // Importa el espacio de nombres TMPro para usar el tipo TextMeshProUGUI


public class LightSwitch : MonoBehaviour
{
    public Light lampLight;
    public Button switchButton; 
    public TMP_Text buttonText; // Referencia al componente de texto de TextMeshPro

    bool isOn = true;

    void Start()
    {
        // Asignar la función de toggle al botón
        switchButton.onClick.AddListener(ToggleLight);
    }

    void ToggleLight()
    {
        // Cambiar el estado del bombillo y actualizar el texto del botón
        isOn = !isOn;
        lampLight.enabled = isOn;
        buttonText.text = isOn ? "Apagar" : "Encender"; // Actualizar el texto del botón
    }
}
```

Nota: Hace falta el bloque de codigo para el controlador y establecer el protocolo binario, hacer pruebas y evidenciarlo 

---

### Ejercicio extra: CAD(Conversion de señales Analogo a Digital) Temperatura del sensor en el Raspberry Pi Pico

lo que haremos en esta ocasión es tomar una señal que puede tener cualquier valor en cualquier instante de tiempo (señal análoga, en este caso temperatura) y convertirla a 0s y 1s (señal digital). Para eso utilizamos un conversor análogo a Digital (CAD) y para el caso del Raspberry Pi Pico ya está incorporado, entonces se trata de usarlo. Para este caso no requieres hacer conexiones adicionales. Si tu reto de hoy funciona adecuadamente, al  correr tu código, visualizar los datos en el monitor serial y poner el dedo en el integrado principal de la tarjeta debes observar cómo la temperatura va aumentando lentamente. Muchos éxitos, utiliza los diferentes mecanismos de aprendizaje. La idea es que logres resolver esto de forma individual, imagínate algo así como una prueba técnica de una empresa. Al final del proceso graba un video explicando tu código verbalmente y mostrando el funcionamiento. Recuerda que las medidas las debemos ver en punto flotante.

Este ejercicio está diseñado para que lo realices en máximo 2 horas de tu tiempo. 
En este espacio debes montar un video, o link al video, donde muestres en pantalla el código desarrollado para adquirir el dato de temperatura, la explicación verbal de dicho código que muestre tu comprensión y el funcionamiento.
Este ejercicio corresponde al 10% del trabajo  final de la unidad 3.

- Rúbrica del trabajo asíncrono:
  - Explicación verbal en el video (2unds)
  - Funcionamiento evidenciado en el video (3 unds)

Material de apoyo para el desarrollo de la actividad asincrónica lo encontrarás a continuación y en la misma carpeta del repositorio:

[CAD.pdf](https://upbeduco-my.sharepoint.com/:b:/g/personal/vera_perez_upb_edu_co/EaOWw61VyFNJitOxEfd90vIBI_IHcwE1qK0W8vdkXfht4A?e=0fpEII)


---

### Trabajo Final Unidad 3

**Narrativa opcional para el trabajo final de la unidad 3 o continuar con el reproductor de musica de la entrega final de la unidad 2**

Una cabina acustica para la grabación de instrumentos, voces, foleys, El controlador avisa de la temperactura actual de la cabina, como los artistas/productores pueden durar horas dentro y con el material acustico que envuelve la cabina puede hacer que se acumule calor durante las sesiones y para no tener que preocuparse por ello, el controlador a temperaturas altas debe poder encender el aire acondicionado y apagarse a temperaturas bajas para aclimar el ambiente dentro de la cabina, adicional dentro de la cabina hay una lampara que se enciende por 5 segundos indicando que ha pasado 1 hora de sesion para recordarles que tomen un descanso y reiniciar el conteo de una hora.

variables:
- temperatura de la cabina (sensor del controlador)
- encender/apagar el aire acondicionado a 24.5° (regulable desde unity?)
- pomodoro encender una lampara dentro de la cabina por 5 seg cada hora(sesion)
