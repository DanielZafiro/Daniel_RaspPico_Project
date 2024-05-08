# Unidad 2. **Protocolos ASCII**

# **Introducción**

En la unidad anterior te has concentrado en la construcción de software para sistemas embebidos. En esta unidad aprenderás como integrar a una plataforma de cómputo interactiva dichos sistemas embebidos mediante el uso de protocolos de comunicación ASCII.

## **Propósitos de aprendizaje**

Construir aplicaciones interactivas que integren información del mundo exterior mediante el intercambio de información codificada en ASCII.

## **Trayecto de actividades**

### **Ejercicio 1: comunicación entre computador y controlador**

La idea de este ejercicio es comunicar a través del puerto serial un computador con un controlador. La aplicación del computador la construirás usando una plataforma de creación de contenido digital interactivo llamada Unity.

Estudia con detenimiento el código para el controlador y para el computador. Busca la definición de todas las funciones usadas en la documentación de Arduino y de Microsoft.

¿Quién debe comenzar primero la comunicación, el computador o el controlador? ¿Por qué?

Programa el controlador con este código:

```cpp
void setup() {
  Serial.begin(115200);
}

void loop() {
if(Serial.available()){
if(Serial.read() == '1'){
      Serial.print("Hello from Raspberry Pi Pico");
    }
  }
}
```

Prueba la aplicación con ScriptCommunicator. ¿Cómo funciona?

Ahora crea un proyecto en Unity. Antes de continuar con la escritura del código configura:

- La herramienta que usarás para editar tus programas. En este caso usarás Visual Studio. Recuerda que este paso lo puedes hacer en el menú Edit, Preferences, External Tools y seleccionar Visual Studio en la opción External Script Editor.
- Configura un scripting backend que permita soportar las comunicaciones seriales con el controlador. Ve al menú Edit, Project Settings, Player, Other Settings, busca la opción Scripting backend y selecciona Mono, luego busca API Compatibility Level y seleccionar .NET Framework.

> [!WARNING]
>
> Siempre que trabajes con comunicaciones seriales y Unity es necesario seleccionar .NET Framework como el Scripting backend, de lo contrario tendrás un error de compilación relacionado con el puerto Serial.

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

### **Ejercicio 2: experimento**

> [!WARNING]
>
> ESTE SEMESTRE CAMBIAMOS DE controlador.
>
> Los videos que te mostraré utilizan un controlador y editor diferente para escribir los programas de este. NO HAY PROBLEMA. Puedes usar el mismo código para experimentar con el controlador que tienes ahora y con el IDE de Arduino.
>

Te invito a ver antes unos videos cortos con la explicación de este experimento usando unas herramientas un poco diferentes, sin embargo, el principio es el mismo.  Te dejo [este](https://youtube.com/playlist?list=PLX4ZVWZsOgzST9kfU9_ohOUYp_oDo2z48) link).

Ahora realiza este experimento. Modifica la aplicación del PC así:

```csharp
using UnityEngine;
using System.IO.Ports;
using TMPro;

public class Serial : MonoBehaviour
{
	private SerialPort _serialPort =new SerialPort();
	private byte[] buffer =new byte[32];

	public TextMeshProUGUI myText;

	private static int counter = 0;

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
        myText.text = counter.ToString();
        counter++;

				if (Input.GetKeyDown(KeyCode.A))
        {
            byte[] data = {0x31};// or byte[] data = {'1'};            
						_serialPort.Write(data,0,1);
            int numData = _serialPort.Read(buffer, 0, 20);
            Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
            Debug.Log("Bytes received: " + numData.ToString());
        }
    }
}
```

> [!WARNING]
>
> Ojo con el puerto serial. Ten cuidado con el programa anterior. Particularmente, nota esta línea en el código escrito:
>
> ```csharp
>  _serialPort.PortName = «COM3»;
> ```
>
> En tu sistema operativo debes averiguar en qué puerto está el controlador y cómo se llama. En Windows se usa COMx, donde x es el número del puerto serial asignado por el sistema operartivo a tu controlador.

A continuación, debes adicionar a la aplicación un elemento de GUI tipo *Text - TextMeshPro* y luego, arrastrar una referencia a este elemento a *myText* (si no sabes cómo hacerlo llama al profe).

Y la aplicación del controlador:

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
			      delay(3000);
			      Serial.print("Hello from Raspi");
				}
		}
}
```

Ejecuta la aplicación en Unity. Verás un número cambiar rápidamente en pantalla. Ahora presiona la tecla A (no olvides dar click en la pantalla *Game*). ¿Qué pasa? ¿Por qué crees que ocurra esto?

> [!IMPORTANT]
> **MUY IMPORTANTE:**
>
>¿Observas que la aplicación se bloquea? Este comportamiento es inaceptable para una aplicación interactiva de tiempo real. ¿Cómo se podría corregir este comportamiento?

Prueba con el siguiente código. Luego, **ANALIZA CON DETENIMIENTO.** Una vez más, no olvides cambiar el puerto serial.

```csharp
using UnityEngine;
using System.IO.Ports;
using TMPro;

