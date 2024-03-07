### **Ejercicio 18: retrieval practice (evaluación formativa)**

Piense cómo podrías hacer lo siguiente:

- Crea una aplicación con una tarea.
- La tarea debe tener su propio buffer de recepción y una capacidad para 32 bytes.
- La tarea almacena los datos del serial en su propio buffer de recepción (el buffer será un arreglo).
- El buffer debe estar encapsulado en la tarea.
- Los datos almacenados en el buffer no se pueden perder entre llamados a la tarea.
- La tarea debe tener algún mecanismo para ir contando la cantidad de datos que han llegado. ¿Cómo lo harías?

Inventa un programa que ilustre todo lo anterior y en el archivo README.md escribe cómo solucionaste el problema.

## Solución

En el proceso de ensayo y error reciclé codigo de los ejercicios anteriores y ejemplos para lograr concretar este codigo donde 
tiene una unica tarea que gestiona datos del puerto serial, 
los almacena en un buffer La cantidad de datos almacenados se muestra en cada iteración, 
y hay un manejo de desbordamiento si el buffer alcanza su capacidad máxima. La tarea se ejecuta en un bucle infinito

```cpp
const int BUFFER_SIZE = 32; // capacidad de almacenamiento 32 bytes
uint8_t taskBuffer[BUFFER_SIZE]; // Buffer para almacenar datos
uint8_t dataCounter = 0; // lleva la cuenta de la cantidad de datos almacenados en el buffer

enum class TaskStates
{
  INIT,
  WAIT_DATA
};

TaskStates taskState = TaskStates::INIT; // variable que indica el estado actual de la tarea, inicializada en INIT.

void processSerialData() // funcion para leer datos del puerto serial y almacenarlos en el buffer.
{
  // Verifica si hay datos disponibles en el puerto serial
  while (Serial.available() > 0)
  {
    // Lee un byte de datos del puerto serial
    uint8_t newData = Serial.read();

    // Almacena el dato en el buffer si hay espacio disponible
    if (dataCounter < BUFFER_SIZE)
    {
      taskBuffer[dataCounter] = newData;
      dataCounter++;
    } else
      {
      // Si el buffer está lleno, se puede implementar manejo de desbordamiento 
      Serial.println("Buffer lleno. Datos perdidos.");
      }
   }
}

void task1() // lógica principal de la tarea
{
  switch (taskState)
    {
    case TaskStates::INIT:
      // Inicialización de la tarea
      Serial.begin(115200);
      taskState = TaskStates::WAIT_DATA; // Cambia al estado de espera de datos
      break;

    case TaskStates::WAIT_DATA:
      // Procesa los datos del puerto serial
      processSerialData();

      // Muestra la cantidad de datos recibidos hasta ahora
      Serial.print("Cantidad de datos: ");
      Serial.println(dataCounter);

      delay(3000);  // Espera 3 segundos entre llamadas a la tarea
      break;

    default:
      break;
   }
}

void setup()
{
  task1(); // Llama a la tarea para la inicialización
}

void loop()
{
  task1(); // Llama a la tarea en el loop principal para que sea un buble infinito
}
```

https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/631021f0-3fe3-40fe-a2e7-acd411bfc8e0

> **Nota:** en el manejo de desboradamiento de datos no le agregué delay al mensaje para que fuera instantanea la respuesta de "Buffer lleno. Datos perdidos."
> solo bastaria agregar este codigo
> ```cpp
> else
>      {
>      // Si el buffer está lleno, se puede implementar manejo de desbordamiento 
>      Serial.println("Buffer lleno. Datos perdidos.");
>
>     delay(1000);
>      break; 
>      }
> 
> ```

paso a paso:

1. **Declaración de variables y estructuras:**
   ```cpp
   const int BUFFER_SIZE = 32; // Capacidad de almacenamiento 32 bytes
   uint8_t taskBuffer[BUFFER_SIZE]; // Buffer para almacenar datos
   uint8_t dataCounter = 0; // Contador de datos almacenados en el buffer
   ```

   - Se define la capacidad del buffer (`BUFFER_SIZE`) como 32 bytes
   - `taskBuffer` es un arreglo de bytes que actuará como el buffer para almacenar datos
   - `dataCounter` llevará la cuenta de la cantidad de datos almacenados en el buffer


2. **Declaración del estado de la tarea:**
   ```cpp
   enum class TaskStates
   {
     INIT,
     WAIT_DATA
   };

   TaskStates taskState = TaskStates::INIT;
   ```

   - Se declara un enumerador `TaskStates` que representa los estados posibles de la tarea (`INIT` y `WAIT_DATA`)
   - `taskState` es la variable que indica el estado actual de la tarea, inicializada en `INIT`

3. **Función `processSerialData()`:**
   ```cpp
   void processSerialData()
   {
     // Verifica si hay datos disponibles en el puerto serial
     while (Serial.available() > 0)
     {
       // Lee un byte de datos del puerto serial
       uint8_t newData = Serial.read();

       // Almacena el dato en el buffer si hay espacio disponible
       if (dataCounter < BUFFER_SIZE)
       {
         taskBuffer[dataCounter] = newData;
         dataCounter++;
       }
       else
       {
         // Si el buffer está lleno, se puede implementar manejo de desbordamiento 
         Serial.println("Buffer lleno. Datos perdidos.");
       }
     }
   }
   ```

   - La función `processSerialData` se encarga de leer datos del puerto serial y almacenarlos en el buffer
   - Utiliza un bucle `while` para leer todos los datos disponibles en el puerto serial
   - Verifica si hay espacio disponible en el buffer antes de almacenar cada dato
   - Si el buffer está lleno, imprime un mensaje indicando que se han perdido datos imprimiendo la cantidad maxima alcanzada

4. **Función `task1()`:**
   ```cpp
   void task1()
   {
     switch (taskState)
     {
     case TaskStates::INIT:
       // Inicialización de la tarea
       Serial.begin(115200);
       taskState = TaskStates::WAIT_DATA; // Cambia al estado de espera de datos
       break;

     case TaskStates::WAIT_DATA:
       // Procesa los datos del puerto serial
       processSerialData();

       // Muestra la cantidad de datos recibidos hasta ahora
       Serial.print("Cantidad de datos: ");
       Serial.println(dataCounter);

       delay(3000); // Espera 3 segundos entre llamadas a la tarea
       break;

     default:
       break;
     }
   }
   ```

   - La función `task1` implementa la lógica principal de la tarea
   - En el estado `INIT`, inicializa el puerto serial y cambia al estado `WAIT_DATA`
   - En el estado `WAIT_DATA`, llama a `processSerialData()` para manejar los datos del puerto serial
   - Muestra la cantidad de datos recibidos hasta el momento
   - Espera 3 segundos antes de realizar la próxima llamada a la tarea

5. **Funciones `setup()` y `loop()`:**
   ```cpp
   void setup()
   {
     task1(); // Llama a la tarea para la inicialización
   }

   void loop()
   {
     task1(); // Llama a la tarea en el loop principal para que sea un búcle infinito
   }
   ```

   - En el `setup`, se llama a la función `task1` para realizar la inicialización una unica vez
   - En el `loop`, se llama continuamente a la función `task1`, convirtiéndola en un bucle infinito

