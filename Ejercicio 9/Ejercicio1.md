Ejercicio 9: tareas concurrentes (evaluación formativa)
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
