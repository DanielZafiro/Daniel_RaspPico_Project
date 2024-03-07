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
Analizemos el programa:

En el estado INIT, se inicia la comunicación serial (`Serial.begin(115200)`) y luego la tarea pasa al estado WAIT_DATA.
1. Entonces una vez inicializado el programa este entra al estado de esperando datos, este solo devolverá el mensaje "Hola computador" si recibe un dato en este caso una tecla + enviar en el scriptcommunicator,
por lo tanto el evento que verifica si ha llegado algo por el puerto serial es el  `if (Serial.available() > 0)`  verifica si hay al menos un dato disponible en el puerto serial.

Si hay datos disponibles, la tarea lee un byte en este caso un codigo ASCII (`Serial.read()`) y luego imprime el mensaje `"Hola computador"` en el Monitor Serie mediante `Serial.print()`

   
```cpp
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
```

2. Tablas del punto:

señalé los valores en haxadecimal correspondiente a cada letra o entrada

![asciifull](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/14f21918-0cd0-4adf-bffd-7cd3dd14553f)

3. Este numero acompañado de la letra al final del mensaje, despues de la r, representa la función de "line feed" o salto de línea 

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/5f863abd-8e3b-4451-9458-eabb4c9f2727) -->
![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/4475cde3-a2ab-4702-91e9-b0a433203a6f) -->
![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/2350c1c0-3fa3-453e-92a6-731acfb69293)

5. El valor 0x0A en hexadecimal corresponde al carácter de nueva línea `\n`

4. La relación entre las letras y los números que devuelve el ScriptCommunicator está relacionada con la representación ASCII de los caracteres.

En el sistema ASCII (American Standard Code for Information Interchange), cada carácter se asigna a un número entero único. Cuando imprimes caracteres en el Monitor Serie, Arduino los envía como su representación ASCII. Aquí tienes una interpretación de tu salida:

- "H" tiene un valor ASCII de 72 (en hexadecimal: 0x48).
- "o" tiene un valor ASCII de 111 (en hexadecimal: 0x6F).
- "l" tiene un valor ASCII de 108 (en hexadecimal: 0x6C).
- "a" tiene un valor ASCII de 97 (en hexadecimal: 0x61).
- " " (espacio) tiene un valor ASCII de 32 (en hexadecimal: 0x20).
- "c" tiene un valor ASCII de 99 (en hexadecimal: 0x63).
- "o" tiene un valor ASCII de 111 (en hexadecimal: 0x6F).
- "m" tiene un valor ASCII de 109 (en hexadecimal: 0x6D).
- "p" tiene un valor ASCII de 117 (en hexadecimal: 0x75).
- "u" tiene un valor ASCII de 117 (en hexadecimal: 0x75).
- "t" tiene un valor ASCII de 116 (en hexadecimal: 0x74).
- "a" tiene un valor ASCII de 97 (en hexadecimal: 0x61).
- "d" tiene un valor ASCII de 100 (en hexadecimal: 0x64).
- "o" tiene un valor ASCII de 111 (en hexadecimal: 0x6F).
- "r" tiene un valor ASCII de 114 (en hexadecimal: 0x72).
- "\n" (nueva línea) tiene un valor ASCII de 10 (en hexadecimal: 0x0A).

6. Sí, tiene total sentido. Cuando se verifica si hay datos disponibles en el puerto serial mediante `Serial.available()`, es importante realizar una lectura (`Serial.read()`) para retirar esos datos del buffer del puerto serial. Si no se realiza la lectura, los datos seguirán estando en el buffer y la próxima vez que se llame a `Serial.available()`, se volverá a detectar que hay datos disponibles, incluso si son los mismos datos anteriores.

En el código, se esta realizando la lectura con `Serial.read()` cuando detecta que hay al menos un byte disponible en el puerto serial. Esto es una buena práctica para asegurarse de que el buffer se limpie y que siempre esté trabajando con datos recientes.

```cpp
if (Serial.available() > 0)
{
    Serial.read(); // Leer para retirar el dato del buffer
    Serial.print("Hola computador\n");
}
```

Esta línea `Serial.read()` asegura que, después de verificar que hay datos disponibles, se retire un byte del buffer, evitando así que el mismo dato se detecte repetidamente en futuras llamadas a `Serial.available()`.
