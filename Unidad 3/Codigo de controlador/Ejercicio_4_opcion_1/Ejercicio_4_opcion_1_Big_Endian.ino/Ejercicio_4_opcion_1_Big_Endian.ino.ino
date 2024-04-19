void setup() {
    Serial.begin(115200);
}

void loop() {
    // 45 60 55 d5
    // https://www.h-schmidt.net/FloatConverter/IEEE754.html
    static float num = 3589.3645;

    if (Serial.available()) {
        if (Serial.read() == 's') {
            // Invertir el orden de los bytes antes de transmitirlos
            uint8_t bytes[sizeof(float)]; // Creamos un buffer para almacenar los bytes del número
            memcpy(bytes, (uint8_t *)&num, sizeof(float)); // Copiamos la representación de bytes del número al buffer
            for (int i = 0; i < sizeof(float) / 2; i++) { // Iteramos sobre la mitad del tamaño del número
                uint8_t temp = bytes[i]; // Guardamos el byte actual en una variable temporal
                bytes[i] = bytes[sizeof(float) - i - 1]; // Intercambiamos el byte actual con su correspondiente opuesto en el buffer
                bytes[sizeof(float) - i - 1] = temp; // Asignamos el byte opuesto al lugar del byte actual
            }
            Serial.write(bytes, sizeof(float)); // Transmitimos los bytes invertidos
        }
    }
}
