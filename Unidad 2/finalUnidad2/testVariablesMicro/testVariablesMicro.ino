#include <Arduino.h>

// Definición de las variables
int volumen = 50; // Volumen inicial (0-100)
int duracionCancion = 0; // Duración de la canción en segundos
int pistaActual = 1; // Pista de música actual

// Variables para el parpadeo del LED
uint32_t previousTime = 0;
bool ledState = false;

// Función para leer los comandos enviados desde Unity
void readCommands() {
    // Verificar si hay datos disponibles en el puerto serial
    if (Serial.available() > 0) {
        // Leer el primer carácter recibido del puerto serial
        char command = Serial.read();
        
        // Procesar el comando recibido
        switch (command) {
            case 'V': // Comando para cambiar el volumen
                if (Serial.available() >= 1) { // Verificar si hay suficientes datos disponibles
                    int newVolume = Serial.parseInt(); // Leer el nuevo volumen desde el puerto serial
                    if (newVolume >= 0 && newVolume <= 10) { // Verificar si el nuevo volumen está dentro del rango permitido
                        volumen = newVolume; // Actualizar el volumen
                        Serial.println("Volumen cambiado a: " + String(volumen));
                    } else {
                        Serial.println("Error: Volumen fuera de rango (0-10).");
                    }
                }
                break;
            case 'D': // Comando para cambiar la duración de la canción
                    if (Serial.available() >= 2) { // Verificar si hay suficientes datos disponibles
                    int newDuration = Serial.parseInt(); // Leer la nueva duración desde el puerto serial
                    if (newDuration >= 0 && newDuration <= 180) { // Verificar si la nueva duración está dentro del rango permitido (0 - 180 segundos)
                        duracionCancion = newDuration; // Actualizar la duración de la canción
                        Serial.println("Duración de la canción cambiada a: " + String(duracionCancion) + " segundos");
                    } else {
                        Serial.println("Error: Duración de la canción fuera de rango (0 - 180 segundos).");
                    }
                }
                break;
            case 'P': // Comando para cambiar la pista actual
                if (Serial.available() >= 2) { // Verificar si hay suficientes datos disponibles
                    int newTrack = Serial.parseInt(); // Leer la nueva pista desde el puerto serial
                    // Implementar la lógica para verificar y actualizar la pista actual
                    // Asumiremos que hay un número máximo definido de pistas
                    int maxTracks = 10; // Definir el número máximo de pistas
                    if (newTrack >= 1 && newTrack <= maxTracks) { // Verificar si la nueva pista está dentro del rango permitido
                        pistaActual = newTrack; // Actualizar la pista actual
                        Serial.println("Pista actual cambiada a: " + String(pistaActual));
                    } else {
                        Serial.println("Error: Pista fuera de rango (1-" + String(maxTracks) + ").");
                    }
                }
                break;
            default:
                Serial.println("Comando no reconocido.");
                break;
        }
    }
}

// Función para realizar tareas según el estado actual del reproductor
void task() {
    // Implementaremos la lógica principal del reproductor aquí
    // Esta función se ejecutará repetidamente en el loop principal
    // Verificaremos si hay comandos para procesar, modificaremos las variables según sea necesario y actualizaremos el estado del LED
    readCommands(); // Llamar a la función para leer los comandos desde Unity
    
    // Verificar si se debe cambiar la variable de duración de la canción
    if (duracionCancion > 0) {
        // Se podria mplementar la lógica para cambiar la duración de la canción en tiempo real
        // Por ejemplo, restar un segundo de la duración de la canción en cada iteración de esta función
        // Aquí, asumiremos que la duración de la canción disminuye en 1 segundo por cada iteración
        duracionCancion--;
        Serial.println("Duración de la canción restante: " + String(duracionCancion) + " segundos");
    }
    
    // Implementar la lógica para cambiar otras variables en tiempo real si es necesario
    
    // Demora de 1 segundo para asegurar que esta función se ejecute aproximadamente cada segundo
    delay(1000);
}

// Configuración inicial del programa
void setup() {
    Serial.begin(115200); // Iniciar comunicación serial
    pinMode(LED_BUILTIN, OUTPUT); // Configurar el LED integrado como salida
}

// Bucle principal del programa
void loop() {
    // Llamaremos a la función task para realizar las tareas principales del reproductor
    task();
    // Mantener el LED parpadeando a 1 Hz
    uint32_t currentTime = millis();
    if ((currentTime - previousTime) >= 500) { // Parpadeo cada 500 milisegundos (0.5 segundos)
        previousTime = currentTime;
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW); // Cambiar el estado del LED
    }
}
