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
