# Unidad 1. Software para sistemas embebidos
# **Introducción**

En esta unidad vas a familiarizarte con el funcionamiento del computador (microcontrolador) que permite interactuar directamente con los actuadores y sensores de una aplicación interactiva que utiliza dispositivos externos.

En [este repositorio](https://classroom.github.com/a/QP2SvcME) implementarás los ejercicios del trayecto de actividades y de final de unidad.

### **Propósito de aprendizaje**

Aprenderás algunas técnicas de programación muy útiles para resolver problemas con sistemas de cómputo reactivos. Usarás estados, eventos y acciones.

## **Trayecto de actividades**

### **Ejercicios**

### **Ejercicio 1: introducción**

> [!IMPORTANT]
>
> RECUERDA LO QUE APRENDERÁS EN ESTE CURSO
>
> En este curso aprenderás a construir aplicaciones interactivas que integren y envíen información desde y hacia el mundo exterior.

¿Recuerdas que te mostré al iniciar el curso un trabajo de grado realizado por estudiantes del programa? Te voy a pedir que veas algunos segundos del video del DEMO de [este](https://tdaxis.github.io/demo.html) trabajo.

Déjame te hablo de nuevo de este sistema porque es un excelente resumen de lo que busco que aprendas con este curso.

La idea de la aplicación es VARIAR las visuales y el audio con la información del movimiento que se captura en tiempo real de una bailarina.

La imagen está dividida en 4 partes. En la esquina superior izquierda observarás   `LA APLICACIÓN INTERACTIVA` que está corriendo en un computador. Esta aplicación se encargará de proyectar las visuales que están en la esquina superior derecha y controlar el software de audio que está en la esquina inferior derecha. Observa la esquina inferior izquierda, allí verás una captura en tiempo real de los movimientos de una bailarina.

¿Cómo se captura este movimiento? Se hace por medio de unos dispositivos que te mostraré en estos videos:

- [Perception Neuron Trailer](https://youtu.be/v72P7q0sIXI).
- [Bailarina controlando un metahumano](https://youtu.be/pynCWHD8RPg).

Los dispositivos que llevan puestos las personas en los videos están compuestos por:

- Un sensor para medir el movimiento.
- Un computador embebido o microcontrolador que lee la información del sensor.
- Un radio de comunicación inalámbrica para transmitir la información leída.

La información se le entrega al computador que ejecuta la aplicación interactiva usando un `PROTOCOLO DE COMUNICACIÓN`. El protocolo es un acuerdo que se establece entre las partes involucradas en la comunicación de tal manera que ambas puedan entenderse.

¿Por qué te muestro todo esto?

Porque en este curso vamos a realizar un recorrido por los elementos que componen este tipo de aplicaciones.

En esta unidad vas a programar un microcontrolador similar al que tienen los dispositivos de captura de movimiento. En las unidades 2 y 3 vas experimentar con dos tipos de protocolos de comunicación. Finalmente, en la unidad 4 construirás una aplicación simple que integre todos los elementos y lo que aprendiste en las unidades previas.

**Advertencia**

ESTO ES MUY IMPORTANTE

Las aplicaciones que realizarás serán simples, PERO si lo analizas te darás cuenta que contienen todos los elementos necesarios para que entiendas cómo funcionan las aplicaciones que te mostré en los videos.

Los ejercicios de la unidad y del curso los desarrollarás en este repositorio.

**Nota**

Hay otro curso en el programa para seguir profundizando

En el plan de estudios de la carrera encontrarás otro curso llamado sistemas físicos interactivos 2. Es un curso de la línea de experiencias interactivas que puedes tomar como optativa del ciclo profesional si no estás en la línea de experiencias. En este curso vas a construir una aplicación usando todo lo que aprenderás en sistemas físicos interactivos 1. Mira por ejemplo [el proyecto](https://github.com/juanferfranco/RisitasCorp_Rider) que realizaron unos de tus compañeros.

### **Ejercicio 2: ¿Cómo funciona un microcontrolador?**

Un microcontrolador es un computador dedicado a ejecutar una aplicación específica para resolver un problema muy concreto. Por ejemplo, leer la información de un sensor y transmitir esa información a un computador.

En este curso vas a utilizar un sistema de desarrollo llamado [raspberry pi pico](https://www.raspberrypi.com/products/raspberry-pi-pico/) que cuenta con un microcontrolador que podrás programar.

### **Ejercicio 3: ¿Cómo puedes programar el microcontrolador?**

Para programar el microcontrolador vas a necesitar:

- Un editor de código de C++, por ejemplo arduino IDE.
- Varios programas que permitan transformar el código de C++ a instrucciones de máquina (compilador).
- Almacenar las instrucciones de máquina en la memoria flash del microcontrolador.

Sigue estos pasos:

- Descarga la versión .ZIP del IDE de arduino [versión 1.8.19](https://downloads.arduino.cc/arduino-1.8.19-windows.zip)
- Descomprime el archivo .ZIP
- Busca la carpeta donde está el archivo arduino.exe.
- Abre el programa arduino.exe.
- Sigue las instrucciones de la sección Installing via Arduino Boards Manager que encontrarás en [este](https://github.com/earlephilhower/arduino-pico#installing-via-arduino-boards-manager) repositorio.

Ahora vas a probar que puedes programar el raspberry pi pico:

- Conecta al computador el raspberry pi pico.
- En el menú Herramientas/Placa/Raspberry PI selecciona la tarjeta Raspberry Pi Pico.
- En el menú Herramientas/Puerto selecciona el puerto asignado por el sistema operativo al raspberry pi pico. Toma nota del nombre porque este mismo nombre lo usarás con otras aplicaciones (en mi caso es el COM5).

Ingresa el siguiente programa:

```cpp
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  static uint32_t previousTime = 0;
  static bool ledState = true;

  uint32_t currentTime = millis();

  if( (currentTime - previousTime) > 100){
    previousTime = currentTime;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }
}
```

Por último presiona el ícono Subir, el segundo ubicado en la esquina superior izquierda. Al hacer esto ocurrirán varias cosas:

- Se transformará el programa de código C++ a lenguaje de máquina.
- Se enviará el código de máquina del computador a la memoria flash del raspberry pi a través del puerto serial que el sistema operativo le asignó a la tarjeta.

Deberás ver el LED ubicado al lado del conectar USB enciendo y apagando muy rápido.

Si quieres practicar también en un entorno simulado te dejo [este](https://wokwi.com/) enlace.

### **Ejercicio 3a: retrieval practice (evaluación formativa)**

En este punto te voy a pedir que en la carpeta del ejercicio 3 coloques bajo control de versión el programa y practiques lo que estudiaste en la introducción de control de versión.

- Conforma tu equipo de trabajo (recuerda que el equipo es de dos o y tres personas, NO UNA).
- Únete al enlace que te compartí al principio de la página. Esto lo hace cada miembro del equipo.

**Advertencia**

MUY IMPORTANTE

DOS PERSONAS no pueden trabajar al mismo tiempo sobre el mismo archivo cuando el proyecto está bajo control de versión porque se crean conflictos, es decir, el sistema no sabe cuál de las dos versiones del archivo es la correcta.

- Ve a la terminal y clona el repositorio.
- Sube al repositorio local el archivo del ejercicio 3 en una carpeta con su nombre
- Envía el archivo al repositorio remoto
- Usa el mismo código del ejercicio, pero esta vez cambia el 100 por un 500. Observa el resultado de este cambio.
- Una vez termines el programa, lo veas funcionando y documentes el efecto del cambio, `DEBES cerrar el IDE de Arduino`.
- Regresa a la terminal. Realiza un commit con esta nueva versión del programa en la carpeta del ejercicio 3.
- Ahora añade el archivo README.md. Coloca el nombre del equipo, el nombre de los integrantes y el ID. Coloca en el archivo el resultado del cambio de 100 a 500. Describe lo que viste.
- Realiza un nuevo commit para incluir el archivo README.md con la documentación.
- Envía los cambios del repositorio local al remoto.

### **Ejercicio 4: retrieval practice (evaluación formativa)**

Recuerda que cada ejercicio lo trabajas en la carpeta que lleva su nombre dentro de tu repositorio de trabajo, en el enlace que hay al principio de esta página. Solo debes adicionar un archivo README.md con el nombre del equipo, integrantes y ID y un enlace a un repositorio `PÚBLICO` donde harás lo siguiente:

- Crea un proyecto para el raspberry pi.
- En el código modifica el 500 por 1000.
- Coloca el proyecto bajo control de versión.
- Sincroniza tu repositorio local con un repositorio público en Github. El enlace a este repositorio será el que coloques en el archivo README.md de la evaluación.

### **Ejercicio 5: documentación**

Para programar el raspberry pi pico tienes mucha documentación con información. Algunos sitios que pueden serte de utilidad son:

- [API de arduino](https://www.arduino.cc/).
- [Port para raspberry pi pico del API de arduino](https://arduino-pico.readthedocs.io/en/latest/#).
- [Sitio oficial del raspberry pi pico](https://www.raspberrypi.com/products/raspberry-pi-pico/).

En el archivo README.md de este ejercicio realiza por favor con tus palabras, preferiblemente a mano, un resumen de los elementos más importantes que identificaste en esta documentación. No olvides enviarla al repositorio remoto.

### **Ejercicio 6: caso de estudio**

Programa la siguiente aplicación en el raspberry y analiza su funcionamiento. Para descubrir lo que hace debes dar click en el ícono que queda en la esquina superior derecha (Monitor Serie). Los números que vez allí son enviados desde el microcontrolador al computador por medio del puerto USB.

```cpp
void task1()
{
    // Definición de estados y variable de estado
    enum class Task1States
    {
        INIT,
        WAIT_TIMEOUT
    };
    static Task1States task1State = Task1States::INIT;

    // Definición de variables static (conservan su valor entre llamadas a task1)
    static uint32_t lastTime = 0;

    // Constantes
    constexpr uint32_t INTERVAL = 1000;

    // MÁQUINA de ESTADOS
    switch (task1State)
    {
    case Task1States::INIT:
    {
        // Acciones:
        Serial.begin(115200);

        // Garantiza los valores iniciales para el siguiente estado.
        lastTime = millis();
        task1State = Task1States::WAIT_TIMEOUT;

        Serial.print("Task1States::WAIT_TIMEOUT\n");

        break;
    }
    case Task1States::WAIT_TIMEOUT:
    {
        uint32_t currentTime = millis();

        // Evento
        if ((currentTime - lastTime) >= INTERVAL)
        {
            // Acciones:
            lastTime = currentTime;
            Serial.print(currentTime);
            Serial.print('\n');
        }
        break;
    }
    default:
    {
        Serial.println("Error");
    }
    }
}

void setup()
{
    task1();
}

void loop()
{
    task1();
}
```

- ¿Cómo se ejecuta este programa?
- Pudiste ver este mensaje: `Serial.print("Task1States::WAIT_TIMEOUT\n");`. ¿Por qué crees que ocurre esto?
- ¿Cuántas veces se ejecuta el código en el case Task1States::INIT?

### **Ejercicio 7: análisis del programa de prueba**

Miremos algunos aspectos del programa:

- Los programas los dividiremos en tareas. En este caso solo tenemos una. Los programas más complejos tendrán muchas más.
- Este programa tiene un pseudo estado y un estado, pero desde ahora diremos que tiene 2 estados:
    
```cpp
enum class Task1States{
    INIT,
    WAIT_TIMEOUT
};
```
    
- ¿Qué son los estados? Son condiciones de espera. Son momentos en los cuales tu programa está esperando a que algo ocurra. En este caso en `Task1States::INIT` realmente no `ESPERAMOS` nada, por eso decimos que es un pseudo estado. Este estado SIEMPRE lo usaremos para configurar las condiciones INICIALES de tu programa.
- Nota cómo se pasa de un estado a otro:
    
```cpp
task1State = Task1States::WAIT_TIMEOUT;
```
    
- En el estado Task1States::WAIT_TIMEOUT estamos esperando a que ocurran un `EVENTO`. En este caso el evento lo identificamos mediante el `IF`. Por tanto, en un estado tu programa estará siempre preguntando por la ocurrencia de algunos eventos.
- Cuando la condición de un evento se produce entonces tu programa ejecuta ACCIONES. Por ejemplo aquí:
    
```cpp
lastTime = currentTime;
Serial.print(currentTime);
Serial.print('\n');
```

Si el evento 

```cpp
if ((currentTime - lastTime) >= INTERVAL) 
```
    
ocurre, el programa ejecutará las acciones.
    

La línea 

```cpp
Serial.print(currentTime)
```

te permite enviar mensaje por USB. Estos mensajes los puedes ver usando un programa como el Monitor Serie.

Observa la función 

```cpp
millis(); 
```

¿Para qué sirve? Recuerda que puedes buscar en [Internet](https://www.arduino.cc/reference/en/language/functions/time/millis/).

### **Ejercicio 8: retrieval practice (evaluación formativa)**

- Realiza un programa que envíe un mensaje al pasar un segundo, dos segundos y tres segundos. Luego de esto debe volver a comenzar.

En el README.md del repositorio responde:

- ¿Cuáles son los estados del programa?
- ¿Cuáles son los eventos?
- ¿Cuáles son las acciones?

### **Ejercicio 9: tareas concurrentes (evaluación formativa)**

Para sacar el máximo provecho a la CPU de tu microcontrolador lo ideal es dividir el problema en varias tareas que se puedan ejecutar de manera concurrente. La arquitectura de software que te voy a proponer es esta:

```cpp
void task1(){

}

void task2(){

}

void task3(){

}

void setup()
{
    task1();
    task2();
    task3();
}

void loop()
{
    task1();
    task2();
    task3();
}
```

Nota entonces que tu programa está dividido en tres tareas. La función setup se ejecuta una sola vez y ahí se llama por primera vez cada tarea. La función loop se ejecuta cada que las tareas terminan, es como un ciclo infinito.

Te voy a mostrar el código para la task1 y luego con tu equipo vas a construir las demás tareas. La frecuencia del mensaje será de 1 Hz

El objetivo es que hagas un programa donde tengas 3 tareas. La tarea 1 enviará un mensaje a 1 Hz., la tarea 2 a 0.5 Hz., la tarea 3 a 0.25 Hz.

Te voy a dejar como ejemplo el programa de una de las tareas. Te queda entonces el reto de realizar las otras tareas. No olvides sincronizar tu repositorio local con el remoto donde está la evaluación.

```cpp
void task1(){
    enum class Task1States{
        INIT,
        WAIT_FOR_TIMEOUT
    };

    static Task1States task1State = Task1States::INIT;
    static uint32_t lastTime;
    static constexpr uint32_t INTERVAL = 1000;

    switch(task1State){
        case Task1States::INIT:{
            Serial.begin(115200);
            lastTime = millis();
            task1State = Task1States::WAIT_FOR_TIMEOUT;
            break;
        }

        case Task1States::WAIT_FOR_TIMEOUT:{
            // evento 1:            uint32_t currentTime = millis();
            if( (currentTime - lastTime) >= INTERVAL ){
                lastTime = currentTime;
                Serial.print("mensaje a 1Hz\n");
            }
            break;
        }

        default:{
            break;
        }
    }

}

void setup()
{
    task1();
}

void loop()
{
    task1();
}
```

### **Ejercicio 10: monitor serial**

Para profundizar un poco más en el funcionamiento de los programas vas a usar una herramienta muy interesante llamada monitor o terminal serial. En este curso vas a utilizar ScriptCommunicator. La aplicación la puedes descargar de forma gratuita. Al instalarla en los computadores de la Universidad usa un directorio del usuario y deshabilita la creación de accesos directos en el escritorio y no asocies los archivos .js con ScriptCommunicator.

Para lanzar la aplicación abre el directorio donde la instalaste y lanza el programa ScriptCommunicator.exe

Ingresa al menu Settings, selecciona la pestaña serial port y elige el puerto (el puerto asignado por el sistema operativo a tu sistema de desarrollo) y el BaudRate a 115200. Los demás parámetros los puedes dejar igual.

Selecciona la pestaña console options y allí marca ÚNICAMENTE las opciones: utf8, receive, hex, mixed. En new line at byte coloca None y en Send on enter key coloca None.

En la pestaña serial port ve a la sección general, selecciona como current interface `serial port`. Cierra la ventana de configuración.

> [!IMPORTANT]
>
> No olvides que DEBES TENER conectado el sistema de desarrollo al computador para poder seleccionar el puerto correcto.

Para conectar ScriptCommunicator al microcontrolador, solo tienes que dar click en Connect y para desconectar Disconnect.

> [!WARNING]
> 
> ESTO ES CRÍTICO
>
> SOLO UNA APLICACIÓN puede comunicarse a la vez con el microcontrolador. Por tanto, SÓLO una aplicación puede abrir o conectarse al puerto serial que el sistema operativo le asigna al sistema de desarrollo.
>
> Esto quiere decir que no puedes programar el raspberry mientras tienes abierto ScriptCommunicator conectado al puerto serial.

### **Ejercicio 11: realiza algunas pruebas**

Ahora vas a probar ScriptCommunicator con el sistema de desarrollo.

Utiliza el siguiente programa:

```cpp
void task1(){
    enum class Task1States{
        INIT,
        WAIT_FOR_TIMEOUT
    };

    static Task1States task1State = Task1States::INIT;
    static uint32_t lastTime;
    static constexpr uint32_t INTERVAL = 1000;

    switch(task1State){
        case Task1States::INIT:{
            Serial.begin(115200);
            lastTime = millis();
            task1State = Task1States::WAIT_FOR_TIMEOUT;
            break;
        }

        case Task1States::WAIT_FOR_TIMEOUT:{
            // evento 1:            uint32_t currentTime = millis();
            if( (currentTime - lastTime) >= INTERVAL ){
                lastTime = currentTime;
                Serial.print("mensaje a 1Hz\n");
            }
            break;
        }

        default:{
            break;
        }
    }

}

void setup()
{
    task1();
}

void loop()
{
    task1();
}
```

Ahora abre ScriptCommunicator:

- Presiona el botón Connect.
- Selecciona la pestaña Mixed.
- Luego escribe una letra en la caja de texto que está debajo del botón `send`. Si quieres coloca la letra s.
- Al lado del botón send selecciona la opción utf8.
- Dale click a send.
- Deberías recibir el mensaje `Hola computador`.
- Nota que al final del mensaje hay un 0a ¿A qué letra corresponde?

Ahora PIENSA:

1. Analiza el programa. ¿Por qué enviaste la letra con el botón send? ¿Qué evento verifica si ha llegado algo por el puerto serial?
2. [Abre](https://www.asciitable.com/) esta tabla.
3. Analiza los números que se ven debajo de las letras. Nota que luego de la r, abajo, hay un número. ¿Qué es ese número?
4. ¿Qué relación encuentras entre las letras y los números?
5. ¿Qué es el 0a al final del mensaje y para qué crees que sirva?
6. Nota que luego de verificar si hay datos en el puerto serial se DEBE HACER UNA LECTURA del puerto. Esto se hace para retirar del puerto el dato que llegó. Si esto no se hace entonces parecerá que siempre tiene un datos disponible en el serial para leer. ¿Tiene sentido esto? Si no es así habla con el profe.

### **Ejercicio 12: punteros**

Vas a explorar un concepto fundamental de los lenguajes de programación C y C++. Se trata de los punteros. Para ello, te voy a proponer que escribas el siguiente programa. Para probarlo usa ScriptCommunicator.

```cpp
void task1()
{
    enum class Task1States    {
        INIT,
        WAIT_DATA
    };
    static Task1States task1State = Task1States::INIT;

    switch (task1State)
    {
    case Task1States::INIT:
    {
        Serial.begin(115200);
        task1State = Task1States::WAIT_DATA;
        break;
    }

    case Task1States::WAIT_DATA:
    {
        // evento 1:        // Ha llegado al menos un dato por el puerto serial? 
       if (Serial.available() > 0)
        {
            // DEBES leer ese dato, sino se acumula y el buffer de recepción 
            //del serial se llenará.   
		        Serial.read();
            uint32_t var = 0;

            // Almacena en pvar la dirección de var.      
			      uint32_t *pvar = &var;

            // Envía por el serial el contenido de var usando 
           // el apuntador pvar.    
            Serial.print("var content: ");
            Serial.print(*pvar);
            Serial.print('\n');

            // ESCRIBE el valor de var usando pvar   
            *pvar = 10;
            Serial.print("var content: ");
            Serial.print(*pvar);
            Serial.print('\n');
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
    task1();
}

void loop()
{
    task1();
}
```

¿No te está funcionando? No olvides que en un ESTADO siempre esperas eventos. Si estás enviando el evento?

La variable `pvar` se conoce como puntero. Simplemente es una variable en la cual se almacenan direcciones de otras variables. En este caso, en pvar se almacena la dirección de `var`. Nota que debes decirle al compilador el tipo de la variable (uint32_t en este caso) cuya dirección será almacenada en pvar.

Ejecuta el programa. Observa lo que hace. Ahora responde las siguientes preguntas mediante un ejercicio de ingeniería inversa:

- ¿Cómo se declara un puntero?
- ¿Cómo se define un puntero? (cómo se inicializa)
- ¿Cómo se obtiene la dirección de una variable?
- ¿Cómo se puede leer el contenido de una variable por medio de un puntero?
- ¿Cómo se puede escribir el contenido de una variable por medio de un puntero?

**Advertencia**

IMPORTANTE

No avances hasta que este ejercicio no lo tengas claro.

### **Ejercicio 13: punteros y funciones**

Vas a escribir el siguiente programa, pero antes de ejecutarlo vas a tratar de lanzar una HIPÓTESIS de qué hace. Luego lo vas a ejecutar y compararás el resultado con lo que creías. Si el resultado no es el esperado, no deberías seguir al siguiente ejercicio hasta que no experimentes y salgas de la duda.

```cpp
static void changeVar(uint32_t *pdata)
{
    *pdata = 10;
}

static void printVar(uint32_t value)
{
    Serial.print("var content: ");
    Serial.print(value);
    Serial.print('\n');
}

void task1()
{
    enum class Task1States    {
        INIT,
        WAIT_DATA
    };
    static Task1States task1State = Task1States::INIT;

    switch (task1State)
    {
    case Task1States::INIT:
    {
        Serial.begin(115200);
        task1State = Task1States::WAIT_DATA;
        break;
    }

    case Task1States::WAIT_DATA:
    {
        // evento 1:        // Ha llegado al menos un dato por el puerto serial?        
	if (Serial.available() > 0)
        {
            Serial.read();
            uint32_t var = 0;
            uint32_t *pvar = &var;
            printVar(*pvar);
            changeVar(pvar);
            printVar(var);
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
    task1();
}

void loop()
{
    task1();
}
```

### **Ejercicio 14: retrieval practice (evaluación formativa)**

Realiza un programa que intercambie mediante una función el valor de dos variables.

### **Ejercicio 15: punteros y arreglos**

Escribe el siguiente programa. `ANALIZA` qué hace, cómo funciona y qué necesitas para probarlo. No olvides revisar de nuevo una tabla ASCII. Para hacer las pruebas usa ScriptCommunicator y abre la pestaña Utf8.

```cpp
static void processData(uint8_t *pData, uint8_t size, uint8_t *res)
{

    uint8_t sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = sum + (pData[i] - 0x30);
    }
    *res = sum;
}

void task1()
{
    enum class Task1States    {
        INIT,
        WAIT_DATA
    };
    static Task1States task1State = Task1States::INIT;
    static uint8_t rxData[5];
    static uint8_t dataCounter = 0;

    switch (task1State)
    {
    case Task1States::INIT:
    {
        Serial.begin(115200);
        task1State = Task1States::WAIT_DATA;
        break;
    }

    case Task1States::WAIT_DATA:
    {
        // evento 1:        if (Serial.available() > 0)
        {
            rxData[dataCounter] = Serial.read();
            dataCounter++;
            if (dataCounter == 5)
            {
                uint8_t result = 0;
                processData(rxData, dataCounter, &result);
                dataCounter = 0;
                Serial.print("result: ");
                Serial.print(result);
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
    task1();
}

void loop()
{
    task1();
}
```

Piensa en las siguientes cuestiones:

- ¿Por qué es necesario declarar `rxData` static? y si no es static ¿Qué pasa? ESTO ES IMPORTANTE, MUCHO.
- dataCounter se define static y se inicializa en 0. Cada vez que se ingrese a la función loop dataCounter se inicializa a 0? ¿Por qué es necesario declararlo static?
- Observa que el nombre del arreglo corresponde a la dirección del primer elemento del arreglo. Por tanto, usar en una expresión el nombre rxData (sin el operador []) equivale a &rxData[0].
- En la expresión `sum = sum + (pData[i] - 0x30);` observa que puedes usar el puntero pData para indexar cada elemento del arreglo mediante el operador [].
- Finalmente, la constante `0x30` en `(pData[i] - 0x30)` ¿Por qué es necesaria?

**Truco**

ALERTA DE SPOILER

Con respecto a la pregunta anterior. Al enviar un carácter numérico desde ScriptCommunicator este se envía codificado, es decir, se envía un byte codificado en ASCII que representa al número. Por tanto, es necesario decodificar dicho valor. El código ASCII que representa los valores del 0 al 9 es respectivamente: 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39. De esta manera, si envías el `1` recibirás el valor 0x31. Si restas de 0x31 el 0x30 obtendrás el número 1.

Repite el ejercicio anterior pero esta vez usa la pestaña Mixed.

### **Ejercicio 16: análisis del api serial (investigación: hipótesis-pruebas)**

Qué crees que ocurre cuando:

- ¿Qué pasa cuando hago un [Serial.available()](https://www.arduino.cc/reference/en/language/functions/communication/serial/available/)?
- ¿Qué pasa cuando hago un [Serial.read()](https://www.arduino.cc/reference/en/language/functions/communication/serial/read/)?
- ¿Qué pasa cuando hago un Serial.read() y no hay nada en el buffer de recepción?
- Un patrón común al trabajar con el puerto serial es este:

```cpp
if(Serial.available() > 0){
    int dataRx = Serial.read()
}
```

- ¿Cuántos datos lee Serial.read()?
- ¿Y si quiero leer más de un dato? No olvides que no se pueden leer más datos de los disponibles en el buffer de recepción porque no hay más datos que los que tenga allí.
- ¿Qué pasa si te envían datos por serial y se te olvida llamar Serial.read()?

**Advertencia**

NO AVANCES SIN ACLARAR LAS PREGUNTAS ANTERIORES

Te pido que resuelvas las preguntas anteriores antes de avanzar. ES MUY IMPORTANTE.

### **Ejercicio 17: buffer de recepción**

Así se pueden leer 3 datos que han llegado al puerto serial:

```cpp
if(Serial.available() >= 3){
    int dataRx1 = Serial.read()
    int dataRx2 = Serial.read()
    int dataRx3 = Serial.read()
}
```

¿Qué escenarios podría tener en este caso?

```cpp
if(Serial.available() >= 2){
    int dataRx1 = Serial.read()
    int dataRx2 = Serial.read()
    int dataRx3 = Serial.read()
}
```

Para responder, es necesario que experimentes. ESTOS son los ejercicios que realmente te ayudarán a aprender.

### **Ejercicio 18: retrieval practice (evaluación formativa)**

Piense cómo podrías hacer lo siguiente:

- Crea una aplicación con una tarea.
- La tarea debe tener su propio buffer de recepción y una capacidad para 32 bytes.
- La tarea almacena los datos del serial en su propio buffer de recepción (el buffer será un arreglo).
- El buffer debe estar encapsulado en la tarea.
- Los datos almacenados en el buffer no se pueden perder entre llamados a la tarea.
- La tarea debe tener algún mecanismo para ir contando la cantidad de datos que han llegado. ¿Cómo lo harías?

Inventa un programa que ilustre todo lo anterior y en el archivo README.md escribe cómo solucionaste el problema.

# Trabajo final

En una experiencia un grupo terrorista llamado “Disedentes del tiempo” realizan la configuración de una central nuclear global con la que se realizará la emisión de radiación nuclear al mundo. El sistema utiliza una interfaz de usuario simulada mediante el puerto serial, implementada en un entorno de software de Arduino.

En esta configuración inicial el sistema inicia en modo de configuración, mostrando una vez el mensaje CONFIG. En este modo se le configura el tiempo para abrir la cámara, por defecto tiene 5 seg y puede configurarse  entre 1 y 40 segundos con los botones S(Subir) y B(Bajar) en pasos de 1 segundo. Tan pronto se ajuste el tiempo de apertura de la cámara se termina con la letra L (listo) y se observa la cuenta en una pantalla, al final de la cual se abre la cámara y se hace la emisión de la radiación.  Cuando la cuenta regresiva termine debe mostrarse el mensaje “RADIACIÓN NUCLEAR ACTIVA” y a los dos segundos pasar nuevamente al modo CONFIG.

La misión del participante de la experiencia es salvar el mundo, por lo cual debe descifrar con pistas e ingresar el código de acceso, para lo cual  se envía por el puerto serial la secuencia 'C' seguido de la clave numérica (por ejemplo, 'C1234'). Si ingresas la clave correcta debe aparecer el mensaje “SALVASTE AL MUNDO”, sino la cuenta regresiva debe continuar hasta el fatal desenlace.

Te dejo el siguiente material trabajado en clase como complemento a la información del trayecto de actividades.

[Presentación de sistemas embebidos](https://upbeduco-my.sharepoint.com/:b:/g/personal/vera_perez_upb_edu_co/EaIafHzSSxFOmAdXvPJzVxIBcPcu_KEhUCUu-k56LJJ4GQ?e=UVVPgY)
