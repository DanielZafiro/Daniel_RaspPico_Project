#include <Arduino.h>

// Enumeración de los posibles estados del reproductor
enum PlayerState
{
    Off,      // Estado apagado
    On,       // Estado encendido
    Play,     // Estado de reproducción
    Pause,    // Estado de pausa
    Stop,     // Estado de detención
    Forward,  // Estado de avance rápido
    Rewind    // Estado de rebobinado
};

// Estado inicial apagado
PlayerState currentState = Off;

// Función para realizar tareas según el estado actual del reproductor
void task()
{
    // Variables para el parpadeo del LED
    static uint32_t previousTime = 0;
    static bool ledState = false;
    
    uint32_t currentTime = millis();
    
    // Verificar si hay datos disponibles en el puerto serial
    if (Serial.available() > 0)
    {
        // Leer el carácter recibido del puerto serial
        char receivedChar = Serial.read();

        // Determinar el estado según el carácter recibido
        switch (receivedChar)
        {
        case 'On':
            currentState = On;
            digitalWrite(LED_BUILTIN, HIGH); // Encender el LED integrado
            break;
        case 'Off':
            currentState = Off;
            digitalWrite(LED_BUILTIN, LOW); // Apagar el LED integrado
            break;
        case 'Play':
            currentState = Play;
            digitalWrite(LED_BUILTIN, HIGH); // Encender el LED integrado durante la reproducción
            break;
        case 'Pause':
            currentState = Pause;
            // Implementar titilación lenta del LED para el estado Pause
            if (currentTime - previousTime > 500) 
            {
                previousTime = currentTime;
                ledState = !ledState;
                digitalWrite(LED_BUILTIN, ledState);
            }
            break;
        case 'Stop':
            currentState = Stop;
            // Mantener el LED encendido para el estado Stop
            digitalWrite(LED_BUILTIN, HIGH);
            break;
        case 'Forward':
        case 'Rewind':
            currentState = Forward; // Ambos comparten el mismo estado
            // Implementar titilación rápida del LED para los estados Forward y Rewind
            if (currentTime - previousTime > 100) 
            {
                previousTime = currentTime;
                ledState = !ledState;
                digitalWrite(LED_BUILTIN, ledState);
            }
            break;
        default:
            Serial.println("Comando no reconocido.");
            break;
        }
    }
}

// Configuración inicial del programa
void setup()
{
    Serial.begin(115200);         // Iniciar comunicación serial
    pinMode(LED_BUILTIN, OUTPUT); // Configurar el LED integrado como salida
    task();
}

// Bucle principal del programa
void loop()
{
    task(); 
}
