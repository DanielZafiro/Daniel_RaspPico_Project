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

## Solución

Mi hipotesis viendo el codigo sin inicializarlo en el controlador esque hay una tarea la cual va a devolver dos valores diferentes para `var` y será algo como esto:

var content: 0

var content: 10

dado que una vez recibe un input del teclado en el scriptCommunicator se inicializa `var = 0` 
y luego se declara un puntero `*pvar` hacia la direccion del `var` el cual almacena la direccion de `var` en `pvar`
luego entra a la funcion `printVar(*pvar);` la cual imprime el valor actual de `var` que es `0`
para luego entrar cambiar ese valor en la funcion `changeVar(pvar);` donde adquiere un nuevo valor `10` declarado por un puntero `*pdata = 10;`
para finalmente imprimir el nuevo valor de `var = 10`

además veo que creo dos funciones por fuera (`static void printVar(uint32_t value) `y` static void changeVar(uint32_t *pdata)`)que en ejercicios anteriores se hacian dentro del mismo loop en cada `case`

Ahora veamos como funciona y si acaso funciona segun mi hipotesis:

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/4a4dba0e-c4ed-4a9e-8d03-599da33ecf9a)

var content: 0

var content: 10

conclusiones: sí estaba en lo correcto con analizar el codigo inicialmente
