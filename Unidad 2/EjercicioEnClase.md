# Actividad evaluativa antes de salir a semana santa

1. Comunicacion bidireccional con envio de datos c/3 segundos (2)
2. Interfaz grafica unity (2)
3. puesta a punto (1)

---

# Solución

- lo primero será decidir que quiero hacer
  se me ocurre hacer que el controlador sea un vehiculo (TREN) con una maquina de estados donde tengamos
  
  insertar llave al recibir "1"
  pasan 3 segundos
  encender TREN al recibir "2"
  pasan 3 segundos
  acelerar TREN al recibir "w"
  pasan 3 segundos
  frenar TREN al recibir "S"
  pasan 3 segundos
  
- lo segundo será establecer la comunicacion entre el controlador y el pc
- interfaz grafica en unity que en pantalla muestre el texto de las acciones
  intrucciones de botones para manejar el tren
  textos de las acciones



```cpp
void task()
{
    // Definición de los posibles estados de la tarea
    enum class TaskStates
    {
        INIT,         // Estado inicial
        INSERT_KEY,   // Insertar la llave
        START_TRAIN,  // Encender el tren
        ACCEL_TRAIN,  // Acelerar el tren
        BRAKE_TRAIN   // Frenar el tren
    };

    static TaskStates taskState = TaskStates::INIT; // Estado actual de la tarea
    static uint32_t previous = 0; // Variable para llevar el tiempo transcurrido

    // Switch-case para manejar los diferentes estados de la tarea
    switch (taskState)
    {
        case TaskStates::INIT:
        {
            // Inicialización de la comunicación serial
            Serial.begin(115200);
            // Pasar al estado de insertar la llave
            taskState = TaskStates::INSERT_KEY;
            break;
        }
        case TaskStates::INSERT_KEY:
        {
            // Esperar a que se reciba el comando "1" para insertar la llave
            if (Serial.available() > 0)
            {
                if (Serial.read() == '1')
                {
                    // Indicar que se ha insertado la llave y guardar el tiempo actual
                    Serial.print("Key inserted");
                    previous = millis();
                    // Pasar al estado de encender el tren
                    taskState = TaskStates::START_TRAIN;
                }
            }
            break;
        }
        case TaskStates::START_TRAIN:
        {
            // Esperar 3 segundos antes de encender el tren
            if (millis() - previous > 3000)
            {
                // Indicar que se ha encendido el tren y guardar el tiempo actual
                Serial.print("Train started");
                previous = millis();
                // Pasar al estado de acelerar el tren
                taskState = TaskStates::ACCEL_TRAIN;
            }
            break;
        }
        case TaskStates::ACCEL_TRAIN:
        {
            // Esperar 3 segundos antes de acelerar el tren
            if (millis() - previous > 3000)
            {
                // Indicar que se está acelerando el tren y guardar el tiempo actual
                Serial.print("Train accelerating");
                previous = millis();
                // Pasar al estado de frenar el tren
                taskState = TaskStates::BRAKE_TRAIN;
            }
            break;
        }
        case TaskStates::BRAKE_TRAIN:
        {
            // Esperar 3 segundos antes de frenar el tren
            if (millis() - previous > 3000)
            {
                // Indicar que se está frenando el tren y guardar el tiempo actual
                Serial.print("Train braking");
                previous = millis();
                // Regresar al estado inicial de insertar la llave para repetir el ciclo
                taskState = TaskStates::INSERT_KEY;
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
    // Llamar a la función task para iniciar la tarea
    task();
}

void loop()
{
    // Llamar a la función task en cada iteración del loop
    task();
}

```