public class Serial : MonoBehaviour
{
		private SerialPort _serialPort =new SerialPort();
		private byte[] buffer =new byte[32];

		public TextMeshProUGUI myText;

		private static int counter = 0;

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
        myText.text = counter.ToString();
        counter++;

				if (Input.GetKeyDown(KeyCode.A))
				{
            byte[] data = {0x31};// or byte[] data = {'1'};
            _serialPort.Write(data,0,1);
        }
				if (_serialPort.BytesToRead > 0)
			  {
	          int numData = _serialPort.Read(buffer, 0, 20);
            Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
            Debug.Log("Bytes received: " + numData.ToString());
        }
		}

```

¿Funciona?
Por ejemplo, ¿Qué pasaría si al momento de ejecutar la instrucción `int numData = 
_serialPort.Read(buffer, 0, 20);` solo han llegado 10 de los 16 bytes del mensaje? ¿Cómo puede hacer tu programa para saber que ya tiene el mensaje completo? ¿Cómo se podría garantizar que antes de hacer la operación Read tenga los 16 bytes listos para ser leídos? Además, si los mensajes que envía el controlador tienen tamaños diferentes, ¿Cómo haces para saber que el mensaje enviado está completo o faltan bytes por recibir?

> [!TIP]
> **Piensa antes de continuar…**
>
> Por favor piensa antes de continuar e intenta dar respuesta a las preguntas plateadas. Sin embargo, no te preocupes, porque te voy a contar en un momento que puedes hacer para responderlas.


### Ejercicio 3: eventos externos

Nótese que en los dos ejercicios anteriores, el PC primero le pregunta al controlador por datos (le manda un 1). ¿Y si el PC no pregunta?

Realiza el siguiente experimento. Programa ambos códigos y analiza su funcionamiento.

```cpp
void task()
{
		enum class TaskStates
		{
				INIT,
				WAIT_INIT,
				SEND_EVENT
		};
		static TaskStates taskState = TaskStates::INIT;
		static uint32_t previous = 0;
		static u_int32_t counter = 0;

		switch (taskState)
		{
				case TaskStates::INIT:
				{
						Serial.begin(115200);
						taskState = TaskStates::WAIT_INIT;
						break;
				}
				case TaskStates::WAIT_INIT:
				{
						if (Serial.available() > 0)
						{
								if (Serial.read() == '1')
								{
										previous = 0; // Force to send the first value immediately
										taskState = TaskStates::SEND_EVENT;
								}
						}
						break;
				}
				case TaskStates::SEND_EVENT:
				{
						uint32_t current = millis();
						if ((current - previous) > 2000)
						{
								previous = current;
								Serial.print(counter);
								counter++;
						}
						if (Serial.available() > 0)
						{
							  if (Serial.read() == '2')
							  {
								    taskState = TaskStates::WAIT_INIT;
							  }
						}
						break;
				}
				default:
				{
						break;
				}
		}
}

void setup()
{
		task();
}

void loop()
{
		task();
}
```

```csharp
using UnityEngine;
using System.IO.Ports;
using TMPro;

enum TaskState
{
    INIT,
    WAIT_START,
    WAIT_EVENTS
}

public class Serial : MonoBehaviour
{
		private static TaskState taskState = TaskState.INIT;
		private SerialPort _serialPort;
		private byte[] buffer;
		public TextMeshProUGUI myText;
		private int counter = 0;

