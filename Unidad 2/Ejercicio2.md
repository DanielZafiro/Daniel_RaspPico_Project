### **Ejercicio 2: experimento**

<aside>
  
💡 **Advertencia:**

ESTE SEMESTRE CAMBIAMOS DE controlador (Arduino a RaspberryPi PICO).

Los videos que te mostraré utilizan un controlador y editor diferente para escribir los programas de este. NO HAY PROBLEMA. Puedes usar el mismo código para experimentar con el controlador que tienes ahora y con el IDE de Arduino.

</aside>

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

<aside>
  
💡 **Advertencia:**

Ojo con el puerto serial. Ten cuidado con el programa anterior. Particularmente, nota esta línea en el código escrito:

```csharp
 _serialPort.PortName = «COM3»;
```

En tu sistema operativo debes averiguar en qué puerto está el controlador y cómo se llama. En Windows se usa COMx, donde x es el número del puerto serial asignado por el sistema operartivo a tu controlador.


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

<aside>
  
💡 **MUY IMPORTANTE:**

¿Observas que la aplicación se bloquea? Este comportamiento es inaceptable para una aplicación interactiva de tiempo real. ¿Cómo se podría corregir este comportamiento?

</aside>

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

<aside>
  
💡 **Piensa antes de continuar…**

Por favor piensa antes de continuar e intenta dar respuesta a las preguntas plateadas. Sin embargo, no te preocupes, porque te voy a contar en un momento que puedes hacer para responderlas.

</aside>

<hr/>

## Solución
