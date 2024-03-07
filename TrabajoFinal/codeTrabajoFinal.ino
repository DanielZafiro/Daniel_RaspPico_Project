#include <Arduino.h>

enum class DefuseStates {
  INIT,
  CONFIG,
  WAIT_DATA
};

static auto defuseState = DefuseStates::INIT;
static char password[5];
static uint8_t dataCounter = 0;
static uint32_t defuseTime = 5;
static constexpr uint32_t INTERVAL = 1000;
static constexpr uint32_t INTERVAL2 = 2000;
static uint32_t lastTime = 0;
static uint8_t result[2];

void defuse() {
  switch (defuseState) {
    case DefuseStates::INIT: {
      // Inicialización del puerto serial y mensaje inicial
      Serial.begin(115200);
      delay(2000);
      Serial.print("AHORA ENTRANDO AL MODO CONFIGURACIÓN");
      delay(2000);
      defuseState = DefuseStates::CONFIG;
      break;
    }
    case DefuseStates::CONFIG: {
      // Inicializa el tiempo de la cuenta regresiva en 5 segundos
      defuseTime = 5;
      Serial.println("'S' para aumentar 1 segundo, 'B' para bajar 1 segundo, 'L' para salir de la configuración. ");
      Serial.println("Segundos por defecto: 5");

      // Bucle que espera la interacción del usuario
      while (true) {
        // Verifica si hay datos disponibles en el puerto serial
        if (Serial.available()) {
          // Lee el caracter ingresado por el usuario
          const char c = Serial.read();

          // Maneja la acción según el caracter ingresado L S o B
          if (c == 'L') {
            // Sale del bucle y pasa al estado de espera de datos
            Serial.println("Ahora Inicia la cuenta regresiva ");
            delay(2000);
            defuseState = DefuseStates::WAIT_DATA;
            break;
          }
          if (c == 'S') {
            // Aumenta el tiempo en 1 segundo, pero no más de 40 segundos
            if(defuseTime == 40){
              Serial.println("No se pueden agregar más de 40 segundos ");
            }
            else{
              defuseTime++;
              Serial.println("Subió 1 segundo ");
            }
          }
          if (c == 'B') {
            // Reduce el tiempo en 1 segundo, pero no menos de 1 segundo
            if(defuseTime == 1){
              Serial.println("No se puede bajar a menos de 1 segundo ");
            }
            else{
              defuseTime--;
              Serial.println("Bajó 1 segundo ");;
            }             
          }

          // Muestra el tiempo actual configurado
          Serial.println(defuseTime);
        }
      }
      break;
    }
    case DefuseStates::WAIT_DATA: {
      // Bucle principal que espera la entrada de datos o el tiempo de cuenta regresiva
      do {            
        // Verifica si hay datos disponibles en el puerto serial
        if (Serial.available() > 0){
          // Lee el caracter del puerto serial y lo almacena en el array de contraseñas
          password[dataCounter] = Serial.read();
          dataCounter++;

          // Cuando se recopilan 5 caracteres
          if(dataCounter == 5){
            // Compara la contraseña ingresada con la contraseña predefinida
            compareData(password, dataCounter,result);
            dataCounter = 0; // Reinicia el contador de caracteres
            Serial.println("result: ");
            Serial.println(result[1]);

            // Si la comparación es exitosa (result[1] == 1), se imprime el mensaje "Salvaste el mundo"
            if(result[1] == 1){
              Serial.println("Salvaste el mundo");
              delay(2000);
              defuseState = DefuseStates::CONFIG;
              break;
            }
            else{
              // Si la comparación falla, imprime "Respuesta incorrecta" y vuelve a esperar datos
              Serial.println("Respuesta incorrecta");
              defuseState = DefuseStates::WAIT_DATA;
              break;
            }          
          }
        }

      // Verifica el tiempo de cuenta regresiva
      uint32_t currentTime = millis();
      if ((currentTime - lastTime) >= INTERVAL) {
        Serial.println("Tiempo restante");
        lastTime = currentTime;
        defuseTime--;     // Reducción del tiempo de cuenta regresiva                        
        Serial.println(defuseTime);
      }
    }while (defuseTime > 0 ); // Repite el bucle mientras el tiempo de cuenta regresiva sea mayor que cero

      // Cuando el tiempo de cuenta regresiva llega a cero
      if(defuseTime == 0){
        Serial.println("RADIACIÓN NUCLEAR ACTIVA");   

        // Espera 2 segundos y vuelve al estado de configuración
        uint32_t currentTime2 = millis();
        bool is = true;
        do{    
          if ((currentTime2 - lastTime) >= INTERVAL2) {
            is = false;
            delay(2000);
            defuseState = DefuseStates::CONFIG;
            break;
          }  
        }while(is == true);          
      }
      // Sale del bucle del estado WAIT_DATA y pasa al siguiente estado
      break;
    }

    default: { //se ejecutará cuando no haya un case correspondiente.
      break;
    }
  }
}
static void compareData(const char *pass, const uint8_t size, uint8_t *res){ //tres parámetros: `pass` (puntero a una cadena de caracteres), `size` (tamaño de la cadena), y `res` (puntero a un arreglo de 8 bits para almacenar los resultados
  constexpr char compare[5] = {'C','1','2','3','4'};  // contraseña predefinida almacenada en un arreglo de caracteres
  bool same = true; // Esta variable se usará para indicar si las contraseñas son iguales o no

  for(int i = 0; i < size; i++){ // bucle que recorre cada caracter de la contraseña ingresada (`pass`) y la compara con la contraseña predefinida (`compare`)
    if (pass[i] == compare[i]){
      same = true;
    }
    else{
      same = false; // si no coincide, se establece `same` en `false` y se sale del bucle
      i = 5;      
    }  
  }

  // Se asignan resultados en el arreglo `res`. `res[0]` almacena 0 si las contraseñas son iguales y 1 si son diferentes. `res[1]` almacena 1 si las contraseñas son iguales y 0 si son diferentes
  res[0] = same ? 0 : 1;
  res[1] = same ? 1 : 0;
}


void setup() { //El setup() llama a la función defuse() para iniciar el juego. Una sola vez al iniciar el programa
  defuse();
}

void loop() { //El loop() continúa ejecutando la función defuse() en un bucle infinito.
  defuse();
}
