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
}

```

¿Funciona?

Por ejemplo, ¿Qué pasaría si al momento de ejecutar la instrucción `int numData = _serialPort.Read(buffer, 0, 20);` solo han llegado 10 de los 16 bytes del mensaje? ¿Cómo puede hacer tu programa para saber que ya tiene el mensaje completo? ¿Cómo se podría garantizar que antes de hacer la operación Read tenga los 16 bytes listos para ser leídos? Además, si los mensajes que envía el controlador tienen tamaños diferentes, ¿Cómo haces para saber que el mensaje enviado está completo o faltan bytes por recibir?

<aside>
  
💡 **Piensa antes de continuar…**

Por favor piensa antes de continuar e intenta dar respuesta a las preguntas plateadas. Sin embargo, no te preocupes, porque te voy a contar en un momento que puedes hacer para responderlas.

</aside>

<hr/>

## Solución


**Codigo #1**

```csharp
if (Input.GetKeyDown(KeyCode.A))
  {
    byte[] data = {0x31};// or byte[] data = {'1'};            
    _serialPort.Write(data,0,1);
    int numData = _serialPort.Read(buffer, 0, 20);
    Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
    Debug.Log("Bytes received: " + numData.ToString());
   }
```
¿Funciona?

https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/983f9e3c-f43e-4024-b55f-858641f305a9

No funciona como deberia,

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/1361e462-9177-4d46-b526-6bb4b2153899)

este codigo tiene un problema potencial de bloqueo en la ejecución del programa. Esto se debe a que el método `Read()` es una operación de bloqueo: si no hay datos disponibles para leer en el puerto serial, el programa se quedará esperando en la línea `int numData = _serialPort.Read(buffer, 0, 20);`, y mientras tanto, Unity no podrá procesar otros eventos de entrada o actualizaciones de la escena.



**Codigo #2**

```csharp
   if (Input.GetKeyDown(KeyCode.A))
   {
       byte[] data = { 0x31 };// or byte[] data = {'1'};
       _serialPort.Write(data, 0, 1);
   }

   if (_serialPort.BytesToRead > 0)
   {
       int numData = _serialPort.Read(buffer, 0, 20);
       Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
       Debug.Log("Bytes received: " + numData.ToString());
   }
```
https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/c8ddaa04-0bc3-4978-be4f-ead709208087

Con el segundo codigo el cambio principal es la adición de una verificación para determinar si hay datos disponibles para leer en el puerto serial antes de intentar leerlos. Esto se logra con la condición `if (_serialPort.BytesToRead > 0)` 

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/ba017d42-d1c8-438b-8728-9f15390c4b25)

se verifica si la propiedad `BytesToRead` del objeto `_serialPort` es mayor que cero. Esta propiedad devuelve el número de bytes disponibles para leer en el búfer de entrada del puerto serial en ese momento. Si hay datos disponibles para leer, el código procede a leer hasta 20 bytes del puerto serial en el buffer `buffer` y muestra la cadena decodificada de bytes en la consola de depuración de Unity, junto con la cantidad de bytes recibidos.

Esta adición asegura que el programa no intente leer del puerto serial si no hay datos disponibles para leer, evitando así que el código se bloquee o que intente leer datos vacíos del puerto serial.

> ¿Qué pasaría si al momento de ejecutar la instrucción `int numData = _serialPort.Read(buffer, 0, 20);` solo han llegado 10 de los 16 bytes del mensaje?

 La línea int numData = _serialPort.Read(buffer, 0, 20); indica que la función Read() intentará leer hasta 20 bytes del puerto serial y almacenarlos en el buffer buffer, si hay menos de 20 bytes disponibles en el buffer de entrada del puerto serial en el momento de la llamada a Read(), la función leerá tantos bytes como estén disponibles (hasta un máximo de 20) y los almacenará en el buffer

- `buffer`: Es el buffer donde se almacenarán los bytes leídos del puerto serial.
- `0`: Es el índice en el buffer donde comenzará a escribir los bytes leídos. En este caso, comienza desde el primer elemento del buffer.
- `20`: Es el número máximo de bytes que la función intentará leer del puerto serial en esta llamada.

En este caso, numData contendrá el número de bytes que realmente se leyeron, que en este caso sería 10. Los primeros 10 bytes del mensaje se almacenarían en el buffer `buffer` y los restantes 6 bytes seguirían pendientes en el buffer de entrada del puerto serial.

> ¿Cómo puede hacer tu programa para saber que ya tiene el mensaje completo? ¿Cómo se podría garantizar que antes de hacer la operación Read tenga los 16 bytes listos para ser leídos?

- **Delimitadores de mensajes**: podriamos utilizar un delimitador especial al final de cada mensaje enviado desde el controlador. Por ejemplo, enviar cada mensaje seguido de un carácter especial que indique el final del mensaje, como un carácter de nueva línea ('\n') o un carácter de retorno de carro ('\r'). En Unity, podríamos leer continuamente del puerto serial hasta que se encuentre este delimitador, lo que indicaría que hemos recibido el mensaje completo.

- **Longitud del mensaje conocida**: Si conocemos la longitud exacta de cada mensaje que se enviará desde el controlador, podria esperar a recibir esa cantidad de bytes antes de procesar el mensaje. Por ejemplo, si sabemos que cada mensaje tiene una longitud fija de 16 bytes, implementar un mecanismo para esperar hasta que se reciban todos los bytes antes de realizar la operación de lectura.

- **Temporizador de espera**: implementar un temporizador de espera para esperar un cierto período de tiempo después de recibir el último byte del mensaje antes de procesarlo. Si no se recibe ningún byte adicional durante este tiempo, podrías asumir que el mensaje está completo y listo para ser procesado. Si no se reciben todos los bytes dentro de este tiempo, se puede considerar que el mensaje está incompleto y se puede tomar una acción adecuada (como volver a intentar la lectura o mostrar un mensaje de error).

> Además, si los mensajes que envía el controlador tienen tamaños diferentes, ¿Cómo haces para saber que el mensaje enviado está completo o faltan bytes por recibir?

- buena pregunta
