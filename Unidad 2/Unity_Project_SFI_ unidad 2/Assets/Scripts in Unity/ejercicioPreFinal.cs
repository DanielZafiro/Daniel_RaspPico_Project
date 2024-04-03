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

public class ejercicioPreFinal : MonoBehaviour
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
        _serialPort.PortName = "COM4";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable = true;

        try
        {
            _serialPort.Open();
            Debug.Log("Open Serial Port");
        }
        catch (System.Exception e) 
        {
            Debug.LogError("Failed to open serial port: " + e.Message);
        }
        buffer = new byte[128];
    }

    void Update()
    {
        // Actualizar el contador en la interfaz gráfica
        contador.text = counter.ToString();
        counter++;

        // Verificar si se ha presionado una tecla y mostrarla en la consola
        if (Input.anyKeyDown)
        {
            foreach (KeyCode keyCode in System.Enum.GetValues(typeof(KeyCode)))
            {
                if (Input.GetKeyDown(keyCode))
                {
                    // Debug.Log("Tecla presionada: " + keyCode);
                    int command = 0;
                    switch (keyCode)
                    {
                        case KeyCode.Alpha1:
                            command = 1;
                            break;
                        case KeyCode.Alpha2:
                            command = 2;
                            break;
                        case KeyCode.Alpha3:
                            command = 3;
                            break;
                        case KeyCode.Alpha4:
                            command = 4;
                            break;
                        case KeyCode.Alpha5:
                            command = 5;
                            break;
                        default:
                            Debug.Log("Tecla no reconocida: " + keyCode);
                            break;
                    }

                    // Enviar el comando al controlador
                    if (command != 0)
                    {
                        try
                        {
                            byte[] data = { (byte)command };
                            _serialPort.Write(data, 0, 1);
                            Debug.Log("Comando enviado al controlador: " + command);
                        }
                        catch (System.Exception e)
                        {
                            Debug.LogError("Error al enviar comando al controlador: " + e.Message);
                        }
                    }

                    break;
                }
            }
        }

        // Manejar el estado actual de la tarea
        switch (taskState)
        {
            case TaskState.INIT:
                // No se realiza ninguna acción en este estado
                taskState = TaskState.WAIT_INIT;
                Debug.Log("WAIT INIT");
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
