### **Ejercicio 16: análisis del api serial (investigación: hipótesis-pruebas)**

Qué crees que ocurre cuando:

- ¿Qué pasa cuando hago un [Serial.available()](https://www.arduino.cc/reference/en/language/functions/communication/serial/available/)?
- ¿Qué pasa cuando hago un [Serial.read()](https://www.arduino.cc/reference/en/language/functions/communication/serial/read/)?
- ¿Qué pasa cuando hago un Serial.read() y no hay nada en el buffer de recepción?
- Un patrón común al trabajar con el puerto serial es este:

```cpp
if(Serial.available() > 0){
    int dataRx = Serial.read()
}
```

- ¿Cuántos datos lee Serial.read()?
- ¿Y si quiero leer más de un dato? No olvides que no se pueden leer más datos de los disponibles en el buffer de recepción porque no hay más datos que los que tenga allí.
- ¿Qué pasa si te envían datos por serial y se te olvida llamar Serial.read()?

**Advertencia**

NO AVANCES SIN ACLARAR LAS PREGUNTAS ANTERIORES

Te pido que resuelvas las preguntas anteriores antes de avanzar. ES MUY IMPORTANTE.

## Solución

- ¿Qué pasa cuando hago un [Serial.available()](https://www.arduino.cc/reference/en/language/functions/communication/serial/available/)?

La función `Serial.available()` en la programación para plataformas Arduino, como en el lenguaje de programación C++, devuelve el número de bytes disponibles en el búfer de entrada del puerto serial. Este búfer almacena los datos que se han recibido pero aún no han sido leídos por el programa.

Cuando llamas a `Serial.available()`, estás consultando cuántos bytes de datos están listos para ser leídos. La razón por la cual esto es importante es que antes de leer datos del puerto serial, es útil verificar si hay datos disponibles para evitar la lectura de datos que aún no han llegado.

Ejemplo de uso típico:

```cpp
if (Serial.available() > 0) {
  // Hay datos disponibles para leer
  char dato = Serial.read();
  // Realizar alguna acción con el dato leído
}
```

En este ejemplo, la condición `Serial.available() > 0` se evalúa como verdadera si hay al menos un byte de datos disponible en el búfer del puerto serial. Luego, `Serial.read()` se utiliza para leer el primer byte disponible.

- ¿Qué pasa cuando hago un [Serial.read()](https://www.arduino.cc/reference/en/language/functions/communication/serial/read/)?

  Cuando utilizamos la función `Serial.read()` en la programación para Arduino, estás leyendo un byte de datos del búfer de entrada del puerto serial. 

- Si hay al menos un byte de datos disponible en el búfer del puerto serial (verificado mediante `Serial.available()`), `Serial.read()` devuelve el siguiente byte de datos en forma de un valor entero (`int`).
  
- Si el búfer está vacío (no hay datos disponibles), `Serial.read()` devuelve `-1`. Por lo tanto, es común verificar si `Serial.read()` es igual a `-1` antes de realizar alguna acción con los datos leídos.

Ejemplo de uso típico:

```cpp
if (Serial.available() > 0)
{
  // Hay datos disponibles para leer
  int dato = Serial.read();
  // Realizar alguna acción con el dato leído
} else
    {
      // No hay datos disponibles en el búfer
      Serial.println("Esperando datos...");
    }
```

En este ejemplo, `Serial.read()` se utiliza para leer un byte de datos del búfer del puerto serial. Si hay datos disponibles, se almacena en la variable `dato` y se realiza alguna acción con él. Si el búfer está vacío, no se realiza ninguna acción.

- ¿Qué pasa cuando hago un Serial.read() y no hay nada en el buffer de recepción?

  se complementa con la respuesta anterior Cuando llamamos a `Serial.read()` y no hay nada en el búfer de recepción (es decir, `Serial.available()` devuelve 0), la función `Serial.read()` devuelve `-1`. Esto se utiliza como un indicador de que no hay datos disponibles para ser leídos.

Es importante manejar este escenario correctamente en tu código para evitar comportamientos inesperados o bloqueos usando el `else`:

```cpp
if (Serial.available() > 0) {
  // Hay datos disponibles para leer
  int dato = Serial.read();
  // Realizar alguna acción con el dato leído
} else {
  // No hay datos disponibles en el búfer
  Serial.println("No hay datos disponibles.");
}
```

En este ejemplo, si `Serial.available()` devuelve 0, el programa imprimirá "No hay datos disponibles." en lugar de intentar leer datos del búfer. 


- Un patrón común al trabajar con el puerto serial es este:

```cpp
if(Serial.available() > 0){
    int dataRx = Serial.read()
}
```

- ¿Cuántos datos lee Serial.read()?

La función `Serial.read()` lee un único byte de datos del búfer de recepción del puerto serial. Si hay más de un byte disponible en el búfer, deberíamos llamar a `Serial.read()` varias veces para leer todos los datos presentes o mediante un ciclo `while`.

- ¿Y si quiero leer más de un dato? No olvides que no se pueden leer más datos de los disponibles en el buffer de recepción porque no hay más datos que los que tenga allí.

Si deseamos leer más de un dato y no sabemos cuántos datos están disponibles en el búfer de recepción, necesitamos asegurarnos de no intentar leer más datos de los que realmente están disponibles.

```cpp
while (Serial.available() > 0) {
    int dataRx = Serial.read();  // Lee un byte de datos
    // Realizar alguna acción con el dato leído
}
```

Este bucle `while` seguirá leyendo bytes de datos del búfer de recepción mientras haya datos disponibles. Es una forma de leer todos los datos presentes en el búfer sin intentar leer más allá de la cantidad real de datos disponibles.

Hay quie tener en cuenta que si el búfer está vacío al principio del bucle, el bucle no se ejecutará. Si hay varios bytes en el búfer, se leerán uno por uno en cada iteración del bucle. Esto permite procesar todos los datos disponibles sin intentar leer más allá de la cantidad real de datos en el búfer.

- ¿Qué pasa si te envían datos por serial y se te olvida llamar Serial.read()?

  Si recibimos datos por el puerto serial y olvidamos llamar a `Serial.read()` para leer esos datos, los datos permanecerán en el búfer de recepción del puerto serial. Esto puede llevar a problemas si el búfer se llena y se reciben nuevos datos, ya que los datos antiguos que no se han leído ocuparán espacio en el búfer.

Algunas consecuencias podrian ser:

1. **Búfer Lleno:** Si el búfer de recepción se llena porque no se está leyendo datos, es posible que los nuevos datos enviados por el puerto serial se pierdan o se sobrescriban, ya que el búfer no tiene espacio para almacenarlos.

2. **Retardo en la Lectura:** Si los datos siguen llegando y el búfer está lleno, se pueden producir retardos en la lectura de nuevos datos hasta que se libere espacio en el búfer.

3. **Comportamiento Inesperado:** Dependiendo de cómo manejemos el puerto serial en el programa, podríamos experimentar comportamientos inesperados o bloqueos si no gestionamos el búfer de recepción.

4. **Bloqueo del Programa:** Si el código está esperando datos en el puerto serial pero nunca los lee, puede quedar bloqueado o pausado indefinidamente en esa espera, lo que afectaría el funcionamiento normal del programa.

Para evitar estos problemas, es importante llamar a `Serial.read()` regularmente para leer y procesar los datos que llegan por el puerto serial.
