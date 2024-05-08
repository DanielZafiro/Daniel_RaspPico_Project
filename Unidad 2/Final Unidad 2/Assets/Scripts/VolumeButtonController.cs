using UnityEngine;
using UnityEngine.UI;

public class VolumeButtonController : MonoBehaviour
{
    public FullCode fullCode; // Reference to the FullCode script
    public int volumeLevel; // The volume level this button represents

    private void Start()
    {
        // Get the Button component and attach the SelectVolume method to its onClick event
        var button = GetComponent<Button>();
        button.onClick.AddListener(SelectVolume);
    }

    private void SelectVolume()
    {
        // Call the SelectVolumeSet method in the FullCode script with this button's volume level
        fullCode.SelectVolumeSet(volumeLevel);
        Debug.Log("Volume selected: " + volumeLevel);
    }
}