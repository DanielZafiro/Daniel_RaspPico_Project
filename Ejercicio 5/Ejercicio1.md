### **Ejercicio 1: introducción**

**Advertencia**

RECUERDA LO QUE APRENDERÁS EN ESTE CURSO

En este curso aprenderás a construir aplicaciones interactivas que integren y envíen información desde y hacia el mundo exterior.

¿Recuerdas que te mostré al iniciar el curso un trabajo de grado realizado por estudiantes del programa? Te voy a pedir que veas algunos segundos del video del DEMO de [este](https://tdaxis.github.io/demo.html) trabajo.

Déjame te hablo de nuevo de este sistema porque es un excelente resumen de lo que busco que aprendas con este curso.

La idea de la aplicación es VARIAR las visuales y el audio con la información del movimiento que se captura en tiempo real de una bailarina.

La imagen está dividida en 4 partes. En la esquina superior izquierda observarás   `LA APLICACIÓN INTERACTIVA` que está corriendo en un computador. Esta aplicación se encargará de proyectar las visuales que están en la esquina superior derecha y controlar el software de audio que está en la esquina inferior derecha. Observa la esquina inferior izquierda, allí verás una captura en tiempo real de los movimientos de una bailarina.

¿Cómo se captura este movimiento? Se hace por medio de unos dispositivos que te mostraré en estos videos:

- [Perception Neuron Trailer](https://youtu.be/v72P7q0sIXI).
- [Bailarina controlando un metahumano](https://youtu.be/pynCWHD8RPg).

Los dispositivos que llevan puestos las personas en los videos están compuestos por:

- Un sensor para medir el movimiento.
- Un computador embebido o microcontrolador que lee la información del sensor.
- Un radio de comunicación inalámbrica para transmitir la información leída.

La información se le entrega al computador que ejecuta la aplicación interactiva usando un `PROTOCOLO DE COMUNICACIÓN`. El protocolo es un acuerdo que se establece entre las partes involucradas en la comunicación de tal manera que ambas puedan entenderse.

¿Por qué te muestro todo esto?

Porque en este curso vamos a realizar un recorrido por los elementos que componen este tipo de aplicaciones.

En esta unidad vas a programar un microcontrolador similar al que tienen los dispositivos de captura de movimiento. En las unidades 2 y 3 vas experimentar con dos tipos de protocolos de comunicación. Finalmente, en la unidad 4 construirás una aplicación simple que integre todos los elementos y lo que aprendiste en las unidades previas.

**Advertencia**

ESTO ES MUY IMPORTANTE

Las aplicaciones que realizarás serán simples, PERO si lo analizas te darás cuenta que contienen todos los elementos necesarios para que entiendas cómo funcionan las aplicaciones que te mostré en los videos.
