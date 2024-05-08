using UnityEngine;
using UnityEngine.UI;

public class TrackButtonController : MonoBehaviour
{
    public FullCode fullCode; // Reference to the FullCode script
    public int trackNumber; // The number of this track
    public MediaBarController mediaBarController; // Reference to the MediaBarController script

    private void Start()
    {
        // Get the Button component and attach the SelectTrack method to its onClick event
        var button = GetComponent<Button>();
        button.onClick.AddListener(SelectTrack);
    }

    private void SelectTrack()
    {
        // Call the SelectTrackSet method in the FullCode script with this button's track number
        fullCode.SelectTrackSet(trackNumber);

        // Call the OnTrackChanged method in the MediaBarController script
        mediaBarController.OnTrackChanged();
    }
}