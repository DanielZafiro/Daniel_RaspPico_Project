#include <Arduino.h>
 
enum State {
    STATE_OFF,
    STATE_SETUP,
    STATE_SELECT_PARAMETERS,
    STATE_PLAYING
};
State currentState = STATE_OFF;
 
// Variables
uint32_t volume = 0; // 0 is mute
uint32_t volumeMax = 10;
uint32_t trackDuration = 0;
uint32_t selectedDuration = 0;
uint32_t currentTrack = 0;
uint32_t maxTrack = 10;
uint32_t trackJump = 1;
uint32_t volumeJump = 1;
uint32_t previousTime = 0;
bool ledState = false;
bool playerOn = false;
unsigned long lastStateChange = 0;

// Lista de canciones
const char* songList[10] = {
    "1. Song One",
    "2. Song Two",
    "3. Song Three",
    "4. Song Four",
    "5. Song Five",
    "6. Song Six",
    "7. Song Seven",
    "8. Song Eight",
    "9. Song Nine",
    "10. Song Ten"
};
 
 
void offState() {
    if (millis() - lastStateChange >= 3000) {
        Serial.println("Player is off Press O to turn ON");
        lastStateChange = millis();
    }
 
    if (Serial.available() > 0) {
        char command = Serial.read();
        if (command == 'O') {
            currentState = STATE_SETUP;
            playerOn = true;
        }
    }
}
 
void selectParametersState() {
    Serial.println("Welcome to Bubble Pop music player setup. Please enter the following parameters:");
    Serial.println("Track number (1-10):");
    while (Serial.available() == 0) {}
    uint32_t selectedTrack = Serial.parseInt();
    if (selectedTrack >= 1 && selectedTrack <= maxTrack) {
        currentTrack = selectedTrack - 1;
        Serial.print("Initial track ");
        Serial.println(songList[currentTrack - 1]);
    } else {
        Serial.println("Invalid track number, defaulting to track 1");
        currentTrack = 1;
    }
 
    Serial.println("Next set Volume (0-10):");
    while (Serial.available() == 0) {}
    uint32_t selectedVolume = Serial.parseInt();
    if (selectedVolume >= 0 && selectedVolume <= volumeMax) {
        volume = selectedVolume;
        Serial.println("Volume set to " + String(volume));
    } else {
        Serial.println("Invalid volume value, defaulting to volume 0 (mute)");
        volume = 0;
    }
 
    Serial.println("Next set the Track duration (5-180 seconds):");
    while (Serial.available() == 0) {}
    selectedDuration = Serial.parseInt();
    if (selectedDuration >= 5 && selectedDuration <= 180) {
        trackDuration = selectedDuration;
        Serial.println("Track duration set to " + String(trackDuration) + " seconds");
    } else {
        Serial.println("Invalid duration value, defaulting to 5 seconds");
        trackDuration = 5;
    }
 
    currentState = STATE_PLAYING;
}
 
void task() {
    if (Serial.available() > 0) {
        char command = Serial.read();
        switch (command) {
            case 'P': // Play
                currentState = STATE_PLAYING;
                break;
            case 'S': // Stop
                currentState = STATE_OFF;
                playerOn = false;
                break;
            case 'N': // Next track
                if (currentTrack < maxTrack) {
                    currentTrack += trackJump;
                } else {
                    currentTrack = 1;
                }
                Serial.println("Playing track " + String(currentTrack));
                break;
            case 'V': // Adjust volume
                if (Serial.available() >= 1) {
                    uint32_t newVolume = Serial.parseInt();
                    if (newVolume >= 0 && newVolume <= volumeMax) {
                        volume = newVolume;
                        Serial.println("Volume set to " + String(volume));
                    } else {
                        Serial.println("Invalid volume value");
                    }
                }
                break;
            case 'D': // Adjust track duration
                if (Serial.available() >= 1) {
                    uint32_t newDuration = Serial.parseInt();
                    if (newDuration >= 0 && newDuration <= 180) {
                        trackDuration = newDuration;
                        Serial.println("Track duration set to " + String(trackDuration) + " seconds");
                    } else {
                        Serial.println("Invalid duration value");
                    }
                }
                break;
            default:
                Serial.println("Invalid command");
                break;
        }
    }
}
 
void playingState() {
  if (playerOn) {
    task();
    if (currentState == STATE_PLAYING){
      if (trackDuration > 0) {
        trackDuration--;
        Serial.println("Track duration: " + String(trackDuration) + " seconds");
      } 
      delay(1000);

      if (trackDuration == 0){
        currentTrack++;
        //songList[currentTrack + 1];
        volume += volumeJump;
        trackDuration = selectedDuration;

        if (currentTrack >= maxTrack){
          currentTrack = 0;
        }
        
      } 
    
 
    // Enviar información de la canción actual
    Serial.print("Current song: ");
    Serial.println(songList[currentTrack]);
    } else {
        currentState = STATE_SETUP; // Volver al estado de configuración
    }
 
}
}
 
void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    currentState = STATE_OFF;
}
 
void loop() {
    switch (currentState) {
        case STATE_OFF:
            offState();
            break;
        case STATE_SETUP:
            selectParametersState();
            break;
        case STATE_PLAYING:
            playingState();
            break;
    }
 
    // Mantener el LED parpadeando a 1 Hz
    uint32_t currentTime = millis();
    if ((currentTime - previousTime) >= 500) { // Parpadeo cada 500 milisegundos (0.5 segundos)
        previousTime = currentTime;
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);
    }
}