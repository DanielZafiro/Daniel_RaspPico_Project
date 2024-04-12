# Reproductor de musica de la tienda Bubble Pop

## Narrativa

En plena era de los años 2010, donde los CDs compactos aún reinan en el mundo de la música, la tienda de música Bubble Pop se encuentra en el epicentro de la escena musical. Con su reputación como un oasis para los amantes de la música, Bubble Pop se convierte en el punto de encuentro para aquellos que buscan descubrir los últimos éxitos y las melodías más innovadoras.

En este contexto, un artista visionario está a punto de lanzar su último álbum, pero antes de que las masas tengan acceso a él, desea que Bubble Pop ofrezca un adelanto exclusivo a sus visitantes más ávidos. Es aquí donde entra en juego el reproductor de música revolucionario diseñado especialmente para Bubble Pop.

Este innovador reproductor no es simplemente un dispositivo convencional; es una herramienta de inmersión musical. Con la capacidad de establecer límites de reproducción temporal, los visitantes pueden saborear breves fragmentos de cada canción del álbum, despertando su curiosidad y dejándoles ansiando más.

Pero la magia no se detiene aquí. El reproductor también ofrece la opción de ajustar la velocidad de reproducción, permitiendo a los oyentes experimentar la música a diferentes ritmos, desde el tranquilo compás de x1 hasta la emocionante aceleración de x3.

Y como si fuera poco, la funcionalidad de cambio de orden de reproducción añade una capa adicional de emoción y sorpresa. ¿Cada Dos canciones seguidas? ¿Tres? ¿O quizás una secuencia única por dia de la semana? 

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
