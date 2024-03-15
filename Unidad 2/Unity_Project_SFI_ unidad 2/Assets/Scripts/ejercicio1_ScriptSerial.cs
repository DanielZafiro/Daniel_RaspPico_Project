using System.Collections;
using System.Collections.Generic;
using UnityEngine; // declaramos que vamos a usar UnityEngine y su entorno
using System.IO.Ports; // declaramos que usaremos los puertos serie para comunicarnos con controladores 

public class ejercicio1_ScriptSerial : MonoBehaviour // El nombre del archivo y de la clase ejercicio1_ScriptSerial y hereda la clase Monobehaviour de Unity para poderlo anexar en el GameObject
{
    private SerialPort _serialPort = new SerialPort(); // Se declara un objeto SerialPort llamado _serialPort
    private byte[] buffer = new byte[32]; // Se declara un buffer de bytes de tamaño 32

    void Start()
    {
        _serialPort.PortName = "COM9"; // Se establece el nombre del puerto serial a COM4 depende del puerto donde se conecte
        _serialPort.BaudRate = 115200; // Se establece la velocidad de baudios en 115200
        _serialPort.DtrEnable = true; // Se habilita la señal DTR
        _serialPort.Open(); // Se abre el puerto serial
        Debug.Log("Open Serial Port"); // Se imprime un mensaje en la consola indicando que el puerto serial se ha abierto
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.A)) // Si se presiona la tecla A
        {
            byte[] data = { 0x31 }; // Se crea un arreglo de bytes con el valor hexadecimal 0x31 (equivalente a '1' en ASCII)
            _serialPort.Write(data, 0, 1); // Se escribe el arreglo de bytes en el puerto serial
            Debug.Log("Send Data"); // Se imprime un mensaje en la consola indicando que se han enviado datos
        }

        if (Input.GetKeyDown(KeyCode.B)) // Si se presiona la tecla B
        {
            if (_serialPort.BytesToRead >= 16) // Si hay al menos 16 bytes disponibles para leer en el puerto serial
            {
                _serialPort.Read(buffer, 0, 20); // Se leen 20 bytes del puerto serial y se almacenan en el buffer
                Debug.Log("Receive Data"); // Se imprime un mensaje en la consola indicando que se han recibido datos
                Debug.Log(System.Text.Encoding.ASCII.GetString(buffer)); // Se imprime en la consola la cadena de texto correspondiente a los 20 bytes recibidos
            }
        }
    }
}