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
