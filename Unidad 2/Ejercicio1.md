### **Ejercicio 1: comunicación entre computador y controlador**

La idea de este ejercicio es comunicar a través del puerto serial un computador con un controlador. La aplicación del computador la construirás usando una plataforma de creación de contenido digital interactivo llamada Unity.

Estudia con detenimiento el código para el controlador y para el computador. Busca la definición de todas las funciones usadas en la documentación de Arduino y de Microsoft.

¿Quién debe comenzar primero la comunicación, el computador o el controlador? ¿Por qué?

Programa el controlador con este código:

```cpp
void setup()
{
  Serial.begin(115200);
}

void loop()
{
if(Serial.available())
  {
  if(Serial.read() == '1')
    {
      Serial.print("Hello from Raspberry Pi Pico");
    }
  }
}
```

Prueba la aplicación con ScriptCommunicator. ¿Cómo funciona?

Ahora crea un proyecto en Unity. Antes de continuar con la escritura del código configura:

- La herramienta que usarás para editar tus programas. En este caso usarás Visual Studio. Recuerda que este paso lo puedes hacer en el menú Edit, Preferences, External Tools y seleccionar Visual Studio en la opción External Script Editor.
- Configura un scripting backend que permita soportar las comunicaciones seriales con el controlador. Ve al menú Edit, Project Settings, Player, Other Settings, busca la opción Scripting backend y selecciona Mono, luego busca API Compatibility Level y seleccionar .NET Framework.

<aside>
	
💡 **Advertencia:**
Siempre que trabajes con comunicaciones seriales y Unity es necesario seleccionar .NET Framework como el Scripting backend, de lo contrario tendrás un error de compilación relacionado con el puerto Serial.

</aside>

Crea un nuevo C# Script y un Game Object. Añade el Script al GameObject. Ve al menu Assets y luego selecciona Open C# Project.

```csharp
using UnityEngine;
using System.IO.Ports;
public class Serial : MonoBehaviour
{
private SerialPort _serialPort =new SerialPort();
private byte[] buffer =new byte[32];

void Start()
    {
        _serialPort.PortName = "COM3";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable =true;
        _serialPort.Open();
        Debug.Log("Open Serial Port");
    }

void Update()
    {

				if (Input.GetKeyDown(KeyCode.A))
        {
            byte[] data = {0x31};// or byte[] data = {'1'};            
						_serialPort.Write(data,0,1);
            Debug.Log("Send Data");
        }

				if (Input.GetKeyDown(KeyCode.B))
        {
						if (_serialPort.BytesToRead >= 16)
            {
                _serialPort.Read(buffer, 0, 20);
                Debug.Log("Receive Data");
                Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
            }
        }

    }
}
```

Analiza:

- ¿Por qué es importante considerar las propiedades *PortName* y *BaudRate*?
- ¿Qué relación tienen las propiedades anteriores con el controlador?

<hr/>

## Solución

> ¿Quién debe comenzar primero la comunicación, el computador o el controlador? ¿Por qué?

Quien debe comenzar primero la comunicación es el computador dado que mediante el puerto USB disponible está a la espera de que un dispositivo nuevo sea conectado(en este caso el controlador).

Sin embargo en terminos de comunicacion de este contexto **es el controlador** el que debe garantizar que el dispositivo receptor esté listo para recibir y procesar los datos. Esto implica que el 
Raspberry Pi Pico debe estar configurado correctamente para escuchar en el puerto serial y debe tener el código adecuado para manejar los datos que recibe.


```cpp
void setup() //Funcion para inicializar, solo sucede una vez al iniciar
{
  Serial.begin(115200); //inicializa la comunicacion serial con una velocidad en baudios o bytes
}

void loop() //Funcion que se ejecuta continuamente despues de inicializar el contenido de la funcion setup()
{
if(Serial.available()) // verifica si hay datos en el puerto serial
  {
  if(Serial.read() == '1') // lee el dato del puerto serial y si este es "1" entra al siguiente codigo
    {
      Serial.print("Hello from Raspberry Pi Pico"); // como la condicion if se cumplió entonces imprime el mensaje
    }
  }
}
```


