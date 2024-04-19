void setup() {
    Serial.begin(115200);
}

void loop() {
    // 45 60 55 d5
    // https://www.h-schmidt.net/FloatConverter/IEEE754.html
    static float num = 3589.3645;
    static uint8_t arr[sizeof(float)] = {0};

    if (Serial.available()) {
        if (Serial.read() == 's') {
            // Copiar la representación de bytes a un buffer
            memcpy(arr, (uint8_t *)&num, sizeof(float));
            // Invertir el orden de los bytes en el buffer
            for (int i = 0; i < sizeof(float) / 2; i++) {
                uint8_t temp = arr[i];
                arr[i] = arr[sizeof(float) - i - 1];
                arr[sizeof(float) - i - 1] = temp;
            }
            // Transmitir los bytes invertidos
            Serial.write(arr, sizeof(float));
        }
    }
}
