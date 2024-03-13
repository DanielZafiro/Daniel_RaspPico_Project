### **Ejercicio 7: análisis del programa de prueba**

```cpp
void task1()
{
    // Definición de estados y variable de estado Dos posibles estados
    enum class Task1States
    {
        INIT,
        WAIT_TIMEOUT
    };
    static Task1States task1State = Task1States::INIT;

    // Definición de variables static (conservan su valor entre llamadas a task1)
    static uint32_t lastTime = 0;

    // Constante de intevalo cada 1000 milisegundos
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

        Serial.print("Task1States::WAIT_TIMEOUT\n"); //Imprimirá en el monitor serie

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

void setup() //como se inicializa
{
    task1();
}

void loop() //bucle
{
    task1();
}
```

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

## Solución

Basado en la documentación de Arduino
`millis()` Devuelve el numero de milisegudnos que pasaron desque que el dispositvio Arduino comenzó a correr el programa actual.

Syntax
`time = millis()`

Returns/Devuelve
Number of milliseconds passed since the program started. Data type: `unsigned long`

Ejemplo:
```cpp
unsigned long myTime; //variable global que almacena el tiempo en myTime

void setup() {
  Serial.begin(9600); // Velocidad de transmision de de 9600 baudios entre Raspberry Pi Pico y el dispos. conectado
}
void loop() {
  Serial.print("Time: "); // Imprime el texto predecesor "Time: "
  myTime = millis(); // Almacena en la variable myTime el tiempo en milisegundos transcurrido

  Serial.println(myTime); // Imprime el tiempo desde que el programa inició
  delay(1000);          // Espera un segundo  para no enviar cantidades de datos masivos 
}
```
este código crea un bucle que imprime el tiempo en milisegundos desde el inicio del programa en el Monitor Serie cada segundo. Esto es útil para monitorear el tiempo de ejecución y entender cómo se comporta el programa en términos temporales.

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/c177f9e1-00ae-4ad7-84c3-6b458b36613c)

utiliza la función `millis()` para medir el tiempo transcurrido desde que el programa comenzó a ejecutarse. Luego, imprime ese tiempo en milisegundos en el Monitor Serie cada segundo. 

1. **Declaración de Variable:**
   - `unsigned long myTime;`: Declara una variable global llamada `myTime` como tipo de datos `unsigned long` para almacenar el tiempo en milisegundos.

2. **Configuración Inicial (`setup`):**
   - `Serial.begin(9600);`: Inicia la comunicación serie a una velocidad de 9600 baudios. Esto permite la comunicación entre el Arduino y el Monitor Serie en la computadora.

3. **Bucle Principal (`loop`):**
   - `Serial.print("Time: ");`: Imprime el texto "Time: " en el Monitor Serie.
   - `myTime = millis();`: Almacena en la variable `myTime` el tiempo en milisegundos transcurrido desde que el programa comenzó a ejecutarse.
   - `Serial.println(myTime);`: Imprime el valor almacenado en `myTime` seguido por un salto de línea en el Monitor Serie. Esto muestra el tiempo en milisegundos desde que el programa se inició.
   - `delay(1000);`: Espera 1000 milisegundos (1 segundo) antes de repetir el bucle. Esto evita que el programa envíe grandes cantidades de datos al Monitor Serie en un corto período de tiempo.
  
En el codigo del ejercicio se inicializa con `Serial.begin(115200);` cosa que me parecio peculiar mientras que en la documentación de ARduino encontré que en el ejemplo de `millis()` usan una velocidad de transferrencia diferente: `Serial.begin(9600);` indagando encontré que, la elección del valor en `Serial.begin()` depende de varios factores, y no hay un valor único que sea siempre el más apropiado. La velocidad de comunicación (`baud rate`) determina la velocidad a la que los datos se transmiten entre el Arduino y el dispositivo conectado (como el Monitor Serie en la computadora). La elección del valor debe coincidir entre ambos dispositivos para garantizar una comunicación correcta.

En el caso de 
```
Serial.begin(9600);
```
Se selecciona una velocidad de 9600 baudios. Esta velocidad es comúnmente utilizada y es una elección adecuada para casos donde la velocidad máxima no es crítica, como en ejemplos sencillos o pruebas iniciales. En configuraciones básicas, como la transmisión de mensajes de estado o datos a una velocidad más baja, 9600 baudios es suficiente.

mientras que en el caso de
```
Serial.begin(115200);
```
Se selecciona una velocidad de 115200 baudios. Esta velocidad es más rápida en comparación con 9600 y es comúnmente utilizada en entornos donde se necesita transmitir datos a una velocidad más alta, como en la transferencia de datos más complejos o en entornos donde la velocidad de transmisión es un factor importante.

*Dato interesante:*

**La velocidad mínima y máxima** 

(baud rate) que se puede utilizar con Serial.begin() en un Arduino depende del modelo específico y de la frecuencia del microcontrolador. Sin embargo, en muchos modelos de Arduino, las velocidades típicas son las siguientes:

|           |             |
|-----------|-------------|
| Velocidad Mínima | La velocidad mínima comúnmente admitida es 300 baudios. Este es un valor bajo y se usa en situaciones donde la velocidad de transmisión no es crítica. |
| Velocidad Máxima | La velocidad máxima puede variar según el modelo, pero valores comunes incluyen 115200, 230400, 460800 e incluso 1000000 (1 Mbps). Estos valores más altos se utilizan cuando se necesita una transmisión de datos más rápida. |