```csharp
using UnityEngine;
using System.IO.Ports;
using TMPro;

// Enumeración de los posibles estados de la tarea
enum TaskState
{
    INIT,
    WAIT_INIT,
    WAIT_INSERT_KEY,
    WAIT_START_TRAIN,
    WAIT_ACCEL_TRAIN,
    WAIT_BRAKE_TRAIN,
    WAIT_EVENTS
}

public class Serial : MonoBehaviour
{
    private static TaskState taskState = TaskState.INIT;
    private SerialPort _serialPort;
    private byte[] buffer;

    public TextMeshProUGUI contador;
    public TextMeshProUGUI insertKey;
    public TextMeshProUGUI startTrain;
    public TextMeshProUGUI accelerateTrain;
    public TextMeshProUGUI brakeTrain;

    private int counter = 0;

    void Start()
    {
        // Inicialización del puerto serial
        _serialPort = new SerialPort();
        _serialPort.PortName = "COM3";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable = true;
        _serialPort.Open();
        Debug.Log("Open Serial Port");
        buffer = new byte[128];
    }

    void Update()
    {
        // Actualizar el contador en la interfaz gráfica
        contador.text = counter.ToString();
        counter++;

        // Manejar el estado actual de la tarea
        switch (taskState)
        {
            case TaskState.INIT:
                // No se realiza ninguna acción en este estado
                break;
            case TaskState.WAIT_INIT:
                // Esperar a que el controlador envíe una señal de inicialización
                if (_serialPort.BytesToRead > 0)
                {
                    // Leer el dato recibido del controlador
                    byte receivedData = (byte)_serialPort.ReadByte();
                    if (receivedData == '1')
                    {
                        // Cambiar al estado de esperar a que se inserte la llave
                        taskState = TaskState.WAIT_INSERT_KEY;
                        Debug.Log("Insert key...");
                    }
                }
                break;
            case TaskState.WAIT_INSERT_KEY:
                // Esperar a que se inserte la llave
                insertKey.text = "Waiting for key insertion...";
                if (_serialPort.BytesToRead > 0)
                {
                    // Leer el dato recibido del controlador
                    byte receivedData = (byte)_serialPort.ReadByte();
                    if (receivedData == '2')
                    {
                        // Cambiar al estado de esperar a que se encienda el tren
                        taskState = TaskState.WAIT_START_TRAIN;
                        Debug.Log("Start the train...");
                    }
                }
                break;
            case TaskState.WAIT_START_TRAIN:
                // Esperar a que se inicie el tren
                startTrain.text = "Waiting for train start...";
                if (_serialPort.BytesToRead > 0)
                {
                    // Leer el dato recibido del controlador
                    byte receivedData = (byte)_serialPort.ReadByte();
                    if (receivedData == '3')
                    {
                        // Cambiar al estado de esperar a que se acelere el tren
                        taskState = TaskState.WAIT_ACCEL_TRAIN;
                        Debug.Log("Accelerate the train...");
                    }
                }
                break;
            case TaskState.WAIT_ACCEL_TRAIN:
                // Esperar a que se acelere el tren
                accelerateTrain.text = "Waiting for train acceleration...";
                if (_serialPort.BytesToRead > 0)
                {
                    // Leer el dato recibido del controlador
                    byte receivedData = (byte)_serialPort.ReadByte();
                    if (receivedData == '4')
                    {
                        // Cambiar al estado de esperar a que se frene el tren
                        taskState = TaskState.WAIT_BRAKE_TRAIN;
                        Debug.Log("Brake the train...");
                    }
                }
                break;
            case TaskState.WAIT_BRAKE_TRAIN:
                // Esperar a que se frene el tren
                brakeTrain.text = "Waiting for train braking...";
                if (_serialPort.BytesToRead > 0)
                {
                    // Leer el dato recibido del controlador
                    byte receivedData = (byte)_serialPort.ReadByte();
                    if (receivedData == '5')
                    {
                        // Cambiar al estado de esperar nuevos eventos
                        taskState = TaskState.WAIT_EVENTS;
                        Debug.Log("Waiting for new events...");
                    }
                }
                break;
            case TaskState.WAIT_EVENTS:
                // Esperar a nuevos eventos
                break;
            default:
                Debug.Log("State Error");
                break;
        }
    }
}

```
