using UnityEngine;
using UnityEngine.UI;

public class MediaBarController : MonoBehaviour
{
    public FullCode fullCode; // Reference to the FullCode script
    public Slider mediaBar; // Reference to the Slider component
    public float selectedDuration; // The selected duration
    public int skipTrackCount; // The number of tracks to skip
    public int skipVolumeCount; // The number of volume levels to skip

    private float _currentTime; // The current time of the track
    private bool _isPlaying; // Whether the media bar is playing or paused
    private bool _isPaused;

    private void Start()
    {
        // Set the maximum value of the Slider to the selected duration
        mediaBar.maxValue = selectedDuration;
        _isPlaying = false; // Initially set isPlaying to false
        _isPaused = true;
    }

    private void Update()
    {
        // Only update the current time and the Slider's value if isPlaying is true
        if (_isPlaying)
        {
            _isPaused = false;
            // Update the current time and the Slider's value
            _currentTime += Time.deltaTime;
            mediaBar.value = _currentTime;

            // If the current time reaches the selected duration, start the next track and increase the volume
            if (_currentTime >= selectedDuration)
            {
                SkipTrack();
            }
        }
        else
        {
            // If a track has been selected and is not empty, and the volume level is greater than or equal to 0, start the slider
            if (!string.IsNullOrEmpty(fullCode.selectedTrack) && int.Parse(fullCode.selectedTrack) > 0 && fullCode.selectedVolume >= 0 && _isPaused == false)
            {
                _isPlaying = true;
            }
        }
        
    }

    // Call this method when the track is changed to restart the timer
    public void OnTrackChanged()
    {
        _currentTime = 0;
    }

    // Call this method to pause the media bar
    public void Pause()
    {
        Debug.Log("Media Bar paused");
        _isPlaying = false;
        _isPaused = true;
    }

    // Call this method to play the media bar
    public void Play()
    {
        _isPlaying = true;
        _isPaused = false;
    }

    // Call this method to skip to the next track
    public void SkipTrack()
    {
        var nextTrack = int.Parse(fullCode.selectedTrack) + skipTrackCount;
        var nextVolume = fullCode.selectedVolume + skipVolumeCount;

        // If the track number or volume level goes above 10, reset it to the first value
        if (nextTrack > 10) nextTrack = 1;
        if (nextVolume > 10) nextVolume = 1;

        fullCode.SelectTrackSet(nextTrack);
        fullCode.SelectVolumeSet(nextVolume);
        _currentTime = 0;
    }

    // Call this method to go to the previous track
    public void PreviousTrack()
    {
        var previousTrack = int.Parse(fullCode.selectedTrack) - 1;
        var previousVolume = fullCode.selectedVolume - 1;

        // If the track number or volume level goes below 1, reset it to the last value (10)
        if (previousTrack < 1) previousTrack = 10;
        if (previousVolume < 1) previousVolume = 10;

        fullCode.SelectTrackSet(previousTrack);
        fullCode.SelectVolumeSet(previousVolume);
        _currentTime = 0;
    }
}