		void Start()
    {
        _serialPort =new SerialPort();
        _serialPort.PortName = "COM3";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable =true;
        _serialPort.Open();
        Debug.Log("Open Serial Port");
        buffer =new byte[128];
    }

void Update()
    {
        myText.text = counter.ToString();
        counter++;

				switch (taskState)
        {
						case TaskState.INIT:
		            taskState = TaskState.WAIT_START;
                Debug.Log("WAIT START");
								break;
						case TaskState.WAIT_START:
								if (Input.GetKeyDown(KeyCode.A))
                {
                    byte[] data = {0x31};// start
                    _serialPort.Write(data,0,1);
                    Debug.Log("WAIT EVENTS");
                    taskState = TaskState.WAIT_EVENTS;
                }
								break;
						case TaskState.WAIT_EVENTS:
								if (Input.GetKeyDown(KeyCode.B))
                {
                    byte[] data = {0x32};// stop
                    _serialPort.Write(data,0,1);
                    Debug.Log("WAIT START");
                    taskState = TaskState.WAIT_START;
                }
								if (_serialPort.BytesToRead > 0)
                {
                    int numData = _serialPort.Read(buffer, 0, 128);
                    Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
                }
								break;
						default:
                Debug.Log("State Error");
								break;
        }
    }
}
```

¿Recuerdas las preguntas presentadas en el experimento anterior? ¿Aquí nos pasa lo mismo?

Analicemos el asunto. Cuando preguntas `_serialPort.BytesToRead > 0` lo que puedes asegurar es que al MENOS tienes un byte del mensaje, pero no puedes saber si tienes todos los bytes que lo componen. Una idea para resolver esto, sería hacer que todos los mensajes tengan el mismo tamaño. De esta manera solo tendrías que preguntar `_serialPort.BytesToRead > SIZE`, donde SIZE sería el tamaño fijo; sin embargo, esto le resta flexibilidad al protocolo de comunicación. Nota que esto mismo ocurre en el caso del programa del controlador con `Serial.available() > 0`. ¿Cómo podrías solucionar este problema?

> [!TIP]
> **PIENSA primero…**
>
>En el siguiente ejercicio te servirá para responder esta pregunta.


### **Ejercicio 4: carácter de fin de mensaje**

Ahora vas a analizar cómo puedes resolver el problema anterior. Puntualmente, analiza el siguiente programa del controlador:

```cpp
String btnState(uint8_t btnState)
{
		if(btnState == HIGH)
		{
				return "OFF";
		}
		else
				return "ON";
}

void task()
{
		enum class TaskStates
		{
		    INIT,
		    WAIT_COMMANDS
	  };
		static TaskStates taskState = TaskStates::INIT;
		constexpr uint8_t led = 25;
		constexpr uint8_t button1Pin = 12;
		constexpr uint8_t button2Pin = 13;
		constexpr uint8_t button3Pin = 32;
		constexpr uint8_t button4Pin = 33;

		switch (taskState)
	  {
				case TaskStates::INIT:
				{
						Serial.begin(115200);
						pinMode(led, OUTPUT);
						digitalWrite(led, LOW);
						pinMode(button1Pin, INPUT_PULLUP);
						pinMode(button2Pin, INPUT_PULLUP);
						pinMode(button3Pin, INPUT_PULLUP);
						pinMode(button4Pin, INPUT_PULLUP);
						taskState = TaskStates::WAIT_COMMANDS;
						break;
				}
				case TaskStates::WAIT_COMMANDS:
				{
						if (Serial.available() > 0)
						{
								String command = Serial.readStringUntil('\n');
								if (command == "ledON")
								{
										digitalWrite(led, HIGH);
								}
								else if (command == "ledOFF")
								{
										digitalWrite(led, LOW);
								}
								else if (command == "readBUTTONS")
							  {
										Serial.print("btn1: ");
						        Serial.print(btnState(digitalRead(button1Pin)).c_str());
						        Serial.print(" btn2: ");
						        Serial.print(btnState(digitalRead(button2Pin)).c_str());
						        Serial.print(" btn3: ");
						        Serial.print(btnState(digitalRead(button3Pin)).c_str());
						        Serial.print(" btn4: ");
						        Serial.print(btnState(digitalRead(button4Pin)).c_str());
						        Serial.print('\n');
					      }
						}
						break;
				}
				default:
				{
						break;
			  }
		}
}

