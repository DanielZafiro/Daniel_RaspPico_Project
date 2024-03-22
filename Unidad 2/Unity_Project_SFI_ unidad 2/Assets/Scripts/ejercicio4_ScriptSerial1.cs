using System.Collections;
using System.Collections.Generic;
using UnityEngine; // declaramos que vamos a usar UnityEngine y su entorno
using System.IO.Ports; // declaramos que usaremos los puertos serie para comunicarnos con controladores 
using TMPro;

enum TaskState1
{
    INIT,
    WAIT_COMMANDS
}

public class ejercicio4_ScriptSerial : MonoBehaviour // El nombre del archivo y de la clase ejercicio1_ScriptSerial y hereda la clase Monobehaviour de Unity para poderlo anexar en el GameObject
{
    private static TaskState1 taskState = TaskState1.INIT;
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
        _serialPort.NewLine = "\n";
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
            case TaskState1.INIT:
                taskState = TaskState1.WAIT_COMMANDS;
                Debug.Log("WAIT COMMANDS");
                break;
            case TaskState1.WAIT_COMMANDS:
                if (Input.GetKeyDown(KeyCode.A))
                {
                    _serialPort.Write("ledON\n");
                    Debug.Log("Send ledON");
                }
                if (Input.GetKeyDown(KeyCode.S))
                {
                    _serialPort.Write("ledOFF\n");
                    Debug.Log("Send ledOFF");
                }
                if (Input.GetKeyDown(KeyCode.R))
                {
                    _serialPort.Write("readBUTTONS\n");
                    Debug.Log("Send readBUTTONS");
                }
                if (_serialPort.BytesToRead > 0)
                {
                    string response = _serialPort.ReadLine();
                    Debug.Log(response);
                }
                break;
            default:
                Debug.Log("State Error");
                break;
        }
    }
}
