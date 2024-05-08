using UnityEngine;
using UnityEngine.UI;

public class PlayButtonController : MonoBehaviour
{
    public MediaBarController mediaBarController; // Reference to the MediaBarController script

    private void Start()
    {
        // Get the Button component and attach the Play method to its onClick event
        var button = GetComponent<Button>();
        button.onClick.AddListener(Play);
    }

    private void Play()
    {
        // Call the Play method in the MediaBarController script
        mediaBarController.Play();
    }
}