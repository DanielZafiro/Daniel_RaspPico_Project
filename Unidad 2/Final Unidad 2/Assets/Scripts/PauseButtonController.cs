using UnityEngine;
using UnityEngine.UI;

public class PauseButtonController : MonoBehaviour
{
    public MediaBarController mediaBarController; // Reference to the MediaBarController script

    private void Start()
    {
        // Get the Button component and attach the Pause method to its onClick event
        var button = GetComponent<Button>();
        button.onClick.AddListener(Pause);
    }

    private void Pause()
    {
        // Call the Pause method in the MediaBarController script
        Debug.Log("Pause button clicked");
        mediaBarController.Pause();
    }
}