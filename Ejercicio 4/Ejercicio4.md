### **Ejercicio 4: retrieval practice (evaluación formativa)**

Recuerda que cada ejercicio lo trabajas en la carpeta que lleva su nombre dentro de tu repositorio de trabajo, en el enlace que hay al principio de esta página. Solo debes adicionar un archivo README.md con el nombre del equipo, integrantes y ID y un enlace a un repositorio `PÚBLICO` donde harás lo siguiente:

- Crea un proyecto para el raspberry pi.
- En el código modifica el 500 por 1000.
- Coloca el proyecto bajo control de versión.
- Sincroniza tu repositorio local con un repositorio público en Github. El enlace a este repositorio será el que coloques en el archivo README.md de la evaluación.

## Solución

**Conclusiones** Al cambiar el code de 500 a 1000 el LED parpadea aun mas lento 

El codigo sirve para controlar el LED incorporado en una placa de desarrollo Arduino o similar. La función `millis()` se utiliza para realizar un parpadeo del LED cada 500 milisegundos (medio segundo). cuando cambio el valor de 500 a 1000 pasa lo siguiente:

1. **Cambio en la Frecuencia del Parpadeo:**
   - Originalmente, el LED parpadea cada 500 milisegundos (medio segundo). Al cambiar el valor a 1000, el LED ahora parpadeará cada 1000 milisegundos (un segundo). Esto afectará la frecuencia del parpadeo del LED.

2. **Ralentización del Parpadeo:**
   - El aumento del valor a 1000 ralentizará el cambio de estado del LED. Ahora, el LED permanecerá encendido o apagado durante un segundo antes de cambiar de estado. Esto puede ser visualmente perceptible y afectará la apariencia del parpadeo.

3. **Consumo de Recursos:**
   - El código utiliza la función `millis()` para realizar el parpadeo sin bloquear el programa. Al cambiar el intervalo a 1000, el tiempo entre cambios de estado es más largo, lo que puede afectar el consumo de recursos y la respuesta a otras tareas del programa, si las hay.

4. **Mayor Duración del Parpadeo:**
   - El cambio a 1000 significa que el LED permanecerá en cada estado (encendido o apagado) durante un segundo completo. 

https://github.com/vera-perez-upb/sfi-estudiantes-202310-DanielZafiro/assets/66543657/70407ec3-577c-454e-9b19-49e21597d80e

Comprendamos el codigo entonces, ya vimos como el codigo funcionada con el Raspb..PICO pero que hace el codigo
entonces vamos a revisar linea a linea y su estructura para comprender que fue lo que hizo que el LED prendiera y a apagara en diferentes milisegundos.

El código está escrito en el lenguaje de programación Arduino, que es una variante simplificada de C++ diseñada para la programación de placas de desarrollo basadas en microcontroladores de Arduino. Este código en particular utiliza funciones específicas de Arduino para configurar el pin del LED incorporado como una salida digital y parpadea ese LED en el bucle principal (`loop()`) con un intervalo de 100 milisegundos.

```cpp
          // Configura el pin del LED incorporado como salida en el inicio del programa.
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

          // Función principal que se ejecuta en un bucle continuo.
void loop() {
          // Variables estáticas para realizar un seguimiento del tiempo anterior y del estado del LED.
  static uint32_t previousTime = 0;
  static bool ledState = true;

          // Obtiene el tiempo actual en milisegundos desde que el programa inició.
  uint32_t currentTime = millis();

          // Comprueba si ha pasado más de 100 milisegundos desde la última vez.
  if ((currentTime - previousTime) > 100) {
          // Actualiza el tiempo anterior al tiempo actual.
    previousTime = currentTime;
          // Invierte el estado del LED (encendido a apagado o viceversa).
    ledState = !ledState;
          // Configura el pin del LED incorporado con el nuevo estado.
    digitalWrite(LED_BUILTIN, ledState);
  }
}

```

Ahora, lo que hace cada parte del código:

1. `void setup()`: Esta función se ejecuta una vez al inicio del programa y se encarga de la configuración inicial. En este caso, establece el pin del LED incorporado (`LED_BUILTIN`) como una salida digital.

