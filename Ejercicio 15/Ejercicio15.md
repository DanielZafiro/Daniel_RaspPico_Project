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

Aparentemente lo copie mal en el IDE

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
