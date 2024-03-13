# Trabajo final

En una experiencia un grupo terrorista llamado “Disedentes del tiempo” realizan la configuración de una central nuclear global con la que se realizará la emisión de radiación nuclear al mundo. El sistema utiliza una interfaz de usuario simulada mediante el puerto serial, implementada en un entorno de software de Arduino.

En esta configuración inicial el sistema inicia en modo de configuración, mostrando una vez el mensaje CONFIG. En este modo se le configura el tiempo para abrir la cámara, por defecto tiene 5 seg y puede configurarse  entre 1 y 40 segundos con los botones S(Subir) y B(Bajar) en pasos de 1 segundo. Tan pronto se ajuste el tiempo de apertura de la cámara se termina con la letra L (listo) y se observa la cuenta en una pantalla, al final de la cual se abre la cámara y se hace la emisión de la radiación.  Cuando la cuenta regresiva termine debe mostrarse el mensaje “RADIACIÓN NUCLEAR ACTIVA” y a los dos segundos pasar nuevamente al modo CONFIG.

La misión del participante de la experiencia es salvar el mundo, por lo cual debe descifrar con pistas e ingresar el código de acceso, para lo cual  se envía por el puerto serial la secuencia 'C' seguido de la clave numérica (por ejemplo, 'C1234'). Si ingresas la clave correcta debe aparecer el mensaje “SALVASTE AL MUNDO”, sino la cuenta regresiva debe continuar hasta el fatal desenlace.

Te dejo el siguiente material trabajado en clase como complemento a la información del trayecto de actividades.

