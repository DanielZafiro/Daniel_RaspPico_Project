using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System.IO.Ports;
using UnityEngine.Serialization;

public class FullCode : MonoBehaviour
{
    public enum CurrentState
    {
        Setup,
        SelectTrack,
        SelectDuration,
        SelectVolume,
        Playing
    }

    [FormerlySerializedAs("_currentState")] public CurrentState currentState;
    [FormerlySerializedAs("_selectedTrack")] public string selectedTrack;
    [FormerlySerializedAs("_selectedVolume")] public int selectedVolume;
    private SerialPort _serialPort;

    public FullCode(SerialPort serialPort)
    {
        _serialPort = serialPort;
    }
    
    public void SelectTrackSet(int trackNumber)
    {
        selectedTrack = trackNumber.ToString();
        Debug.Log("Current track: " + selectedTrack);
    }

    public void SelectVolumeSet(int volumeNumber)
    {
        selectedVolume = volumeNumber;
        Debug.Log("Current volume: " + selectedVolume);
    }
    
    private void Start() 
    {
        _serialPort = new SerialPort();
        _serialPort.PortName = "COM3";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable = true;
        _serialPort.Open();
        Debug.Log("Open Serial Port");
    }

    private void Update()
    {
        switch (currentState)
        {
            case CurrentState.Setup:
                // Waiting for user input, no action needed
                break;
            case CurrentState.SelectTrack:
                // Waiting for user input, no action needed
                break;
            case CurrentState.SelectDuration:
                // Waiting for user input, no action needed
                break;
            case CurrentState.SelectVolume:
                // Waiting for user input, no action needed
                break;
            case CurrentState.Playing:
                // Waiting for user input, no action needed
                break;
        }
    }
}