2. `void loop()`: Esta función se ejecuta de forma continua en un bucle infinito. Aquí es donde se realiza la lógica principal del programa.

3. `static uint32_t previousTime = 0;`: Se declara una variable estática para realizar un seguimiento del tiempo anterior. Se inicializa en 0 al principio.

4. `static bool ledState = true;`: Se declara una variable estática para realizar un seguimiento del estado del LED. Se inicializa en `true` al principio.

5. `uint32_t currentTime = millis();`: Obtiene el tiempo actual en milisegundos y lo almacena en la variable `currentTime`.

6. `if ((currentTime - previousTime) > 100) { ... }`: Verifica si ha pasado más de 100 milisegundos desde la última vez que se cambió el estado del LED.

7. `previousTime = currentTime;`: Actualiza el tiempo anterior al tiempo actual.

8. `ledState = !ledState;`: Invierte el estado del LED.

9. `digitalWrite(LED_BUILTIN, ledState);`: Configura el pin del LED incorporado con el nuevo estado, encendiéndolo o apagándolo según el valor de `ledState`.

Desglose de Palabras Claves y funciones para recordar y para empezar a familiarizarse con el lenguaje C++ :

1. `void`: Es una palabra clave que se utiliza en la declaración de funciones para indicar que la función no devuelve ningún valor. En este contexto, las funciones `setup()` y `loop()` son de tipo `void` porque no están devolviendo ningún valor.

2. `pinMode(pin, mode)`: Esta es una función de la biblioteca de Arduino. `pinMode` se utiliza para configurar un pin específico en la placa de desarrollo para ser utilizado como entrada o salida. En este caso, `pinMode(LED_BUILTIN, OUTPUT);` configura el pin del LED incorporado (`LED_BUILTIN`) como una salida digital.

3. `digitalWrite(pin, value)`: Otra función de la biblioteca de Arduino. `digitalWrite` se utiliza para establecer el estado de un pin digital específico. En este caso, `digitalWrite(LED_BUILTIN, ledState);` establece el estado del pin del LED incorporado con el valor almacenado en la variable `ledState`.

4. `uint32_t` es un tipo de dato en C++ que representa un entero sin signo de 32 bits. En particular:

- `uint`: significa "unsigned integer" (entero sin signo).
- `32`: representa la cantidad de bits utilizados para almacenar el valor.

 `uint32_t` se utiliza para declarar variables que pueden almacenar números enteros no negativos de hasta 32 bits. El rango de valores posibles para `uint32_t` va desde 0 hasta 2^32 - 1.

En el código se utilizan las variables `previousTime` y `currentTime` como `uint32_t` para almacenar valores de tiempo en milisegundos. Al utilizar un tipo de dato sin signo, se asegura de que estas variables solo almacenen valores no negativos, ya que el tiempo no puede ser negativo.Esta elección de tipo de dato es común en programación de sistemas embebidos y en entornos donde se necesita un control preciso sobre el tamaño y el signo de los datos.

5. La función `millis()` es una función proporcionada por la plataforma Arduino que devuelve el número de milisegundos desde que el programa comenzó a ejecutarse. Este valor se basa en el tiempo transcurrido desde que la placa Arduino fue reiniciada o encendida.

En el código se utiliza la función `millis()` para obtener el tiempo actual en milisegundos y se almacena en la variable `currentTime`. Este valor se utiliza para realizar un seguimiento del tiempo y controlar el parpadeo del LED.

Estas funciones y palabras clave son parte de la API (Interfaz de Programación de Aplicaciones) proporcionada por la biblioteca de Arduino. Alguien que escriba código para una placa Arduino necesita conocer estas funciones y cómo usarlas para interactuar con los periféricos y componentes conectados a la placa.

La documentación oficial de Arduino y los recursos en línea son fuentes valiosas para aprender sobre las funciones y la programación en Arduino. Además, la comunidad de Arduino es muy activa, y es común encontrar ejemplos y tutoriales que ayudan a los principiantes a comprender cómo utilizar estas funciones en sus proyectos.
