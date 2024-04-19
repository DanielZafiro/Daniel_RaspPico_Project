void setup() {
    Serial.begin(115200);
}

void loop() {
    // Número en punto flotante que se desea transmitir
    float num = 3589.3645;
    
    // Buffer para almacenar la representación en bytes del número
    static uint8_t arr[4] = {0};

    if (Serial.available()) {
        if (Serial.read() == 's') {
            // Copiar la representación de bytes del número al buffer
            memcpy(arr, (uint8_t *)&num, 4);
            
            // Invertir el orden de los bytes en el buffer antes de transmitirlos
            for (int8_t i = 3; i >= 0; i--) { // Iteramos desde el último byte hasta el primero
                Serial.write(arr[i]); // Transmitimos los bytes en orden inverso (big endian)
            }
        }
    }
}
