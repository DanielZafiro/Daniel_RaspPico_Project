### **Ejercicio 17: buffer de recepción**

Así se pueden leer 3 datos que han llegado al puerto serial:

```cpp
if(Serial.available() >= 3){
    int dataRx1 = Serial.read()
    int dataRx2 = Serial.read()
    int dataRx3 = Serial.read()
}
```

¿Qué escenarios podría tener en este caso?

```cpp
if(Serial.available() >= 2){
    int dataRx1 = Serial.read()
    int dataRx2 = Serial.read()
    int dataRx3 = Serial.read()
}
```

Para responder, es necesario que experimentes. ESTOS son los ejercicios que realmente te ayudarán a aprender.


## Solución

```cpp
if(Serial.available() >= 3){
    int dataRx1 = Serial.read()
    int dataRx2 = Serial.read()
    int dataRx3 = Serial.read()
}
```

En este primer escenario, donde la condición es `Serial.available() >= 3`, se está verificando que haya al menos tres bytes disponibles en el búfer de recepción antes de intentar leer. En este caso, si hay exactamente tres o más bytes disponibles, se leerán los tres bytes uno por uno. Si hay menos de tres bytes, el bloque de código no se ejecutará.

```cpp
if(Serial.available() >= 2){
    int dataRx1 = Serial.read()
    int dataRx2 = Serial.read()
    int dataRx3 = Serial.read()
}
```

En el segundo escenario, donde la condición es `Serial.available() >= 2`, estamos verificando que haya al menos dos bytes disponibles en el búfer de recepción antes de intentar leer.

1. **Exactamente dos bytes disponibles:**
   Se leerán los dos bytes uno por uno, y `dataRx1` y `dataRx2` contendrán esos dos bytes.

2. **Tres o más bytes disponibles:**
   Se leerán los dos primeros bytes, y `dataRx1` y `dataRx2` contendrán esos bytes. El tercer byte y cualquier byte adicional permanecerán en el búfer de recepción sin ser leídos.

3. **Menos de dos bytes disponibles:**
   El bloque de código no se ejecutará, ya que no hay suficientes bytes disponibles.

recordar que el uso de `Serial.read()` en Arduino devuelve `-1` si no hay datos disponibles. 
