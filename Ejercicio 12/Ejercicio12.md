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
