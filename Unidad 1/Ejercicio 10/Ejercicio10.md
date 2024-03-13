### **Ejercicio 10: monitor serial**

Para profundizar un poco más en el funcionamiento de los programas vas a usar una herramienta muy interesante llamada monitor o terminal serial. En este curso vas a utilizar ScriptCommunicator. La aplicación la puedes descargar de forma gratuita. Al instalarla en los computadores de la Universidad usa un directorio del usuario y deshabilita la creación de accesos directos en el escritorio y no asocies los archivos .js con ScriptCommunicator.

Para lanzar la aplicación abre el directorio donde la instalaste y lanza el programa ScriptCommunicator.exe

Ingresa al menu Settings, selecciona la pestaña serial port y elige el puerto (el puerto asignado por el sistema operativo a tu sistema de desarrollo) y el BaudRate a 115200. Los demás parámetros los puedes dejar igual.

Selecciona la pestaña console options y allí marca ÚNICAMENTE las opciones: utf8, receive, hex, mixed. En new line at byte coloca None y en Send on enter key coloca None.

En la pestaña serial port ve a la sección general, selecciona como current interface `serial port`. Cierra la ventana de configuración.

<aside>
💡 **Advertencia**

</aside>

IMPORTANTE

No olvides que DEBES TENER conectado el sistema de desarrollo al computador para poder seleccionar el puerto correcto.

Para conectar ScriptCommunicator al microcontrolador, solo tienes que dar click en Connect y para desconectar Disconnect.

<aside>
💡 **Advertencia**

</aside>

ESTO ES CRÍTICO

SOLO UNA APLICACIÓN puede comunicarse a la vez con el microcontrolador. Por tanto, SÓLO una aplicación puede abrir o conectarse al puerto serial que el sistema operativo le asigna al sistema de desarrollo.

Esto quiere decir que no puedes programar el raspberry mientras tienes abierto ScriptCommunicator conectado al puerto serial.


## Solución

Serial port:
![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/511ab14e-69fe-4de0-89a4-9503704e482c)

Console options:
![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/1e2ccd45-e83a-4287-af61-9bb7949bd3c5)


No hay opción de none como dice la instrucción inicial
![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/48905120-e5a5-4a88-8617-1adacfb676d4)