1. `void setup() { }`: Esta función se ejecuta una vez cuando el programa comienza. En este caso, se inicializa la comunicación serial con una velocidad de 115200 baudios mediante `Serial.begin(115200);`.

2. `void loop() { }`: Esta función se ejecuta continuamente después de que `setup()` haya terminado de ejecutarse. Aquí es donde ocurre la mayor parte del trabajo del programa.

3. `if(Serial.available()){ }`: Esta condición verifica si hay datos disponibles en el puerto serial. Si hay datos disponibles para leer, entra en el bloque de código que sigue.

4. `if(Serial.read() == '1'){ }`: Aquí se lee un byte del puerto serial utilizando `Serial.read()`. Si el byte leído es igual a `'1'`, lo cual significa que se ha enviado el carácter "1" desde el otro dispositivo conectado al puerto serial, entonces entra en el bloque de código que sigue.

5. `Serial.print("Hello from Raspberry Pi Pico");`: Si se ha recibido el carácter "1", este comando imprime la cadena "Hello from Raspberry Pi Pico" a través del puerto serial, lo que significa que envía este mensaje al dispositivo conectado al puerto serial.


> Prueba la aplicación con ScriptCommunicator. ¿Cómo funciona?

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/2b4a0d66-6a34-4ed3-895f-4ac55e7d4f05)

lo que ocurre cuando se conecta el controlador es basicamente que este está esperando que se le envíe la tecla "1" mediante el puerto serial para poder imprimir el mensaje,
independientemente de los caracteres que se escriban siempre y cuando esten acompañadas del "1" imprimirá el mensaje, si la cadena de caracteres no lo contienen no lo hará

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/b80e60b7-5693-4cdb-b9ae-c4b803a3e5cf)

como en este caso que le envíe "545412" y el controlador imprimió el mensaje porque contenia el "1" y el programa no tiene restricción de que unicamente deba ser el 1 para poder imprimir.

---

Ahora en unity: en un Game Object pegar el codigo entender y analizar lo que hace:

```csharp
using UnityEngine; // declaramos que vamos a usar UnityEngine y su entorno
using System.IO.Ports; // declaramos que usaremos los puertos serie para comunicarnos con controladores 

public class Serial : MonoBehaviour // El nombre del archivo y de la clase Serial (en mi caso le puse ejercicio1_ScriptSerial) y hereda la clase Monobehaviour de Unity para poderlo anexar en el GameObject
{
    private SerialPort _serialPort = new SerialPort(); // Se declara un objeto SerialPort llamado _serialPort
    private byte[] buffer = new byte[32]; // Se declara un buffer de bytes de tamaño 32

    void Start()
    {
        _serialPort.PortName = "COM3"; // Se establece el nombre del puerto serial a COM3 depende del puerto donde se conecte en mi caso COM4
        _serialPort.BaudRate = 115200; // Se establece la velocidad de baudios en 115200
        _serialPort.DtrEnable = true; // Se habilita la señal DTR
        _serialPort.Open(); // Se abre el puerto serial
        Debug.Log("Open Serial Port"); // Se imprime un mensaje en la consola indicando que el puerto serial se ha abierto
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.A)) // Si se presiona la tecla A
        {
            byte[] data = { 0x31 }; // Se crea un arreglo de bytes con el valor hexadecimal 0x31 (equivalente a '1' en ASCII)
            _serialPort.Write(data, 0, 1); // Se escribe el arreglo de bytes en el puerto serial
            Debug.Log("Send Data"); // Se imprime un mensaje en la consola indicando que se han enviado datos
        }

        if (Input.GetKeyDown(KeyCode.B)) // Si se presiona la tecla B
        {
            if (_serialPort.BytesToRead >= 16) // Si hay al menos 16 bytes disponibles para leer en el puerto serial
            {
                _serialPort.Read(buffer, 0, 20); // Se leen 20 bytes del puerto serial y se almacenan en el buffer
                Debug.Log("Receive Data"); // Se imprime un mensaje en la consola indicando que se han recibido datos
                Debug.Log(System.Text.Encoding.ASCII.GetString(buffer)); // Se imprime en la consola la cadena de texto correspondiente a los 20 bytes recibidos
            }
        }
    }
}
```

