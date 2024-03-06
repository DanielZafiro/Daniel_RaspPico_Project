### **Ejercicio 3: ¿Cómo puedes programar el microcontrolador?**

Para programar el microcontrolador vas a necesitar:

- Un editor de código de C++, por ejemplo arduino IDE.
- Varios programas que permitan transformar el código de C++ a instrucciones de máquina (compilador).
- Almacenar las instrucciones de máquina en la memoria flash del microcontrolador.

Sigue estos pasos:

- Descarga la versión .ZIP del IDE de arduino [versión 1.8.19](https://downloads.arduino.cc/arduino-1.8.19-windows.zip)
- Descomprime el archivo .ZIP
- Busca la carpeta donde está el archivo arduino.exe.
- Abre el programa arduino.exe.
- Sigue las instrucciones de la sección Installing via Arduino Boards Manager que encontrarás en [este](https://github.com/earlephilhower/arduino-pico#installing-via-arduino-boards-manager) repositorio.

Ahora vas a probar que puedes programar el raspberry pi pico:

- Conecta al computador el raspberry pi pico.
- En el menú Herramientas/Placa/Raspberry PI selecciona la tarjeta Raspberry Pi Pico.
- En el menú Herramientas/Puerto selecciona el puerto asignado por el sistema operativo al raspberry pi pico. Toma nota del nombre porque este mismo nombre lo usarás con otras aplicaciones (en mi caso es el COM5).

Ingresa el siguiente programa:

```cpp
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  static uint32_t previousTime = 0;
  static bool ledState = true;

  uint32_t currentTime = millis();

  if( (currentTime - previousTime) > 100){
    previousTime = currentTime;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }
}
```

Por último presiona el ícono Subir, el segundo ubicado en la esquina superior izquierda. Al hacer esto ocurrirán varias cosas:

- Se transformará el programa de código C++ a lenguaje de máquina.
- Se enviará el código de máquina del computador a la memoria flash del raspberry pi a través del puerto serial que el sistema operativo le asignó a la tarjeta.

Deberás ver el LED ubicado al lado del conectar USB enciendo y apagando muy rápido.

Si quieres practicar también en un entorno simulado te dejo [este](https://wokwi.com/) enlace.

### **Ejercicio 3a: retrieval practice (evaluación formativa)**

En este punto te voy a pedir que en la carpeta del ejercicio 3 coloques bajo control de versión el programa y practiques lo que estudiaste en la introducción de control de versión.

- Conforma tu equipo de trabajo (recuerda que el equipo es de dos o y tres personas, NO UNA).
- Únete al enlace que te compartí al principio de la página. Esto lo hace cada miembro del equipo.

**Advertencia**

MUY IMPORTANTE

DOS PERSONAS no pueden trabajar al mismo tiempo sobre el mismo archivo cuando el proyecto está bajo control de versión porque se crean conflictos, es decir, el sistema no sabe cuál de las dos versiones del archivo es la correcta.

- Ve a la terminal y clona el repositorio.
- Sube al repositorio local el archivo del ejercicio 3 en una carpeta con su nombre
- Envía el archivo al repositorio remoto
- Usa el mismo código del ejercicio, pero esta vez cambia el 100 por un 500. Observa el resultado de este cambio.
- Una vez termines el programa, lo veas funcionando y documentes el efecto del cambio, `DEBES cerrar el IDE de Arduino`.
- Regresa a la terminal. Realiza un commit con esta nueva versión del programa en la carpeta del ejercicio 3.
- Ahora añade el archivo README.md. Coloca el nombre del equipo, el nombre de los integrantes y el ID. Coloca en el archivo el resultado del cambio de 100 a 500. Describe lo que viste.
- Realiza un nuevo commit para incluir el archivo README.md con la documentación.
- Envía los cambios del repositorio local al remoto.


## Solución Ejercicio 3

**Conclusiones de la actividad 3** 

Inicialmente es necesario instalar el editor de codigos en este caso Arduino IDE, una vez instalada es importante que reconozca cual es board en la que vamos a trabajar como es un placa reconocida para ambitos educativos y profesionales vamos a instalarle un manejador(Raspberry PICO), luego debemos conectar la placa y en tools seleccionar en que puerto esta conectada, luego copiamos y pegamos el cogido en el editor con el codigo en 100, el LED parpadeaba muy rapido porque en la construccion del coddigo por intuicion la frecuencia entre mas cerca a cero mas rapida sera por lo tanto el LED en 100 parapderara muy rapido

Que hace el codigo: 


https://github.com/vera-perez-upb/sfi-estudiantes-202310-DanielZafiro/assets/66543657/914205f0-2dde-48c6-becf-f3a7f11f7812 

*En la imagen el codigo con el LED en 100:*

![IDE RP PICO LED 100](https://github.com/vera-perez-upb/sfi-estudiantes-202310-DanielZafiro/assets/66543657/d8076077-6a8f-460b-bcad-bad185a1ebef)

## Solución Ejercicio 3a

**Conclusiones** 

Cuando cambiamos en el codigo la frecuencia de 100 a 500 el LED parpadeaba mucho mas lento.


https://github.com/vera-perez-upb/sfi-estudiantes-202310-DanielZafiro/assets/66543657/344952cc-123d-444c-99e5-3ce490b1e180


*En la imagen el codigo con el LED en 500:*

![IDE RP PICO LED 500](https://github.com/vera-perez-upb/sfi-estudiantes-202310-DanielZafiro/assets/66543657/6e484d55-2513-42f5-8ca7-7ff15363f841)
