using UnityEngine;
using UnityEngine.UI;

public class SkipButtonController : MonoBehaviour
{
    public MediaBarController mediaBarController; // Reference to the MediaBarController script

    private void Start()
    {
        // Get the Button component and attach the SkipTrack method to its onClick event
        var button = GetComponent<Button>();
        button.onClick.AddListener(SkipTrack);
    }

    private void SkipTrack()
    {
        // Call the SkipTrack method in the MediaBarController script
        mediaBarController.SkipTrack();
    }
}