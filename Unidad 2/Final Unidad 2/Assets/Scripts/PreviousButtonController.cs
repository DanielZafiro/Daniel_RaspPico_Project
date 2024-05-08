using UnityEngine;
using UnityEngine.UI;

public class PreviousButtonController : MonoBehaviour
{
    public MediaBarController mediaBarController; // Reference to the MediaBarController script

    private void Start()
    {
        // Get the Button component and attach the PreviousTrack method to its onClick event
        var button = GetComponent<Button>();
        button.onClick.AddListener(PreviousTrack);
    }

    private void PreviousTrack()
    {
        // Call the PreviousTrack method in the MediaBarController script
        mediaBarController.PreviousTrack();
    }
}