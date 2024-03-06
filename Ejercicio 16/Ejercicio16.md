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
