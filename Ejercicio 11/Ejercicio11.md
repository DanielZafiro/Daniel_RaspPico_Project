### **Ejercicio 11: realiza algunas pruebas**

Ahora vas a probar ScriptCommunicator con el sistema de desarrollo.

Utiliza el siguiente programa:

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
            Serial.read();
            Serial.print("Hola computador\n");
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


## Solución

Subido el codigo proporcionado al controlador:

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/6788dda4-a735-4815-851f-583aa2e5f36e)

Probando la primera parte de la instrucción
![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/9d6e3e20-6a40-4efc-a3e1-c5e470aaee3a)