void setup()
{
  task();
}

void loop()
{
  task();
}
```

A continuación, analiza el siguiente programa del PC:

```csharp
using UnityEngine;
using System.IO.Ports;
using TMPro;

enum TaskState
{
    INIT,
    WAIT_COMMANDS
}

public classSerial : MonoBehaviour
{
		private static TaskState taskState = TaskState.INIT;
		private SerialPort _serialPort;
		private byte[] buffer;
		public TextMeshProUGUI myText;
		private int counter = 0;

		void Start()
    {
				_serialPort =new SerialPort();
        _serialPort.PortName = "COM3";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable =true;
        _serialPort.NewLine = "\n";
        _serialPort.Open();
        Debug.Log("Open Serial Port");
        buffer =new byte[128];
    }

		void Update()
    {
        myText.text = counter.ToString();
        counter++;

				switch (taskState)
        {
						case TaskState.INIT:
		            taskState = TaskState.WAIT_COMMANDS;
                Debug.Log("WAIT COMMANDS");
								break;
						case TaskState.WAIT_COMMANDS:
								if (Input.GetKeyDown(KeyCode.A))
                {
		                _serialPort.Write("ledON\n");
                    Debug.Log("Send ledON");
                }
								if (Input.GetKeyDown(KeyCode.S))
                {
                    _serialPort.Write("ledOFF\n");
                    Debug.Log("Send ledOFF");
                }
								if (Input.GetKeyDown(KeyCode.R))
                {
                    _serialPort.Write("readBUTTONS\n");
                    Debug.Log("Send readBUTTONS");
                }
								if (_serialPort.BytesToRead > 0)
                {
                    string response = _serialPort.ReadLine();
                    Debug.Log(response);
                }
								break;
						default:
                Debug.Log("State Error");
								break;
        }
    }
}
```

### **Ejercicio 5: retrieval practice**

Con todo lo que has aprendido hasta ahora, vas a volver a darle una mirada al material expuesto desde el ejercicio 1 hasta el ejercicio 4. Una iteración más cae bien. Pero la idea de este ejercicio es que le expliques a un compañero cada ejercicio mientras tu compañero será hacerte preguntas. Después se invierten los papeles.

### **RETO BONIFICACIÓN: protocolo ASCII**

El reto consiste en implementar un sistema que permita, mediante una interfaz gráfica en Unity interactuar con el controlador. La idea será que puedas leer el estado de una variable que estará cambiando en el controlador y cambiar el estado del LED verde del controlador. Ten presente que aunque este ejercicio usa un controlador simple, los conceptos asociados a su manejo pueden fácilmente extrapolarse a dispositivos y sistemas más complejos.

Este reto está compuesto por dos partes: aplicación para el PC y aplicación para el controlador.

**Aplicación para el PC:**

- Debes gestionar las comunicaciones seriales y al mismo tiempo mostrar un contenido digital dinámico que permita observar fácilmente caídas en el *framerate*. Si quieres puedes usar la estrategia del contador que se incremente en cada *frame* o cambiar por algo que te guste más.
- Implementa una interfaz de usuario compuesta por botones y cajas de texto para controlar y visualizar.

**Aplicación para el controlador:**

- Programa una tarea que espere solicitudes de datos por parte de la aplicación interactiva. Por favor, recuerda de los ejercicios del trayecto de actividades cómo se hace esto.
- La tarea debe incrementar cada segundo un contador.
- La tarea debe poder modificar el estado del LED por solicitud de la aplicación interactiva.

**Protocolo de comunicación:**

- El PC SIEMPRE inicia la comunicación solicitando información al controlador. Es decir, desde la aplicación del PC siempre se solicita información y el controlador responde.
- Desde el PC se enviarán tres solicitudes: `read`, `outON`, `outOFF`.
- Para enviar los comandos anteriores usarás los botones de la interfaz de usuario.
- El controlador enviará los siguientes mensajes de respuesta a cada solicitud:
    - Respuesta a `read`: `estadoContador,estadoLED`. Por ejemplo, una posible respuesta será: `235,OFF`. Quiere decir que el contador está en 235 y el LED está apagado.
    - Respuesta a `outON` y `outOFF`: `estadoLED`. Es decir, el controlador recibe el comando, realiza la orden solicitada y devuelve el estado en el cual quedó el LED luego de la orden.
- No olvides que DEBES terminar TODOS los mensajes con el carácter NEWLINE (`\n`) para que ambas partes sepan que el mensaje está completo.

# Trabajo final

Para esta evaluación tendrás la oportunidad con tu grupo de escoger una de dos posibles alternativas:

## **Alternativa 1**

Realizarás una versión más elaborada de la experiencia de la Central Nuclear en la que trabajaste al final de la Unidad 1.  En este caso vas a realizar un sistema de aplicaciones interactivas que se comunicarán entre ellas, donde una aplicación correrá en el PC y la otra en el microcontrolador.

Los requisitos son los siguientes:

**La aplicación en el PC debe:**

- Interactuar con el usuario por medio de elementos de interfaz de usuario, tales como botones, cajas de texto, textos en pantalla, entre otros. Nota: Solo se debe usar la consola para depuración y no para interacción.
- Leer el estado de tres (3) variables de la aplicación del microcontrolador. Te proporciono algunas:
    - i) temperatura actual del cuarto
    - ii) presión del refrigerante
    - iii) nivel de agua
- La aplicación del PC deberá solicitar el valor y estado de las variables a través de una única instrucción y el microcontrolador debe reportar toda la información de las tres variables en un único mensaje… Ojo, no por separado, en una misma trama.
- Permitir configurar la velocidad a la cual cambiará la variable y si debe cambiar o no, como también, permitir definir el valor inicial de la variable.
- Además, en la interfaz se debe mostrar el tiempo para la activación y el tiempo de activación

**La aplicación en el microcontrolador debe:**

- Verificar si debe cambiar la variable y modificarla en tiempo real, siempre y cuando esté habilitada para cambiar. La función de cambio será simplemente aumentar en uno el valor previo a la velocidad especificada.
- Mantener un LED funcionando a una frecuencia de 1 Hz. El objetivo de este LED es que se pueda verificar de manera visual que la aplicación en el microcontrolador NUNCA se bloquea. Esto implica que la señal de activación se genera en el PC

De MANERA CREATIVA, defina cómo se visualizará el estado de las tres variables en la aplicación del PC. Dado que el requisito aquí es ser creativo, se espera que la representación de las variables que haga cada equipo sea ÚNICA. NO USES TEXTO en la interfaz de usuario para visualizar los valores.

## **Alternativa 2**

Define una experiencia que requiera interacción con variables físicas e impleméntala.  Revisa por favor con la profesora al iniciar la actividad evaluativa la pertinencia de esa idea bajo el contexto de la temática que se está evaluando

**La aplicación en el PC debe:**

- Interactuar con el usuario por medio de elementos de interfaz de usuario, tales como botones, cajas de texto, textos en pantalla, entre otros. Nota: Solo se debe usar la consola para depuración y no para interacción.
- Leer el estado de tres (3) variables de la aplicación del microcontrolador.
- La aplicación del PC deberá solicitar el valor y estado de las variables a través de una única instrucción y el microcontrolador debe reportar toda la información de las tres variables en un único mensaje… Ojo, no por separado, en una misma trama.
- Permitir configurar la velocidad a la cual cambiará la variable y si debe cambiar o no, como también, permitir definir el valor inicial de la variable.

**La aplicación en el microcontrolador debe:**

- Verificar si debe cambiar la variable y modificarla en tiempo real, siempre y cuando esté habilitada para cambiar. La función de cambio será simplemente aumentar en uno el valor previo a la velocidad especificada.
- Mantener un LED funcionando a una frecuencia de 1 Hz. El objetivo de este LED es que se pueda verificar de manera visual que la aplicación en el microcontrolador NUNCA se bloquea. Esto implica que la señal de activación se genera en el PC


© Derechos de autor 2023, Juan Franco. Revisión 42b38a74.
