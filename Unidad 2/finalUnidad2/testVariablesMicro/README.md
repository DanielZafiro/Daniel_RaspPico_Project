# Documentación

Esta documentación hace referencia al testVariablesMicro.ino de la carpeta actual

## Definición de las variables

Empezamos definiendo las 3 variables que vamos a implementar en el microcontrolador, establecimos las siguientes:

- Volumen: es un valor numerico que vaya desde 0 a 10, donde 0 es silencio y 10 es el max volumen
- Pista actual: representa la pista actual del reproductor con un numero entero dentro de la lista de reproduccion
- Duracion de la cancion: un valor en segundos que refleje la duracion de la pista actual
- velocidad de reproduccion: x1 x2 x3 la aceleracion del tiempo
- orden de reproduccion: reproduzca cada 1 pista cada 2 pistas cada 3pistas o asi

El micro debe encender el LED a 1 hz cada 500 milisegundos (0.5 segundos) para visualizar fisicamente que no se bloquee

Desde Unity debe haber comunicacion con el controlador para cambiar los parametros iniciales y en tiempo real de las variables mediante elementos interactivos en la interfaz grafica

---

La estructura para el codigo del microcontrolador organizada de la siguiente manera, estableciendo el parpadeo del LED y que espere los comandos para establecer el valor de las variables
ejemplo:

para el volumen: V (1-10)
para la duracion: D (1-infinitos segundos)
para la pista actual: P (1-10)

Si 

```cpp
#include <Arduino.h>

// Definición de las variables
int volumen = 5; // Volumen inicial (0-10)
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
                if (Serial.available() >= 2) { // Verificar si hay suficientes datos disponibles
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
                    if (newDuration >= 0) { // Verificar si la nueva duración es válida
                        duracionCancion = newDuration; // Actualizar la duración de la canción
                        Serial.println("Duración de la canción cambiada a: " + String(duracionCancion) + " segundos");
                    } else {
                        Serial.println("Error: Duración de la canción no válida.");
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
    // Implementar otras tareas según sea necesario
}

// Configuración inicial del programa
void setup() {
    Serial.begin(115200); // Iniciar comunicación serial
    pinMode(LED_BUILTIN, OUTPUT); // Configurar el LED integrado como salida
}

// Bucle principal del programa
void loop() {
    static uint32_t previousTime = 0;
    static bool ledState = true;

    // Verificaremos si ha pasado el tiempo suficiente para cambiar el estado del LED
    uint32_t currentTime = millis();
    if ((currentTime - previousTime) > 500) { // Cambio cada 500 milisegundos (0.5
```