Este código C# para Unity controla la comunicación serial entre la computadora y el RaspberryPiPico para recibir y enviar datos a través del puerto COM3 (dependerá de que puerto esta conectado en mi caso COM4).

1. Se importan las bibliotecas necesarias para trabajar con Unity (`UnityEngine`) y para la comunicación serial (`System.IO.Ports`) las cuales se usarán.

- `using UnityEngine;`: Esta línea importa el espacio de nombres `UnityEngine`, que contiene las clases y funciones necesarias para el desarrollo de aplicaciones y juegos en Unity. Esto incluye todo, desde gráficos en 2D y 3D hasta física, audio, interfaz de usuario y más. Es esencial para cualquier script que forme parte de un proyecto de Unity.

- `using System.IO.Ports;`: Esta línea importa el espacio de nombres `System.IO.Ports`, que proporciona las clases y funciones necesarias para realizar comunicaciones serie en C#. Esto es esencial para interactuar con puertos seriales en la computadora, como los puertos COM utilizados para conectar dispositivos como Arduino o Raspberry Pi.

2. Se declara una clase llamada `Serial` que hereda de `MonoBehaviour`, lo que significa que este script puede adjuntarse a un GameObject en Unity.

3. Se crean dos variables privadas: `_serialPort`, que es un objeto de la clase `SerialPort` utilizado para comunicarse a través del puerto serial, y `buffer`, que es un arreglo de bytes utilizado para almacenar los datos recibidos del puerto serial.

4. En el método `Start()`, se configuran las propiedades del objeto `_serialPort` (nombre del puerto, velocidad de baudios, habilitación de DTR) y se abre el puerto serial. Además, se imprime un mensaje en la consola indicando que el puerto serial se ha abierto.

 	La línea `_serialPort.DtrEnable = true;` establece el estado del pin DTR (Data Terminal Ready) del puerto serial:

	- DTR (Data Terminal Ready): Es una señal que el dispositivo conectado al puerto serial puede utilizar para indicar al otro extremo de la comunicación serial que está listo para la comunicación. Cuando se establece en "true" (verdadero), como en este caso, significa que el dispositivo conectado está listo para la comunicación.

	- Su función: Al habilitar el pin DTR, se indica al dispositivo conectado que está listo para la comunicación. Esto puede ser útil para dispositivos que requieren esta señal para iniciar la comunicación o para configurar correctamente el flujo de datos.

5. En el método `Update()`, se verifica si se ha presionado la tecla A o B. Si se presiona la tecla A, se envía un byte con el valor hexadecimal 0x31 ('1' en ASCII) al dispositivo externo a través del puerto serial. Si se presiona la tecla B y hay al menos 16 bytes disponibles para leer en el puerto serial, se leen 20 bytes del puerto serial y se almacenan en el buffer. Luego, se imprime en la consola un mensaje indicando que se han recibido datos, seguido de la cadena de texto correspondiente a los bytes recibidos, convertida utilizando la codificación ASCII.

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/1bb0df1f-23ff-45b8-b55a-4686a655fe19)

Se puede observar que se finalizó la funcion inicial e imprime que el puerto serial esta abierto

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/cf9655d9-63e5-4334-87b0-e03c9458df0f)

Al presionar la tecla A envía al controlador el valor hexadecimal 0x31 (equivalente a '1' en ASCII) e imprime en consola que envió los datos y espera que se presione A o B de nuevo

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/b5295ee3-d64b-4a91-9a4b-c3ea4b1ac96e)

Al presionar B imprime que hermos recibido datos e imprime los datos recibidos como el codigo esta establecido que solo lea 20 bytes y los guarde en el buffer para imprimirlos en la consola.

> Analiza:
>
> - ¿Por qué es importante considerar las propiedades *PortName* y *BaudRate*?
> - ¿Qué relación tienen las propiedades anteriores con el controlador?

Es importante considerar el `PortName` ya que este es el puerto por el cual se está comunicando con el controlador y el `baudRate` velocidad en la que se van a comunicar entre sí

la relación que tienen las propiedad son que la primera(`PortName`) define el nombre del puerto de comunicacion con el controlador y la segunda(`baudRate` ) la velocidad de comunicacion entre los dispositivos en bytes/baudios



