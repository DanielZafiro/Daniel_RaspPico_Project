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