[Presentación de sistemas embebidose](https://upbeduco-my.sharepoint.com/:b:/g/personal/vera_perez_upb_edu_co/EaIafHzSSxFOmAdXvPJzVxIBcPcu_KEhUCUu-k56LJJ4GQ?e=UVVPgY) 

## Solución

```cpp
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
```

imulamos la situación de desactivación de una bomba, donde se configura un tiempo y se introduce una contraseña para desactivarla analicemos el paso a paso de que fue lo qe hicimos y su funcionamiento logico

1. **Inclusión de librerías y definición de enumeración:**
   ```cpp
   #include <Arduino.h>

   enum class DefuseStates {
     INIT,
     CONFIG,
     WAIT_DATA
   };
   ```
   - Se incluye la librería de Arduino dado que se trabajó en un IDE de Arduino actualizado y se define una enumeración `DefuseStates` que representa los diferentes estados del sistema.
  

2. **Declaración de variables estáticas:**

```cpp
static auto defuseState = DefuseStates::INIT;
static char password[5];
static uint8_t dataCounter = 0;
static uint32_t defuseTime = 5;
static constexpr uint32_t INTERVAL = 1000;
static constexpr uint32_t INTERVAL2 = 2000;
static uint32_t lastTime = 0;
static uint8_t result[2];
```

- `defuseState`: Almacena el estado actual del juego. El uso de `static` aquí asegura que la variable retenga su valor entre llamadas a la función `defuse()`.

- `password[5]`: Almacena la contraseña ingresada. `static` se utiliza para mantener el contenido del arreglo entre llamados.

- `dataCounter`: Lleva un seguimiento de la cantidad de caracteres ingresados para la contraseña.

- `defuseTime`: Representa el tiempo restante de la cuenta regresiva en este caso 5s. 

- `INTERVAL` y `INTERVAL2`: Son constantes que representan intervalos de tiempo en milisegundos de 1 y 2 segundos.

- `lastTime`: Almacena el tiempo del último evento, utilizado para controlar los intervalos de tiempo.

- `result[2]`: Almacena los resultados de la comparación de la contraseña. `result[0]` indica si la contraseña es correcta (0 si es correcta, 1 si es incorrecta), y `result[1]` es una versión invertida de `result[0]`.


3. **Definición de la función principal `defuse()`:**
   ```cpp
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
       // ...
       // Los otros casos (CONFIG y WAIT_DATA) contienen la lógica principal del juego.
       // ...
     }
   }
   ```
   - La función `defuse()` maneja el estado actual del sistema y ejecuta diferentes lógicas según el estado. inicializando con u mensaje y cambiando a estado CONFIG

4. caso `DefuseStates::CONFIG` y se encarga de manejar la configuración del tiempo para la cuenta regresiva antes de la apertura de la cámara. Aquí hay un desglose paso a paso:

```cpp
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
        if (defuseTime == 40) {
          Serial.println("No se pueden agregar más de 40 segundos ");
        } else {
          defuseTime++;
          Serial.println("Subió 1 segundo ");
        }
      }
      if (c == 'B') {
        // Reduce el tiempo en 1 segundo, pero no menos de 1 segundo
        if (defuseTime == 1) {
          Serial.println("No se puede bajar a menos de 1 segundo ");
        } else {
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
```

- **Configuración inicial:**
  - Inicializa el tiempo de la cuenta regresiva (`defuseTime`) en 5 segundos.
  - Imprime instrucciones y el tiempo por defecto.

- **Bucle de interacción del usuario:**
  - Entra en un bucle infinito que espera la interacción del usuario a través del puerto serial.
  - Lee el caracter ingresado por el usuario y realiza acciones específicas para 'L', 'S', y 'B'.
  - Muestra el tiempo actual configurado después de cada ajuste.

- **Acciones según el caracter ingresado:**
  - 'L': Sale del bucle y pasa al estado de espera de datos (`DefuseStates::WAIT_DATA`).
  - 'S': Aumenta el tiempo en 1 segundo, con una verificación para no exceder los 40 segundos.
  - 'B': Reduce el tiempo en 1 segundo, con una verificación para no disminuir por debajo de 1 segundo. Llegando al minimo que es 5s establecidos por defuseTime = 5

5. caso `DefuseStates::WAIT_DATA`  maneja el proceso de espera de datos desde el puerto serial, la comparación de la contraseña y la gestión de la cuenta regresiva.

```cpp
case DefuseStates::WAIT_DATA: {
  // Bucle principal que espera la entrada de datos o el tiempo de cuenta regresiva
  do {
    // Verifica si hay datos disponibles en el puerto serial
    if (Serial.available() > 0) {
      // Lee el caracter del puerto serial y lo almacena en el array de contraseñas
      password[dataCounter] = Serial.read();
      dataCounter++;

      // Cuando se recopilan 5 caracteres
      if (dataCounter == 5) {
        // Compara la contraseña ingresada con la contraseña predefinida
        compareData(password, dataCounter, result);
        dataCounter = 0;  // Reinicia el contador de caracteres
        Serial.println("result: ");
        Serial.println(result[1]);

        // Si la comparación es exitosa (result[1] == 1), se imprime el mensaje "Salvaste el mundo"
        if (result[1] == 1) {
          Serial.println("Salvaste el mundo");
          delay(2000);
          defuseState = DefuseStates::CONFIG;
          break;
        } else {
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
      defuseTime--;  // Reducción del tiempo de cuenta regresiva
      Serial.println(defuseTime);
    }
  } while (defuseTime > 0);  // Repite el bucle mientras el tiempo de cuenta regresiva sea mayor que cero

  // Cuando el tiempo de cuenta regresiva llega a cero
  if (defuseTime == 0) {
    Serial.println("RADIACIÓN NUCLEAR ACTIVA");

    // Espera 2 segundos y vuelve al estado de configuración
    uint32_t currentTime2 = millis();
    bool is = true;
    do {
      if ((currentTime2 - lastTime) >= INTERVAL2) {
        is = false;
        delay(2000);
        defuseState = DefuseStates::CONFIG;
        break;
      }
    } while (is == true);
  }

  // Sale del bucle del estado WAIT_DATA y pasa al siguiente estado
  break;
}
```

- **Entrada de Datos:**
  - Entra en un bucle (`do-while`) que espera la entrada de datos desde el puerto serial o la cuenta regresiva.
  - Si hay datos disponibles en el puerto serial, lee el caracter y lo almacena en el array de contraseñas (`password`).
  - Cuando se recopilan 5 caracteres, realiza una comparación de la contraseña (`compareData`).
  - Si la comparación es exitosa, imprime "Salvaste el mundo" y vuelve al estado de configuración (`DefuseStates::CONFIG`).
  - Si la comparación falla, imprime "Respuesta incorrecta" y vuelve a esperar datos (`DefuseStates::WAIT_DATA`).

- **Cuenta Regresiva:**
  - Verifica el tiempo de cuenta regresiva cada segundo.
  - Reduce el tiempo de cuenta regresiva y lo muestra por el puerto serial.
  - Sale del bucle cuando el tiempo de cuenta regresiva llega a cero.

- **RADIACIÓN NUCLEAR ACTIVA:**
  - Si el tiempo de cuenta regresiva llega a cero, imprime "RADIACIÓN NUCLEAR ACTIVA".
  - Espera 2 segundos antes de volver al estado de configuración (`DefuseStates::CONFIG`).

- **Transicion de Estado:**
  - Sale del bucle del estado `WAIT_DATA` y pasa al siguiente estado.
 
```cpp
while (defuseTime > 0);  // Repite el bucle mientras el tiempo de cuenta regresiva sea mayor que cero

  // Cuando el tiempo de cuenta regresiva llega a cero
  if (defuseTime == 0) {
    Serial.println("RADIACIÓN NUCLEAR ACTIVA");

    // Espera 2 segundos y vuelve al estado de configuración
    uint32_t currentTime2 = millis();
    bool is = true;
    do {
      if ((currentTime2 - lastTime) >= INTERVAL2) {
        is = false;
        delay(2000);
        defuseState = DefuseStates::CONFIG;
        break;
      }
    } while (is == true);
  }

  // Sale del bucle del estado WAIT_DATA y pasa al siguiente estado
  break;
```
en este fragmento garantiza que, después de que el tiempo de cuenta regresiva alcance cero, se realice una transición al estado de configuración con una breve espera de dos segundos. Durante esta espera, el mensaje "RADIACIÓN NUCLEAR ACTIVA" se imprime por el puerto serial.

```cpp
while (defuseTime > 0);  // Repite el bucle mientras el tiempo de cuenta regresiva sea mayor que cero
```

- Este es un bucle `do-while` que se ejecuta mientras `defuseTime` sea mayor que cero.
- Dentro de este bucle, se espera a que `defuseTime` alcance cero antes de salir del bucle.
- Después de salir del bucle `while`, se verifica si `defuseTime` ha llegado a cero.
- Si es así, imprime "RADIACIÓN NUCLEAR ACTIVA" por el puerto serial.
- Inicia un bucle `do-while` que espera dos segundos antes de volver al estado de configuración (`DefuseStates::CONFIG`).
- Esta espera está controlada por la variable `is`, que se establece en falso cuando ha transcurrido el tiempo de espera.

```cpp
// Sale del bucle del estado WAIT_DATA y pasa al siguiente estado
break;
```

- Finalmente, después de esperar dos segundos, el código sale del bucle del estado `WAIT_DATA` y pasa al siguiente estado (`DefuseStates::CONFIG`).


6. la función `compareData`, se encarga de comparar una contraseña ingresada con una contraseña predefinida y devuelve los resultados de la comparación.

```cpp
static void compareData(const char *pass, const uint8_t size, uint8_t *res){ //tres parámetros: `pass` (puntero a una cadena de caracteres), `size` (tamaño de la cadena), y `res` (puntero a un arreglo de 8 bits para almacenar los resultados
  constexpr char compare[5] = {'C','1','2','3','4'}; // contraseña predefinida almacenada en un arreglo de caracteres
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
```

- **Declaración y definición de la función:**
   ```cpp
   static void compareData(const char *pass, const uint8_t size, uint8_t *res)
   ```
   - La función `compareData` es de tipo `void` (no devuelve ningún valor).
   - Toma tres parámetros: `pass` (puntero a una cadena de caracteres), `size` (tamaño de la cadena), y `res` (puntero a un arreglo de 8 bits para almacenar los resultados).

- **Definición de la contraseña predefinida:**
   ```cpp
   constexpr char compare[5] = {'C','1','2','3','4'};
   ```
   - Se define una contraseña predefinida almacenada en un arreglo de caracteres llamado `compare`. En este caso, la contraseña es "C1234".

- **Inicialización de la variable `same`:**
   ```cpp
   bool same = true;
   ```
   - Se inicializa una variable booleana `same` en `true`. Esta variable se usará para indicar si las contraseñas son iguales o no.

- **Bucle de comparación:**
   ```cpp
   for(int i = 0; i < size; i++){
     if (pass[i] == compare[i]){
       same = true;
     }
     else{
       same = false;
       i = 5;      
     }  
   }
   ```
   - Se realiza un bucle que recorre cada caracter de la contraseña ingresada (`pass`) y la compara con la contraseña predefinida (`compare`).
   - Si un caracter no coincide, se establece `same` en `false` y se sale del bucle.

- **Asignación de resultados:**
   ```cpp
   res[0] = same ? 0 : 1;
   res[1] = same ? 1 : 0;
   ```
   - Se asignan resultados en el arreglo `res`. `res[0]` almacena 0 si las contraseñas son iguales y 1 si son diferentes. `res[1]` almacena 1 si las contraseñas son iguales y 0 si son diferentes.


7. **Funciones `setup()` y `loop()`:**
   ```cpp
   void setup() {
     defuse();
   }

   void loop() {
     defuse();
   }
   ```
   - El `setup()` llama a la función `defuse()` para iniciar el juego. Una sola vez al iniciar el programa
   - El `loop()` continúa ejecutando la función `defuse()` en un bucle infinito.

el código está estructurado para gestionar el juego de desactivación con configuración de tiempo y contraseña. Quedaron pendientes las pistas
