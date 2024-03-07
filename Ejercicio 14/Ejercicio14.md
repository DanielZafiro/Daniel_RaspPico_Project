### **Ejercicio 14: retrieval practice (evaluación formativa)**

Realiza un programa que intercambie mediante una función el valor de dos variables.

## Solución

### Primera forma de hacerlo

Declarando de manera explicita dentro del WAIT_DATA el valor intercambiado para las variables

1. **Inicialización de Estados:** El código utiliza una máquina de estados (`Task1States`) para gestionar el flujo del programa. Comienza en el estado `INIT` donde se inicia la comunicación serial y luego pasa al estado `WAIT_DATA`.

2. **Espera de Datos por Serial:** En el estado `WAIT_DATA`, verifica si hay datos disponibles en el puerto serial. Si es así, lee un byte (`Serial.read()`) para evitar la acumulación en el búfer.

3. **Trabajo con Punteros:** Declara dos variables (`var1` y `var2`) y dos punteros (`pvar1` y `pvar2`). Los punteros se inicializan con las direcciones de memoria de las variables correspondientes.

4. **Intercambio de Valores:** Muestra por el puerto serial los valores originales de las variables (`var1` y `var2`). Luego, intercambia los valores mediante los punteros (`*pvar1` y `*pvar2`).

5. **Resultado Final:** Muestra por el puerto serial los valores actualizados después del intercambio.

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
            // DEBES leer ese dato, sino se acumula y el buffer de recepción del serial se llenará.   
            Serial.read();

            uint32_t var1 = 5; // Declara la variable var1 inicializadad en 5
            uint32_t var2 = 25; // Declara la variable var2 inicializadad en 25

	    uint32_t *pvar1 = &var1; // Declara un puntero pvar1 que apunta a la direccion var1 y Almacena en pvar1 la dirección de var1
            uint32_t *pvar2 = &var2; // Declara un puntero pvar2 que apunta a la direccion var2 y Almacena en pvar2 la dirección de var2

            // Envía por el serial el contenido de var usando el apuntador pvar. 
            Serial.print("Antes del intercambio: x = ");
            Serial.print(*pvar1);
            Serial.print(", y = ");
            Serial.println(*pvar2);
            Serial.print('\n');

            *pvar1 = 25; // Escribir un nuevo valor en pvar1 mediante el puntero en este caso intercambiado
            *pvar2 = 5;

	    // Envía por el serial el contenido actualizado de var usando el apuntador pvar. 
            Serial.print("Despues del intercambio: x = ");
            Serial.print(*pvar1);
            Serial.print(", y = ");
            Serial.println(*pvar2);
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
![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/86434a2e-fc4b-4b98-8a57-614c40ec8796)


### Segunda forma de hacerlo

en este código se están utilizando punteros `a` y `b` que apuntan a las direcciones de memoria `&x` y `&y`, y se hace referencia a los valores de las variables `x` e `y` mediante `*a` y `*b`

```cpp
static void interchangeVar(uint32_t *a, uint32_t *b)
{
    uint32_t temp = *a;  // Se obtiene el valor apuntado por 'a' en este caso '&x' en el estado WAIT_DATA y se almacena en 'temp'
    *a = *b;            // Se asigna el valor apuntado por 'b' en este caso '&y' a la dirección apuntada por 'a' es decir está copiando el valor de 'y' en la variable que 'a' está apuntando, que es 'x'
    *b = temp;          // Se asigna el valor original de 'a' (guardado en 'temp') a la dirección apuntada por 'b' está copiando el valor original de 'x' en la variable que 'b' está apuntando, que es 'y'
}

static void printInterchange(uint32_t x, uint32_t y)
{
    Serial.print("intercambio: x = ");
    Serial.print(x);
    Serial.print(", y = ");
    Serial.println(y);
    Serial.print('\n');
}

void task1()
{
    enum class Task1States
    {
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
            uint32_t x = 5;
            uint32_t y = 25;
            printInterchange(x, y);
            interchangeVar(&x, &y);  // Se pasan las direcciones de memoria de 'x' y 'y' a la función
            printInterchange(x, y);
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

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/ae7f7b02-4069-4d6e-9577-2aad49db75e0)

mientras desarrollaba el codigo me encontré com este error error: expected primary-expression before 'x'
esto según la documentación es porque habia pegado la funcion completa donde esta declarandose la variable "x" y "y"
cuando en realidad aqui deberian de llamarse dado que ya estan declaradas entonces solo deberia de ponerse asi
`printInterchange(x, y);`

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/e9e0315e-0b1f-4e14-8d18-469b48814760)

Aqui se puede ver el codigo ya corregido, voy a probarlo en el scriptCommunicator y esto es lo que devuelve:

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/3433e8de-a9ca-4c26-ba3f-a88761288e9d)

intercambio: x = 5 , y = 25

intercambio: x = 25 , y = 5

### Tercera forma de hacerlo

Referenciando y trababajndo directamente con las variables

```cpp
static void interchangeVar(uint32_t &a, uint32_t &b)
{
    uint32_t temp = a;
    a = b;
    b = temp;
}

static void printInterchange(uint32_t x, uint32_t y)
{
    Serial.print("Intercambio: x = ");
    Serial.print(x);
    Serial.print(", y = ");
    Serial.println(y);
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
            uint32_t x = 5;
            uint32_t y = 25;
            printInterchange(x, y);
            interchangeVar(x, y);
            printInterchange(x, y);
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
