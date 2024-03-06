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


## Solución

Este es el comportamiento del codigo visto desde el Monitor serie
La salida muestra el tiempo actual en milisegundos, y parece seguir un patrón donde se incrementa en 1000 milisegundos (1 segundo) en cada línea. 

https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/c41fde5b-1a89-4a4a-a7ec-b5b45ca9ee1e

Este código es un ejemplo de programación basada en máquinas de estados:
- La aplicación tiene una tarea (task1()) que se ejecuta repetidamente.
- Se utiliza una máquina de estados para gestionar diferentes estados y transiciones.
- La tarea mide el tiempo transcurrido y envía números al puerto serie a intervalos regulares.

Funcionamiento

1. **Enum `Task1States`:**
   - Define dos estados posibles: `INIT` y `WAIT_TIMEOUT`.
   - El estado inicial es `INIT`.

2. **Variables Estáticas:**
   - `task1State`: Almacena el estado actual de la máquina de estados.
   - `lastTime`: Almacena el tiempo de la última acción.

3. **Constantes:**
   - `INTERVAL`: Establece el intervalo de tiempo en milisegundos (1000 milisegundos = 1 segundo).

4. **Máquina de Estados (`switch`):**
   - **`INIT` Estado:**
     - Se ejecuta solo una vez al inicio.
     - Inicia la comunicación serie (`Serial.begin(115200)`).
     - Establece el tiempo inicial (`lastTime = millis()`).
     - Cambia al estado `WAIT_TIMEOUT` e imprime un mensaje en la consola.

   - **`WAIT_TIMEOUT` Estado:**
     - Comprueba si ha pasado el intervalo de tiempo especificado desde la última acción.
     - Si ha pasado el tiempo, imprime el tiempo actual en la consola.
     - No cambia de estado.

   - **`default` (Error):**
     - Se ejecuta si la máquina de estados se encuentra en un estado no definido.

5. **Setup y Loop:**
   - `setup()`: Inicia la máquina de estados llamando a `task1()` una vez al inicio.
   - `loop()`: Ejecuta la máquina de estados de forma continua en un bucle.

Salida Serial:

- La salida se envía al puerto serie (`Serial.print()`).
- En el estado `WAIT_TIMEOUT`, se imprimirá el tiempo actual en la consola(Monitor serie) cada vez que haya pasado el intervalo de tiempo especificado.

Conclusiones:

- El código establece un intervalo (`INTERVAL`) de 1000 milisegundos en la constante correspondiente.
- Se utiliza una máquina de estados para gestionar los diferentes estados del programa.
- El código está organizado y estructurado de manera clara.
- La tarea (`task1()`) se ejecuta continuamente en el bucle principal (`loop()`).
- En el estado `WAIT_TIMEOUT`, se verifica si ha pasado el intervalo de tiempo especificado desde la última acción.
- Si han pasado aproximadamente 1000 milisegundos desde la última acción, imprime el tiempo actual en milisegundos en el Monitor Serie.
- Los números en la salida representan el tiempo en milisegundos, y cada línea muestra un incremento de 1000 milisegundos.


1. **¿Cómo se ejecuta este programa?**
   - El programa utiliza una máquina de estados para controlar su ejecución. Al principio, se encuentra en el estado `INIT`. En este estado, se inicia la comunicación serie y se establecen valores iniciales. Luego, cambia al estado `WAIT_TIMEOUT`, donde permanece durante la ejecución continua del bucle principal (`loop()`). En el estado `WAIT_TIMEOUT`, verifica si ha pasado el intervalo de tiempo especificado y, si es así, imprime el tiempo actual en milisegundos en el Monitor Serie.

2. **¿Pudiste ver este mensaje: `Serial.print("Task1States::WAIT_TIMEOUT\n");`? ¿Por qué crees que ocurre esto?**
   - La línea `Serial.print("Task1States::WAIT_TIMEOUT\n");` está en el estado `INIT`, y se ejecuta solo una vez al inicio del programa, cuando la máquina de estados pasa de `INIT` a `WAIT_TIMEOUT`. Después de esa transición inicial, el programa permanece en el estado `WAIT_TIMEOUT`, donde imprime el tiempo actual en milisegundos. Por lo tanto, el mensaje solo se imprime una vez durante la inicialización.

3. **¿Cuántas veces se ejecuta el código en el case `Task1States::INIT`?**
   - El código en el caso `Task1States::INIT` se ejecuta una sola vez al inicio del programa, cuando la máquina de estados está en el estado `INIT`. Después de la ejecución de este caso, la máquina de estados cambia al estado `WAIT_TIMEOUT`, y no regresa al estado `INIT` durante la ejecución continua del programa en el bucle principal (`loop()`). Entonces el código en el caso `Task1States::INIT` se ejecuta una vez durante la inicialización del programa.
