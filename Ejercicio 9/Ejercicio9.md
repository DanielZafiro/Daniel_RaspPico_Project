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


## Solución

Inicialmente entonces definí las otras dos tareas de esta manera:

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
                // evento 1:
                uint32_t currentTime = millis();
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

    void task2(){
        enum class Task2States{
            INIT,
            WAIT_FOR_TIMEOUT
        };
    
        static Task2States task2State = Task2States::INIT;
        static uint32_t lastTime;
        static constexpr uint32_t INTERVAL = 500;
    
        switch(task2State){
            case Task2States::INIT:{
                Serial.begin(115200);
                lastTime = millis();
                task2State = Task2States::WAIT_FOR_TIMEOUT;
                break;
            }
    
            case Task2States::WAIT_FOR_TIMEOUT:{
                // evento 2:
                uint32_t currentTime = millis();
                if( (currentTime - lastTime) >= INTERVAL ){
                    lastTime = currentTime;
                    Serial.print("mensaje a 0.25Hz\n");
                }
                break;
            }
    
            default:{
                break;
            }
        }
    
    }

    void task3(){
        enum class Task3States{
            INIT,
            WAIT_FOR_TIMEOUT
        };
    
        static Task3States task3State = Task3States::INIT;
        static uint32_t lastTime;
        static constexpr uint32_t INTERVAL = 250;
    
        switch(task3State){
            case Task3States::INIT:{
                Serial.begin(115200);
                lastTime = millis();
                task3State = Task3States::WAIT_FOR_TIMEOUT;
                break;
            }
    
            case Task3States::WAIT_FOR_TIMEOUT:{
                // evento 3:
                uint32_t currentTime = millis();
                if( (currentTime - lastTime) >= INTERVAL ){
                    lastTime = currentTime;
                    Serial.print("mensaje a 0.25Hz\n");
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
        task3();
        task2();
        
    }
    
    void loop()
    {
        task1();
        task3();
        task2();
    }
```
Y al compilar encontré con este error:
![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/6b25f599-2c1c-44b7-a75b-1318039a7713)

Esto ocurre porque 'currentTime' no ha sido declarado en este bloque y debe ser declarado antes de poder usarlo, y revisando el codigo éste sí esta implementado solo que quedo atrapado en el comentario del evento en la linea superior es un error que a cualquiera programando le puede pasar que comenta algo por error // evento 3:            uint32_t currentTime = millis();

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/6f0d5444-ffa8-4f5f-9493-e31205da75db)

Compilado y subido exitosamente asi es como se ve el programa:

https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/bcad736f-53e8-40d8-92ab-4ab780487b00

Funciona, pero no como deberia y revisando el codigo mas a fondo cometí un error en la consecusion de los eventos, no estan en orden
```cpp
    void setup()
    {
        task1();
        task3();
        task2();
        
    }
    
    void loop()
    {
        task1();
        task3();
        task2();
    }
```
lo que hace que el programa no alcance a realizar task3 por la rapides de task2

Con el codigo ya organizado:
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
                // evento 1:            
                uint32_t currentTime = millis();
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

        void task2(){
        enum class Task2States{
            INIT,
            WAIT_FOR_TIMEOUT
        };
    
        static Task2States task2State = Task2States::INIT;
        static uint32_t lastTime;
        static constexpr uint32_t INTERVAL = 500;
    
        switch(task2State){
            case Task2States::INIT:{
                Serial.begin(115200);
                lastTime = millis();
                task2State = Task2States::WAIT_FOR_TIMEOUT;
                break;
            }
    
            case Task2States::WAIT_FOR_TIMEOUT:{
                // evento 2:            
                uint32_t currentTime = millis();
                if( (currentTime - lastTime) >= INTERVAL ){
                    lastTime = currentTime;
                    Serial.print("mensaje a 0.5Hz\n");
                }
                break;
            }
    
            default:{
                break;
            }
        }
    
    }

        void task3(){
        enum class Task3States{
            INIT,
            WAIT_FOR_TIMEOUT
        };
    
        static Task3States task3State = Task3States::INIT;
        static uint32_t lastTime;
        static constexpr uint32_t INTERVAL = 250;
    
        switch(task3State){
            case Task3States::INIT:{
                Serial.begin(115200);
                lastTime = millis();
                task3State = Task3States::WAIT_FOR_TIMEOUT;
                break;
            }
    
            case Task3States::WAIT_FOR_TIMEOUT:{
                // evento 3:            
                uint32_t currentTime = millis();
                if( (currentTime - lastTime) >= INTERVAL ){
                    lastTime = currentTime;
                    Serial.print("mensaje a 0.25Hz\n");
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

este es el resultado:

https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/d1e47445-30cd-4cc2-88db-421447e55197

Me queda la duda de como hacer un diagrama de estados para este ejercicio
