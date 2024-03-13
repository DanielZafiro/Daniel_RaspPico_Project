### **Ejercicio 8: retrieval practice (evaluación formativa)**

- Realiza un programa que envíe un mensaje al pasar un segundo, dos segundos y tres segundos. Luego de esto debe volver a comenzar.

En el README.md del repositorio responde:

- ¿Cuáles son los estados del programa?
- ¿Cuáles son los eventos?
- ¿Cuáles son las acciones?


## Solución

Diagrama de estados:
![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/a606940b-03fc-4e3a-986c-fe9f21907b1e)

- ¿Cuáles son los estados del programa?

Estados del Programa:

Estado 0: Espera 1 segundo.

Estado 1: Espera 2 segundos.

Estado 2: Espera 3 segundos y luego reinicia al Estado 0.

- ¿Cuáles son los eventos?

Eventos: La transición entre estados se activa cuando ha pasado el tiempo especificado desde el inicio del estado actual. 1s, 2s, 3s.

- ¿Cuáles son las acciones?

Acciones: Se imprime un mensaje en el Monitor Serie cuando se realiza la transición entre estados.

**Manos al codigo:**

Declaramos una variable `startTime` como tipo `unsigned long`. Se utilizará para almacenar el tiempo en milisegundos en el que se inicia cada estado.

Inicializamos la variable `state` en 0. Esta variable representa el estado actual de la máquina de estados. Cada número corresponde a un estado específico (en este caso 3 estados 0,1,2)

En `void setup() { ... } ` Configuramos el entorno y  la comunicación serie a una velocidad de 115200 baudios. Esto se hace una sola vez al inicio del programa.

```cpp
unsigned long startTime; // almacenar el tiempo en milisegundos en el que se inicia cada estado
int state = 0; // estado actual de la máquina de estados

void setup() {
  Serial.begin(115200); // velocidad de transferencia/comunicacion entre RaspPico y dispositivo conectado
}
```

Segun el ejercicio entonces necesito 3 estados en bucle:
1. cuando pase un segundo imprima que pasó 1 segundo (estado 0)
2. cuando pasen dos segundos imprima que pasaron 2 segundos (estado 1)
3. cuando pasen tres segundos imprima que pasaron 3 segundos y que vuelva a empezar (estado 2)

```cpp
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
```
`unsigned long currentTime = millis();`: Obtiene el tiempo actual en milisegundos en el bucle principal. Se actualiza en cada iteración del bucle.

`switch (state) { ... }`: Inicia una estructura switch basada en el estado actual `(state)`. Aquí definimos la lógica de la máquina de estados.

`case 0: // Estado 0`: Verifica si ha pasado 1 segundo desde el inicio del estado. Si es así, imprime un mensaje, actualiza el tiempo de inicio y cambia al Estado 1.

`case 1: // Estado 1`: Verifica si ha pasado 2 segundos, imprime el mensaje, actualiza el tiempo de inicio y cambia al Estado 2.

`case 2: // Estado 2`: Verifica si han pasado 3 segundos, imprime el mensaje, actualiza el tiempo de inicio y reinicia al Estado 0.

`default: Serial.println("Error: Estado no definido");`: Maneja cualquier estado no definido en el switch y imprime un mensaje de error.

