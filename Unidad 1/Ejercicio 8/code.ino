unsigned long startTime; // almacenar el tiempo en milisegundos en el que se inicia cada estado
int state = 0; // estado actual de la máquina de estados

void setup() {
  Serial.begin(115200); // velocidad de transferencia/comunicacion entre RaspPico y dispositivo conectado
}

void loop() {
  unsigned long currentTime = millis();

  switch (state) {
    case 0:  // Estado 0: Espera 1 segundo antes de imprimir
      if (currentTime - startTime >= 1000) { // Si ha pasado un segundo entonces..
        Serial.println("Pasó 1 segundo"); // Imprime este mensaje
        startTime = currentTime; // actualiza la variable startTime con el valor actual de currentTime.
        state = 1; // cambia al estado 1
      }
      break;

    case 1:  // Estado 1: Espera 2 segundos antes de imprimir
      if (currentTime - startTime >= 2000) { // Si han pasado dos segundos entonces..
        Serial.println("Pasaron 2 segundos"); // Imprime este mensaje
        startTime = currentTime; // actualiza la variable startTime con el valor actual de currentTime.
        state = 2; // cambia al estado 2
      }
      break;

    case 2:  // Estado 2: Espera 3 segundos antes de imprimir y reinicia a estado 0
      if (currentTime - startTime >= 3000) { // Si han pasado tres segundos entonces..
        Serial.println("Pasaron 3 segundos"); // Imprime este mensaje
        startTime = currentTime; // actualiza la variable startTime con el valor actual de currentTime.
        state = 0;  // cambia Reiniciando al Estado 0
      }
      break;

    default:
      Serial.println("Error: Estado no definido"); //seguridad: estado no definido en el switch imprime un mensaje de error.
      break;
  }
}
