### **Ejercicio 15: punteros y arreglos**

Escribe el siguiente programa. `ANALIZA` qué hace, cómo funciona y qué necesitas para probarlo. No olvides revisar de nuevo una tabla ASCII. Para hacer las pruebas usa ScriptCommunicator y abre la pestaña Utf8.

```cpp
static void processData(uint8_t *pData, uint8_t size, uint8_t *res)
{

    uint8_t sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = sum + (pData[i] - 0x30);
    }
    *res = sum;
}

void task1()
{
    enum class Task1States    {
        INIT,
        WAIT_DATA
    };
    static Task1States task1State = Task1States::INIT;
    static uint8_t rxData[5];
    static uint8_t dataCounter = 0;

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
        // evento 1:        if (Serial.available() > 0)
        {
            rxData[dataCounter] = Serial.read();
            dataCounter++;
            if (dataCounter == 5)
            {
                uint8_t result = 0;
                processData(rxData, dataCounter, &result);
                dataCounter = 0;
                Serial.print("result: ");
                Serial.print(result);
                Serial.print('\n');
            }
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

Piensa en las siguientes cuestiones:

- ¿Por qué es necesario declarar `rxData` static? y si no es static ¿Qué pasa? ESTO ES IMPORTANTE, MUCHO.
- dataCounter se define static y se inicializa en 0. Cada vez que se ingrese a la función loop dataCounter se inicializa a 0? ¿Por qué es necesario declararlo static?
- Observa que el nombre del arreglo corresponde a la dirección del primer elemento del arreglo. Por tanto, usar en una expresión el nombre rxData (sin el operador []) equivale a &rxData[0].
- En la expresión `sum = sum + (pData[i] - 0x30);` observa que puedes usar el puntero pData para indexar cada elemento del arreglo mediante el operador [].
- Finalmente, la constante `0x30` en `(pData[i] - 0x30)` ¿Por qué es necesaria?

**Truco**

ALERTA DE SPOILER

Con respecto a la pregunta anterior. Al enviar un carácter numérico desde ScriptCommunicator este se envía codificado, es decir, se envía un byte codificado en ASCII que representa al número. Por tanto, es necesario decodificar dicho valor. El código ASCII que representa los valores del 0 al 9 es respectivamente: 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39. De esta manera, si envías el `1` recibirás el valor 0x31. Si restas de 0x31 el 0x30 obtendrás el número 1.

Repite el ejercicio anterior pero esta vez usa la pestaña Mixed.

## Solución

De entrada al subir el codigo al controlador devuelve esto en el monitor serie

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/87f369b2-cb69-4c50-85dd-7c671bd78eb0)

Aparentemente lo copie mal en el IDE, no fue equivocación sin embargo en codigos anteriores no habia presentado ese problema sin embargo un compañero (Andres) me proporcionó una explicación de una manera de organizar mejor ese codigo dado que todo estaba dentro de la clase `void task1` cuando podria hacerse mas modular y legible si se sacan las variables `static` y la clase `enum class TaskStates` y al probarlo ya tiene un comportamiento estable.

```cpp
static void processData(uint8_t *pData, uint8_t size, uint8_t *res)
{
  uint8_t sum = 0;
  for(int i = 0; i < size; i++)
    {
     sum = sum + (pData[i] - 0x30);
    }
  *res = sum;
}

enum class Task1States
{
  INIT,
  WAIT_DATA
};

static Task1States task1State = Task1States::INIT;
static uint8_t rxData[5];
static uint8_t dataCounter = 0;

