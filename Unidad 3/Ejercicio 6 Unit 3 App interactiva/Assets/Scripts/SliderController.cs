using UnityEngine;
using UnityEngine.UI;
using System.IO.Ports; // Para la comunicación serial
using TMPro; // Importa el espacio de nombres TMPro para usar el tipo TextMeshProUGUI


public class SliderController : MonoBehaviour
{
    public Slider slider;
    public TextMeshProUGUI valueText;
    public Light lampLight;

    SerialPort serialPort;

    void Start()
    {
        // Inicializar el puerto serial
        serialPort = new SerialPort("COM4", 9600); 
        serialPort.Open();
    }

    void Update()
    {
        // Mostrar el valor del slider en el texto
        valueText.text = slider.value.ToString("F2");

        // Controlar la intensidad de la luz según la posición del slider
        float intensity = slider.value; // Suponiendo que el slider va de 0 a 1
        lampLight.intensity = intensity * 1; // 


        // Enviar el valor por el puerto serial
        float sliderValue = slider.value;
        serialPort.WriteLine(sliderValue.ToString("F2"));
    }

    void OnDestroy()
    {
        // Cerrar el puerto serial cuando el objeto se destruye
        if (serialPort != null && serialPort.IsOpen)
        {
            serialPort.Close();
        }
    }
}
