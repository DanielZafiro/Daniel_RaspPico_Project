# **Introducción**

Llegaste al final del curso. En esta unidad aplicarás todos los conceptos que has aprendido para la construcción de aplicaciones interactivas que integren sistemas embebidos con plataformas de cómputo interactivas.

### **Propósito de aprendizaje**

Aplicar los conceptos y procedimientos aprendidos en el curso para resolver un problema que requiera la integración de una plataforma de tiempo real con un sistema microcontrolado.

# **Trayecto de actividades**

### **Ejercicios**

### **Ejercicio 1: caso de estudio-plugin Ardity**

Lo primero que te propondré es que pongas a funcionar el demo del plugin. Todo lo relacionado con el plugin estará en [este](https://github.com/DWilches/Ardity) repositorio. Comienza leyendo el archivo README.md.

Cuando te sientas listo para comenzar a experimentar ten presente que la versión de Unity con la cual se realizó el proyecto fue la 2018.2.  Abre el proyecto con tu versión de Unity.

¿Por dónde comienzo? Ve a la carpeta Scenes y comienza a analizar cada una de las escenas DemoScene. Son en total 5. En uno de los ejercicios que vienen vamos a analizar juntos la scene DemoScene_UserPoll_ReadWrite. Tu debes decidir luego con cuál scene trabajar y tratar de analizarla a fondo tal como lo haremos a continuación.

<aside>
💡 **Advertencia**

</aside>

<aside>
💡 No te desesperes…Piensa en esta unidad como la oportunidad de realizar un ejercicio de retrieval practice y aclarar algunos vacíos conceptuales que aún tengas. Esta unidad requiere analizar a fondo y ser autocrítico, así que trabaja con calma si es necesario para que el proceso de aprendizaje logre ser más profundo, llenando los vacíos conceptuales que aún tengas. No hay ningún problema en utilizar las herramientas disponibles en el medio, porque luego requerirás utilizar ese aprendizaje en el trabajo final.

</aside>

### **Ejercicio 2: concepto de hilo**

Observa y analiza [este](https://youtu.be/5wpSidCEJn4) video donde te explicarán rápidamente el concepto de hilo.

Te voy a pedir que veas [este](https://youtu.be/nv1NUR-qjcU) video corto de 15 minutos donde verás aplicado el concepto de hilo y por qué es necesario.

Ahora, no te voy a pedir que hagas lo siguiente ya, claro, a menos que seas una persona muy curiosa y además tengas tiempo. En [este](https://learn.microsoft.com/en-us/dotnet/standard/threading/managed-threading-basics) sitio puedes profundizar sobre el concepto de hilo.

### **Ejercicio 3: análisis del plugin**

Ahora, vamos a analizar más detalladamente una de las escenas demo de Ardity: DemoScene_UserPoll_ReadWrite

Primero, vamos a analizar rápidamente el código de arduino (para un protocolo ASCII):

```csharp
uint32_t last_time = 0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
	// Print a heartbeat
	if ( (millis() - last_time) >  2000)
    {
        Serial.print("Arduino is alive!!");
        Serial.print('\n');
        last_time = millis();
    }

// Send some message when I receive an 'A' or a 'Z'.
switch (Serial.read())
    {
			case 'A':
            Serial.print("That's the first letter of the abecedarium.");
            Serial.print('\n');
						break;
			case 'Z':
            Serial.print("That's the last letter of the abecedarium.");
            Serial.print('\n');
						break;
    }
}
```


¿Recuerdas en la unidad 2 para qué hacemos esto? ¿Podrías desde ahora predecir qué tipo de protocolo utilizará este demo (ASCII o binario)? 

Ahora analicemos la parte de Unity/Ardity. Para ello, carguemos una de las escenas ejemplo: DemoScene_UserPoll_ReadWrite

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/64db7bbf-cd48-4fd8-a108-7eaa41984785)


Veamos el gameObject SampleUserPolling_ReadWrite. Este gameObject tiene dos components, un transform y un script. El script tiene el código como tal de la aplicación del usuario.

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/b669644d-c625-4a56-ad37-9b8d6f4606d9)


Nota que el script expone una variable pública: serialController. Esta variable es del tipo SerialController.

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/45db0c9d-c7fd-4ea4-b048-24677437d505)


Esa variable nos permite almacenar la referencia a un objeto tipo SerialController. ¿Donde estaría ese objeto? Pues cuando el gameObject SerialController es creado nota que uno de sus componentes es un objeto de tipo SerialController:

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/0c92a893-41a8-412f-8654-d97d4fbcf3f9)


Entonces desde el editor de Unity podemos arrastrar el gameObject SerialController al campo SerialController del gameObject SampleUserPolling_ReadWrite y cuando se despliegue la escena, automáticamente se inicializará la variable serialController con la referencia en memoria al objeto SerialController:

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/384c3ca6-b589-4c05-85ff-5b352f5fd955)


De esta manera logramos que el objeto SampleUserPolling_ReadWrite tenga acceso a la información del objeto SerialController.