void task1()
{
  switch(task1State)
    {
    case Task1States::INIT:
        {
      Serial.begin(115200);
      task1State = Task1States::WAIT_DATA;
      break;
        }
    
    case Task1States::WAIT_DATA:
    {
      // Evento 1:

      if(Serial.available() > 0)
        {
        rxData[dataCounter] = Serial.read();
        dataCounter++;
        if(dataCounter == 5)
            {
              uint8_t result = 0;
              processData(rxData, dataCounter, &result);
              dataCounter = 0;
              Serial.print("result: ");
              Serial.print(result);
              Serial.print('\n');
            }
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
REvisemos que hace el cosdigo:

**Función `processData`:**
   ```cpp
   static void processData(uint8_t *pData, uint8_t size, uint8_t *res)
   {
      uint8_t sum = 0;
      for(int i = 0; i < size; i++)
      {
         sum = sum + (pData[i] - 0x30);
      }
      *res = sum;
   }
   ```
   - `processData`: Esta función toma un puntero a datos (`pData`), el tamaño de los datos (`size`), y un puntero al resultado (`res`). Itera a través de los datos y suma cada valor convertido a un número decimal (restando 0x30, que es el valor ASCII de '0'). El resultado se almacena en la dirección apuntada por `res`.

   - **Objetivo:** Esta función procesa un conjunto de datos (números en formato ASCII) y calcula la suma de los dígitos. Luego, almacena el resultado en la dirección de memoria apuntada por `res`.
   - **Parámetros:**
     - `uint8_t *pData`: Puntero al inicio de los datos.
     - `uint8_t size`: Tamaño de los datos.
     - `uint8_t *res`: Puntero para almacenar el resultado.

```cpp
enum class Task1States
{
  INIT,
  WAIT_DATA
};
```
- `Task1States`: Enumeración que define dos estados posibles para la máquina de estados (`INIT` y `WAIT_DATA`).

```cpp
static Task1States task1State = Task1States::INIT;
static uint8_t rxData[5];
static uint8_t dataCounter = 0;
```
- `task1State`, `rxData`, y `dataCounter`: Variables globales que mantienen el estado de la máquina (`task1State`), un búfer de datos de 5 elementos (`rxData`), y un contador de datos (`dataCounter`).

```cpp
void task1()
{
  switch(task1State)
    {
    case Task1States::INIT:
        {
      Serial.begin(115200);
      task1State = Task1States::WAIT_DATA;
      break;
        }
    
    case Task1States::WAIT_DATA:
    {
      // Evento 1:

      if(Serial.available() > 0)
        {
        rxData[dataCounter] = Serial.read();
        dataCounter++;
        if(dataCounter == 5)
            {
              uint8_t result = 0;
              processData(rxData, dataCounter, &result);
              dataCounter = 0;
              Serial.print("result: ");
              Serial.print(result);
              Serial.print('\n');
            }
        }
      break;
    }
      default:
            {
              break;
            }
      }
}
```
- `task1`: Función principal que implementa la máquina de estados.
  - **INIT**: Se inicializa la comunicación serial y se cambia al estado `WAIT_DATA`.
  - **WAIT_DATA**: Se verifica si hay datos disponibles en el puerto serial. Si hay, se lee un byte y se almacena en `rxData`, incrementando el contador `dataCounter`. Cuando se han recibido 5 bytes, se llama a `processData` con el búfer y se imprime el resultado. Luego, se reinicia `dataCounter`.

```cpp
void setup()
{
  task1();
}

void loop()
{
  task1();
}
```
- `setup` y `loop`: Ambas funciones simplemente llaman a `task1`. En un programa de Arduino típico, `setup` se ejecuta una vez al principio y `loop` se ejecuta repetidamente en un bucle infinito.



- ¿Por qué es necesario declarar `rxData` static? y si no es static ¿Qué pasa? 

La declaración de `rxData` como `static` en este contexto se realiza para que la variable conserve su valor entre llamadas a la función `task1`. Por qué se utiliza `static` y qué pasaría si no se utilizara:

1. **`static` en Variables Locales:**
   - Cuando una variable local se declara como `static` dentro de una función, significa que la variable conservará su valor entre llamadas a esa función.
   - En el código, `rxData` se declara como `static uint8_t rxData[5];`, lo que implica que la variable `rxData` mantendrá su contenido incluso después de salir de la función `task1`.

2. **Razón de Uso:**
   - Dado que `rxData` almacena datos recibidos a través del puerto serial (`Serial.read()`), es necesario conservar su valor entre llamadas a `task1`. Si no fuera `static`, la variable `rxData` se reiniciaría en cada llamada a `task1`, perdiendo los datos previamente almacenados.

3. **¿Qué Pasa si no es `static`?**
   - Si `rxData` no se declara como `static`, cada vez que se llame a `task1`, se crearía una nueva instancia de `rxData` y la variable se inicializaría nuevamente. Como resultado, no se mantendría ningún dato previamente almacenado, y el programa perdería la capacidad de acumular datos durante varias llamadas.

4. **Ejemplo sin `static`:**
   ```cpp
   void task1()
   {
      uint8_t rxData[5];  // Variable local sin static
    // Resto del código...
   }
   ```
   - En este caso, `rxData` se reinicializaría en cada llamada a `task1`, y los datos anteriores se perderían.

   
- dataCounter se define static y se inicializa en 0. Cada vez que se ingrese a la función loop dataCounter se inicializa a 0? ¿Por qué es necesario declararlo static?

La declaración static de dataCounter significa que la variable mantiene su valor entre llamadas a la función `task1`. En este caso, cuando `dataCounter` se declara `static`, conserva su valor incluso después de que la función `task1` haya terminado su ejecución. Esto es diferente de las variables locales normales, que se crean y destruyen cada vez que la función se llama.

Al inicializar dataCounter con el valor 0 fuera de la función, se garantiza que la variable comienza con ese valor cuando el programa comienza su ejecución. Después de eso, el valor de dataCounter se mantiene y se modifica durante la ejecución del programa, incluso cuando la función task1 se llama repetidamente en el bucle principal.

La elección de usar static en este caso depende de la necesidad de conservar el valor de dataCounter entre llamadas a task1. Si se declarara simplemente como una variable local sin el modificador static, se inicializaría a 0 cada vez que la función task1 se llamara, lo que podría no ser deseado en este contexto.

- Observa que el nombre del arreglo corresponde a la dirección del primer elemento del arreglo. Por tanto, usar en una expresión el nombre rxData (sin el operador []) equivale a &rxData[0].

Cuando se utiliza el nombre de un arreglo en una expresión sin el operador de corchetes ([]), este se convierte en un puntero al primer elemento del arreglo. Es decir, rxData sin corchetes es equivalente a &rxData[0].

- En la expresión `sum = sum + (pData[i] - 0x30);` observa que puedes usar el puntero pData para indexar cada elemento del arreglo mediante el operador [].

La expresión `pData[i]` es equivalente a `*(pData + i)`. En este contexto, `pData` actúa como un puntero al primer elemento del arreglo, y la expresión `pData[i]` accede al elemento en la posición `i` del arreglo.

La notación de corchetes (`[]`) es un atajo conveniente para trabajar con punteros y arreglos. La expresión `pData[i]` es semánticamente equivalente a `*(pData + i)`, donde `pData + i` representa la dirección de memoria del elemento en la posición `i` del arreglo.

En el contexto de la línea mencionada:

```cpp
sum = sum + (pData[i] - 0x30);
```

`pData[i]` se refiere al contenido del elemento en la posición `i` del arreglo `pData`. Esta expresión se utiliza para sumar cada elemento del arreglo después de restar `0x30` (48 en decimal), lo que sugiere que se está convirtiendo de caracteres ASCII a valores numéricos.

- Finalmente, la constante `0x30` en `(pData[i] - 0x30)` ¿Por qué es necesaria?

  La constante `0x30` en `(pData[i] - 0x30)` se utiliza para realizar una conversión de caracteres ASCII a valores numéricos. En el conjunto de caracteres ASCII, los dígitos numéricos del 0 al 9 tienen valores asociados que van desde `0x30` (48 en decimal) para '0' hasta `0x39` (57 en decimal) para '9'.

Cuando se trabaja con datos provenientes del puerto serial, los caracteres que representan dígitos numéricos se envían en forma de códigos ASCII. Restar `0x30` de un carácter ASCII que representa un dígito numérico convierte ese carácter en el valor numérico correspondiente.

Por ejemplo:

- Si `pData[i]` es el carácter '0' (cuyo valor ASCII es 48), entonces `(pData[i] - 0x30)` sería igual a `48 - 48`, resultando en `0`.
- Si `pData[i]` es el carácter '5' (cuyo valor ASCII es 53), entonces `(pData[i] - 0x30)` sería igual a `53 - 48`, resultando en `5`.


![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/6757fa85-da6b-448d-aec4-e5094ce21f87)

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/db624f61-3a24-47a2-8b34-4ba3a1fcccfa)


