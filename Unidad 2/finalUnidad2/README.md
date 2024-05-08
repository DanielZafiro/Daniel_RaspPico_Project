# Unit 2 project: music player

**This README will hold all documentation related to the final Unit 2 project**

## Objective:

**The controller must be able to:**
1. make a variable available or unavailable.
2. change the speed at which it is changed.
3. change the value at the beginning.
4. Keep the led working.


**the graphic interface must be able to**

1. Have visual forms of interaction for all three variables.
2. Set the three variables: initial value, speed, if it's available, wether it's increasing or decreasing.
3. To activate or deactivate.
4. Be creative and have a god aesthetic.


## Project overview:

We're trying to incorporate the necessary parts asked in a music player

Our three variables are:

Song (number in a playlist)

Volume (from 0 to 20)

Minute (Where is the song right now in a 3:50 minute long song)

Our initial design of it's interface is this:

![alt text](IMG_6187(2).PNG)

More on the interface can be read about below in it's own section


An idea thrown around in the team, that the speed of the song and volume variable work as frequency, aka how many songs/volume levels will be skipped the next time a change happens, and this change will happen only when the time slider gets to 3 minutes

the slider will change either by frequency or speed between selected time stamps

the time slider, will have key points and it will be thru those points that the skips will happen, wether it's by how many keypoints will skip, or in how many seconds the skip will happen.

The keypoints and exact values of each variable have been decided and they will be:

Volume: 0-10. they're all int, 0 is mute
Songs: 1-10. they're all int
TimeStamps: the songs will all last 2 minutes: 0:00, 0:30, 1:00, 1:30, 2:00.



## status diagram:

This was the first idea for a status diagram we thought of:

![alt text](IMG_6188(2).PNG)



## Graphic interface:

We begun with the design we wanted to have for the project:

![alt text](IMG_6187(2).PNG)

This design is subject to change


## Microcontroller:

The start of the project is actually here, we must first try to make this project work

First we must try to emulate how only one of the variables would work on the controller.

It's also a good way to check the led is always working.

Firstly an array will be made, it'll have all the possible values of the variable, in this case 0 thru 10


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


## Interfaz Grafica

![2](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/aab4e6f0-7b36-4afb-a594-b68cb3e7cb51)
![1](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/3853a998-d504-4746-8be0-d13fa7a27f32)
![3](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/6f239f7a-2cf4-418f-8327-2af2d58239b3)
![4](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/e77958e7-f836-4170-b1be-fea979c2e295)
![5](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/c3c8420e-3df7-4c21-8267-a7795b91277a)
![6](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/dd7ed84f-bf6d-447e-8b05-0641fce30851)
![7](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/a823746f-befe-40c7-b010-830139dec765)
![8](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/b83323f7-cadf-4acc-9103-bd731fd515ce)
![9](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/8bf85615-0db2-4ecb-ab87-b9df012c9e94)
![10](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/8ad857e1-2804-4ef8-b9b7-02987c4d04a6)
![11](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/3e35edb8-19e9-4c66-8788-b72121efa769)
![12](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/a4eae7ee-4d2a-4f8c-98b6-5b144c369efc)
![13](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/d54b4b79-85ea-452c-8699-196d9b2841d0)
![14](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/188873ac-1959-4a74-abcf-79b6542b9291)
![15](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/b311e424-5391-48c3-a369-13a93660f8b6)
![16](https://github.com/Mafe-Garcia/estrellitas_misc/assets/66543657/78d1dd89-9039-413d-b00a-1858a0309c6c)

