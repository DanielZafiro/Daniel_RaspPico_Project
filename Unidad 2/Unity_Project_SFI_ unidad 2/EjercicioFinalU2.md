# Reproductor de musica de la tienda Bubble Pop

## Narrativa

## Procedimiento

Queremos un reproductor de música controlado por comandos enviados desde Unity a través del puerto serial al microcontrolador. 

1. **Definir los comandos desde Unity:** En Unity, definiremos botones gráficos que enviarán comandos al microcontrolador a través del puerto serial. Estos comandos serán para inicilizar el reproductor, cambiar la canción, ajustar el volumen, cambiar la velocidad de reproducción, cambiar el tiempo de duracion de la reproduccion, pausar, reproducir la siguiente canción y detener la reproducción.

2. **Configuración inicial del reproductor:** En el microcontrolador, implementaremos un estado de configuración inicial donde solicitaremos al usuario todos los parámetros necesarios para iniciar la reproducción, como la canción inicial, el volumen, la duración de la canción, la velocidad de reproducción y la configuración de salto entre canciones.

3. **Control de reproducción:** Implementaremos la lógica para controlar la reproducción de la música en el microcontrolador, incluyendo la reproducción, pausa, cambio de canción, ajuste de volumen, cambio de velocidad de reproduccion, cambio de tiempo de duracion de reproduccion y detención.

4. **Interfaz de usuario en Unity:** Crearemos una interfaz de usuario en Unity con botones gráficos para permitir al usuario enviar comandos al microcontrolador. Estos botones activarán los comandos correspondientes según las acciones que el usuario desee realizar y mostrarán las canciones, lo que se reproduce y como está configurado.

5. **Comunicación serial:** Estableceremos la comunicación serial entre Unity y el microcontrolador para enviar los comandos desde Unity al microcontrolador y viceversa.

6. **Pruebas y depuración:** Probaremos el sistema para asegurarnos de que funcione correctamente y solucionaremos cualquier problema que surja durante el proceso.

## Implementación en el microcontrolador

## Implementación en Unity

## Interfaz Grafica
