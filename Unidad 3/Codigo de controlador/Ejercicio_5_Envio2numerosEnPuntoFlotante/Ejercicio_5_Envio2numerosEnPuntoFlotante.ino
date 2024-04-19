void setup() {
    Serial.begin(115200);
}

void loop() {
    // Dos números en punto flotante que se desean transmitir
    // https://www.h-schmidt.net/FloatConverter/IEEE754.html
    float num1 = 3589.3645; // 45 60 55 d5 L.E.
    float num2 = -1234.5678; // c4 9a 52 2b L.E.
    
    // Buffer para almacenar la representación en bytes de los números
    static uint8_t arr1[4] = {0};
    static uint8_t arr2[4] = {0};

    if (Serial.available()) {
        if (Serial.read() == 's') {
            // Copiar la representación de bytes de los números al buffer
            memcpy(arr1, (uint8_t *)&num1, 4);
            memcpy(arr2, (uint8_t *)&num2, 4);
            
            // Transmitir los bytes en orden original (little endian)
            Serial.write(arr1, 4);
            Serial.write(arr2, 4);
            
            // Invertir el orden de los bytes antes de transmitirlos (big endian)
            for (int8_t i = 3; i >= 0; i--) {
                Serial.write(arr1[i]);
            }
            for (int8_t i = 3; i >= 0; i--) {
                Serial.write(arr2[i]);
            }
        }
    }
}
