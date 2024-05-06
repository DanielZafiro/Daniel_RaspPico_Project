using UnityEngine;
using UnityEngine.UI;
using TMPro; // Importa el espacio de nombres TMPro para usar el tipo TextMeshProUGUI


public class LightSwitch : MonoBehaviour
{
    public Light lampLight;
    public Button switchButton; 
    public TMP_Text buttonText; // Referencia al componente de texto de TextMeshPro

    bool isOn = true;

    void Start()
    {
        // Asignar la funci�n de toggle al bot�n
        switchButton.onClick.AddListener(ToggleLight);
    }

    void ToggleLight()
    {
        // Cambiar el estado del bombillo y actualizar el texto del bot�n
        isOn = !isOn;
        lampLight.enabled = isOn;
        buttonText.text = isOn ? "Apagar" : "Encender"; // Actualizar el texto del bot�n
    }
}
