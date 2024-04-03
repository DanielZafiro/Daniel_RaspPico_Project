using System.Collections;
using System.Collections.Generic;
using UnityEngine; // declaramos que vamos a usar UnityEngine y su entorno
using System.IO.Ports; // declaramos que usaremos los puertos serie para comunicarnos con controladores 
using TMPro;

public class ejercicio2_ScriptSerial : MonoBehaviour // El nombre del archivo y de la clase ejercicio1_ScriptSerial y hereda la clase Monobehaviour de Unity para poderlo anexar en el GameObject
{
    private SerialPort _serialPort = new SerialPort(); // Se declara un objeto SerialPort llamado _serialPort
    private byte[] buffer = new byte[32]; // Se declara un buffer de bytes de tamaño 32

    public TextMeshProUGUI myText;

    private static int counter = 0;


    void Start()
    {
        _serialPort.PortName = "COM4"; // Se establece el nombre del puerto serial a COM4 depende del puerto donde se conecte
        _serialPort.BaudRate = 115200; // Se establece la velocidad de baudios en 115200
        _serialPort.DtrEnable = true; // Se habilita la señal DTR
        _serialPort.Open(); // Se abre el puerto serial
        Debug.Log("Open Serial Port"); // Se imprime un mensaje en la consola indicando que el puerto serial se ha abierto
    }

    void Update()
    {
        myText.text = counter.ToString();
        counter++;

        if (Input.GetKeyDown(KeyCode.A))
        {
            byte[] data = { 0x31 };// or byte[] data = {'1'};
            _serialPort.Write(data, 0, 1);
        }
        if (_serialPort.BytesToRead > 0)
        {
            int numData = _serialPort.Read(buffer, 0, 20);
            Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
            Debug.Log("Bytes received: " + numData.ToString());
        }

    }
}