Observemos ahora qué datos y qué comportamientos tendría un objeto de tipo SampleUserPolling_ReadWrite:

```csharp
/** 
* Ardity (Serial Communication for Arduino + Unity) 
* Author: Daniel Wilches <dwilches@gmail.com> 
* 
* This work is released under the Creative Commons Attributions license. 
* https://creativecommons.org/licenses/by/2.0/ 
*/

usingUnityEngine;
usingSystem.Collections;

/** 
* Sample for reading using polling by yourself, and writing too. 
*/
publicclassSampleUserPolling_ReadWrite : MonoBehaviour
{
	public SerialController serialController;

// Initialization
void Start()
    {
        serialController = GameObject.Find("SerialController").GetComponent<SerialController>();

        Debug.Log("Press A or Z to execute some actions");
    }

// Executed each frame
void Update()
    {
//---------------------------------------------------------------------
// Send data
//---------------------------------------------------------------------

// If you press one of these keys send it to the serial device. A
// sample serial device that accepts this input is given in the README.
if (Input.GetKeyDown(KeyCode.A))
        {
            Debug.Log("Sending A");
            serialController.SendSerialMessage("A");
        }

if (Input.GetKeyDown(KeyCode.Z))
        {
            Debug.Log("Sending Z");
            serialController.SendSerialMessage("Z");
        }


//---------------------------------------------------------------------
// Receive data
//---------------------------------------------------------------------        

string message = serialController.ReadSerialMessage();

if (message ==null)
		return;

// Check if the message is plain data or a connect/disconnect event.
if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_CONNECTED))
            Debug.Log("Connection established");
else if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_DISCONNECTED))
            Debug.Log("Connection attempt failed or disconnection detected");
else            Debug.Log("Message arrived: " + message);
    }
}
```

Piensa en el diseño de una prueba de esto y ejecútala…

Te voy a ayudar a realizar la prueba. Pero antes configuremos el puerto serial en el cual está conectado el arduino. El arduino ya debe estar corriendo el código que te mostré al comienzo.

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/92aa2c09-f11b-4bd2-9fa7-21f128b08520)


En este caso el puerto es COM4.

Corre el programa, abre la consola y selecciona la ventana Game del Editor de Unity. Con la ventana seleccionada (click izquierdo del mouse), escribe las letras A y Z. Notarás los mensajes que aparecen en la consola:

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/c1714041-4c16-4d87-ba37-0cd40d90ec94)

<aside>
🙄 No te funciona?  Por favor revisa nuevamente el archivo README.md del proyecto.  En especial la parte relacionada con el DTR.

</aside>

Aún no logras resolverlo?  Por favor utiliza entonces [este paquete](https://github.com/VeraPerez/ardity_package_update.git) que ya tiene la adaptación del DTR para que no tengas inconvenientes en el proceso de comunicación. 

Una vez la aplicación funcione nota algo en el código de SampleUserPolling_ReadWrite:

```csharp
serialController = GameObject.Find("SerialController").GetComponent<SerialController>();
```

Comenta esta línea y corre la aplicación de nuevo. Funciona?

Ahora, elimina el comentario de la línea y luego borra la referencia al SerialController en el editor de Unity:

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/ece8ab53-28bc-4d60-8baa-f108bc644e12)

Corre de nuevo la aplicación.

- ¿Qué puedes concluir?
- ¿Para qué incluyó esta línea el autor del plugin?

Ahora analicemos el código del método Update de SampleUserPolling_ReadWrite:

```csharp
// Executed each framevoid Update()
{
  .
  .
  .
  serialController.SendSerialMessage("A");
  .
  .
  .
  string message = serialController.ReadSerialMessage();
  .
  .
  .
}
```

¿Recuerdas cada cuánto se llama el método Update?

Update se llama en cada frame. Lo llama automáticamente el motor de Unity

Nota los dos métodos que se resaltan:

```csharp
serialController.SendSerialMessage("A");
string message = serialController.ReadSerialMessage();
```

Ambos métodos se llaman sobre el objeto cuya dirección en memoria está guardada en la variable serialController.

El primer método permite enviar la letra A y el segundo permite recibir una cadena de caracteres.

- ¿Cada cuánto se envía la letra A o la Z?
- ¿Cada cuánto leemos si nos llegaron mensajes desde el arduino?

Ahora vamos a analizar cómo transita la letra A desde el SampleUserPolling_ReadWrite hasta el arduino.

Para enviar la letra usamos el método SendSerialMessage de la clase SerialController. Observa que la clase tiene dos variables protegidas importantes:

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/c2be31e4-1c4e-432f-8406-8b8f8a1c9519)

```csharp
protected Thread thread;
protected SerialThreadLines serialThread;
```

Con esas variables vamos a administrar un nuevo hilo y vamos a almacenar una referencia a un objeto de tipo SerialThreadLines.

En el método onEnable de SerialController tenemos:

```csharp
serialThread =new SerialThreadLines(portName, baudRate, reconnectionDelay, maxUnreadMessages);
thread =new Thread(new ThreadStart(serialThread.RunForever));
thread.Start();
```
