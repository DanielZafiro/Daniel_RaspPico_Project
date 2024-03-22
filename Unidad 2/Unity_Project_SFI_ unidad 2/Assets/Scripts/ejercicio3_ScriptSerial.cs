using System.Collections;
using System.Collections.Generic;
using UnityEngine; // declaramos que vamos a usar UnityEngine y su entorno
using System.IO.Ports; // declaramos que usaremos los puertos serie para comunicarnos con controladores 
using TMPro;

enum TaskState
{
    INIT,
    WAIT_START,
    WAIT_EVENTS
}

public class ejercicio3_ScriptSerial : MonoBehaviour // El nombre del archivo y de la clase ejercicio1_ScriptSerial y hereda la clase Monobehaviour de Unity para poderlo anexar en el GameObject
{
    private static TaskState taskState = TaskState.INIT;
    private SerialPort _serialPort;
    private byte[] buffer;
    public TextMeshProUGUI myText;
    private int counter = 0;

    void Start()
    {
        _serialPort = new SerialPort();
        _serialPort.PortName = "COM4";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable = true;
        _serialPort.Open();
        Debug.Log("Open Serial Port");
        buffer = new byte[128];
    }

    void Update()
    {
        myText.text = counter.ToString();
        counter++;

        switch (taskState)
        {
            case TaskState.INIT:
                taskState = TaskState.WAIT_START;
                Debug.Log("WAIT START");
                break;
            case TaskState.WAIT_START:
                if (Input.GetKeyDown(KeyCode.A))
                {
                    byte[] data = { 0x31 };// start
                    _serialPort.Write(data, 0, 1);
                    Debug.Log("WAIT EVENTS");
                    taskState = TaskState.WAIT_EVENTS;
                }
                break;
            case TaskState.WAIT_EVENTS:
                if (Input.GetKeyDown(KeyCode.B))
                {
                    byte[] data = { 0x32 };// stop
                    _serialPort.Write(data, 0, 1);
                    Debug.Log("WAIT START");
                    taskState = TaskState.WAIT_START;
                }
                if (_serialPort.BytesToRead > 0)
                {
                    int numData = _serialPort.Read(buffer, 0, 128);
                    Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
                }
                break;
            default:
                Debug.Log("State Error");
                break;
        }
    }
}
