# Unidad 3. Protocolos Binarios

# **Introducción**

En esta unidad seguiremos profundizando en la integración de dispositivos periféricos a las aplicaciones interactivas, pero esta vez, usando protocolos binarios.

# **Propósitos de aprendizaje**

Integrar aplicaciones interactivas y periféricos utilizando protocolos seriales binarios.

# **Trayecto de actividades**

## **Ejercicio 1: introducción a los protocolos binarios - caso de estudio**

¿Cómo se ve un protocolo binario? Para explorar este concepto te voy a mostrar una hoja de datos de un [sensor](http://www.chafon.com/productdetails.aspx?pid=382) comercial que usa un protocolo de comunicación binario. La idea es que tu explores su hoja de datos ([datasheet](https://drive.google.com/file/d/1uDtgNkUCknkj3iTkykwhthjLoTGJCcea/view?pli=1)), tanto como sea posible, invitándote a que observes con detenimiento hasta la página 5.

Durante la lectura, intenta dar respuestas a las siguientes preguntas:

- ¿Cómo se ve un protocolo binario?
- ¿Puedes describir las partes de un mensaje?
- ¿Para qué sirve cada parte del mensaje?

# **Ejercicio 2: experimento**

En [este](https://www.arduino.cc/reference/en/language/functions/communication/serial/) enlace vas a mirar los siguientes métodos. Te pediré que, por favor, los tengas a mano porque te servirán para resolver problemas. Además, en este punto, hagamos un repaso de las funciones que han apoyado la comunicación seral:

<aside>
💡 Serial.available()
Serial.read()
Serial.readBytes(buffer, length)
Serial.write()

</aside>

Nótese que la siguiente función no está en la lista de repaso:

<aside>
💡 `**Serial.readBytesUntil()**`

</aside>

¿Sospecha por qué se ha excluido? La razón es porque en un protocolo binario usualmente no tiene un carácter de FIN DE MENSAJE, como si ocurre con los protocolos ASCII, donde usualmente el último carácter es el `\n`.

## Ejercicio 3: **¿Qué es el *endian*?**

Cuando trabajamos con protocolos binarios es necesario transmitir variables que tienen una longitud mayor a un byte. Por ejemplo, los números en punto flotante cumplen con el [estándar IEEE754](https://www.h-schmidt.net/FloatConverter/IEEE754.html) y se representan con 4 bytes.

Algo que debemos decidir al trabajar con números como los anteriormente descritos es el orden en elcual serán transmitidos sus bytes. En principio tenemos dos posibilidades: i) transmitir primero el byte de menor peso (*little endian*) o transmitir primero el byte de mayor peso (*big endian*). Por lo tanto, al diseñar un protocolo binario se debe escoger una de las dos posibilidades.

## **Ejercicio 4: transmitir números en punto flotante**

<aside>
💡 **¡Desempolva ScriptCommunicator!**

Para este ejercicio vas a necesitar una herramienta que te permita ver los bytes que se están transmitiendo sin interpretarlos como caracteres ASCII. Usa **ScriptCommunicator** en los sistemas operativos Windows o Linux y **CoolTerm** en el sistema operativo MacOS (te soporta la arquitectura Mx).

</aside>

¿Cómo transmitir un número en punto flotante? Veamos dos alternativas:

Opción 1:

```arduino
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

```arduino
void setup() {
    Serial.begin(115200);
}

void loop() {
// 45 60 55 d5// https://www.h-schmidt.net/FloatConverter/IEEE754.htmlstatic float num = 3589.3645;
static uint8_t arr[4] = {0};

if(Serial.available()){
if(Serial.read() == 's'){
            memcpy(arr,(uint8_t *)&num,4);
            Serial.write(arr,4);
        }
    }
}
```

Preguntas:

- ¿En qué *endian* estamos transmitiendo el número?
- Y si queremos transmitir en el *endian* contrario, ¿Cómo se modifica el código?

Pausa… A continuación, te dejo una posible solución a la pregunta anterior.

```arduino
void setup() {
    Serial.begin(115200);
}

void loop() {
// 45 60 55 d5// https://www.h-schmidt.net/FloatConverter/IEEE754.htmlstatic float num = 3589.3645;
static uint8_t arr[4] = {0};

if(Serial.available()){
if(Serial.read() == 's'){
            memcpy(arr,(uint8_t *)&num,4);
for(int8_t i = 3; i >= 0; i--){
              Serial.write(arr[i]);
            }
        }
    }
}
```

## **Ejercicio 5: envía tres números en punto flotante**

Ahora te voy a pedir que practiques. La idea es que transmitas dos números en punto flotante en ambos *endian*.

## Ejercicio 6: **aplicación interactiva**

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

<aside>
💡 **A PRACTICAR**

Inventa una aplicación en Unity que utilice TODOS los métodos anteriores. Ten presente que necesitarás, además, inventar también la aplicación del microcontrolador.

</aside>

## **Ejercicio 7: RETO**

Vas a enviar 2 números en punto flotante desde un microcontrolador a una aplicación en Unity usando comunicaciones binarias. Además, inventa una aplicación en Unity que modifique dos dimensiones de un *game object* usando los valores recibidos.

<aside>
💡 Te voy a dejar una ayuda. Revisar el siguiente fragmento de código… ¿Qué hace?

</aside>

```csharp
byte[] buffer = new byte[4];
.
.
.
if(_serialPort.BytesToRead >= 4){
  _serialPort.Read(buffer,0,4);
  Console.WriteLine(System.BitConverter.ToSingle(buffer,0));
```

<aside>
💡 Presta especial atención **System.BitConverter.ToSingle**. Ahora, te pediré que busques en la documentación de Microsoft de C# qué más te ofrece System.BitConverter.

</aside>

## Trabajo final de la unidad 3

- En este trabajo final vas a crear un protocolo binario para comunicar la aplicación del PC y el microcontrolador.
- Vas a leer mínimo tres variables: la primera será la variable real temperatura a través del sensor incorporado en el Raspberry Pi Pico y las otras pueden ser variables creadas a través de contadores. En este trabajo las variables deben ser números en punto flotante y el delta de cambio ya no es UNO, sino un número en punto flotante.
- Para leer las variables del microcontrolador, el PC enviará un BYTE (tu decides cuál). El microcontrolador responderá la solicitud con la información de TODASlas variables. Por cada variable se deben indicar tres elementos:
    - el valor actual
    - si está habilitada
    - el intervalo o delta de cambio de la variable.
- Debes incluir un byte extra al final que cambiará en función de la información que envíes (*checksum*). Parte del ejercicio es consultar cómo puedes construir el checksum e implementarlo. La idea con este byte es que el receptor pueda verificar que la información recibida no se dañó en el camino.
- El microcontrolador deberá mantener un LED funcionando a una frecuencia de 0.5 Hz. El objetivo de este LED es que verifiques de manera visual que la aplicación en el microcontrolador NUNCA se bloquea.

Para desarrollar lo anterior tienes dos alternativas:

**Alternativa 1:**  Continuar con la experiencia trabajada en la unidad anterior y hacerle los ajustes para incluir la variable temperatura en caso de que no la tengas y los otros a los que haya lugar de acuerdo a los requerimientos.

**Alternativa 2:** Construir una nueva experiencia en la cual se interactúe con mínimo tres variables y la temperatura será una de ellas.  Si optas por esta opción es muy importante la narrativa y la experiencia en sí misma, que utilice los datos de las variables en la toma de decisiones dentro de la experiencia.

La presentación trabajada en clase la encuentras a continuación:

[02 Sistemas numéricos_v22_sol.pdf](https://upbeduco-my.sharepoint.com/:b:/g/personal/vera_perez_upb_edu_co/EfFkGLGlfolCneLd-WE-LlwByt-a6iWAQafw40zuGaZC-Q?e=IRCh2t)

Material de apoyo para el desarrollo de la actividad asincrónica lo encontrarás a continuación: 

[CAD.pdf](https://upbeduco-my.sharepoint.com/:b:/g/personal/vera_perez_upb_edu_co/EaOWw61VyFNJitOxEfd90vIBI_IHcwE1qK0W8vdkXfht4A?e=0fpEII)

© Derechos de autor 2023, Juan Franco. Revisión 42b38a74.
