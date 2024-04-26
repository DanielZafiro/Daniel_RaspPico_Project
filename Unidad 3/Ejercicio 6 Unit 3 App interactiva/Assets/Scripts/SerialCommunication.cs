using System.Collections;
using System.Collections.Generic;
using System.IO.Ports;
using UnityEngine;
using TMPro; // Importa el espacio de nombres TMPro para usar el tipo TextMeshProUGUI

public class SerialCommunication : MonoBehaviour
{
    SerialPort _serialPort = new SerialPort();
    public TextMeshProUGUI lampStateText; // Usa TextMeshProUGUI en lugar de Text

    void Start()
    {
        _serialPort.PortName = "COM4";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable = true;
        _serialPort.Open();
        Debug.Log("Open serial port");
    }

    public void SendBrightnessCommand(byte brightness)
    {
        byte[] data = { 0x01, brightness };
        _serialPort.Write(data, 0, data.Length);


        // Imprime los datos enviados a la consola
        Debug.Log("Sent brightness command: " + data[0].ToString("X2") + " " + data[1].ToString("X2"));
    }
    public void HandleBrightnessSliderValueChanged(float value)
    {
        // Convierte el valor del Slider (entre 0 y 1) a un valor de brillo entre 0 y 255
        byte brightness = (byte)(value * 255);
        SendBrightnessCommand(brightness);
    }
    void Update()
    {
        if (_serialPort.BytesToRead >= 4)
        {
            byte[] buffer = new byte[4];
            _serialPort.Read(buffer, 0, buffer.Length);
            string state = System.Text.Encoding.UTF8.GetString(buffer);
            lampStateText.text = "Lamp State: " + state;
        }
    }
}
