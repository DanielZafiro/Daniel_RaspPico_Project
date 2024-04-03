using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class ReproductorController : MonoBehaviour
{
    // Enumeración de los posibles estados del reproductor
    enum PlayerState
    {
        Off,
        On,
        Play,
        Pause,
        Stop,
        Forward,
        Rewind
    }

    private SerialPort serialPort;
    private PlayerState currentState = PlayerState.Off;

    // Tiempo entre cambios de estado (3 segundos)
    private float stateChangeTime = 3f;
    private float lastStateChangeTime = 0f;

    void Start()
    {
        // Inicialización del puerto serial
        serialPort = new SerialPort("COM4", 115200);
        serialPort.DtrEnable = true;

        try
        {
            serialPort.Open();
            Debug.Log("Puerto serial abierto correctamente.");
        }
        catch (System.Exception e)
        {
            Debug.LogError("Error al abrir el puerto serial: " + e.Message);
        }

        // Establecer el estado inicial del reproductor
        ChangeState(PlayerState.Off);
    }

    void OnDestroy()
    {
        // Cerrar el puerto serial cuando el objeto se destruye
        if (serialPort != null && serialPort.IsOpen)
        {
            serialPort.Close();
            Debug.Log("Puerto serial cerrado correctamente.");
        }
    }

    void Update()
    {
        // Verificar si ha pasado el tiempo suficiente para enviar el estado actual al controlador
        if (Time.time - lastStateChangeTime > stateChangeTime)
        {
            // Mostrar el estado actual del reproductor en la consola
            Debug.Log("Reproductor en " + currentState.ToString() + "...");

            // Actualizar el tiempo del último cambio de estado
            lastStateChangeTime = Time.time;
        }

        // Capturar la entrada del usuario y enviar el comando correspondiente al controlador
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            SendCommandToController("On");
            currentState = PlayerState.On;
        }
        else if (Input.GetKeyDown(KeyCode.Alpha0))
        {
            SendCommandToController("Off");
            currentState = PlayerState.Off;
        }
        else if (Input.GetKeyDown(KeyCode.Space))
        {
            SendCommandToController("Play");
            currentState = PlayerState.Play;
        }
        else if (Input.GetKeyDown(KeyCode.P))
        {
            SendCommandToController("Pause");
            currentState = PlayerState.Pause;
        }
        else if (Input.GetKeyDown(KeyCode.S))
        {
            SendCommandToController("Stop");
            currentState = PlayerState.Stop;
        }
        else if (Input.GetKeyDown(KeyCode.F))
        {
            SendCommandToController("Forward");
            currentState = PlayerState.Forward;
        }
        else if (Input.GetKeyDown(KeyCode.R))
        {
            SendCommandToController("Rewind");
            currentState = PlayerState.Rewind;
        }
    }


    // Método para cambiar manualmente el estado del reproductor
    void ChangeState(PlayerState newState)
    {
        currentState = newState;
        SendCommandToController(newState.ToString());
    }

    // Método para enviar comandos al controlador a través del puerto serial
    void SendCommandToController(string command)
    {
        try
        {
            serialPort.WriteLine(command);
            Debug.Log("Comando enviado al controlador: " + command);
        }
        catch (System.Exception e)
        {
            Debug.LogError("Error al enviar comando al controlador: " + e.Message);
        }
    }
}
