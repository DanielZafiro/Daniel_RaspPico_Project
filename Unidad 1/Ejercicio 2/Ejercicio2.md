### **Ejercicio 2: ¿Cómo funciona un microcontrolador?**

Un microcontrolador es un computador dedicado a ejecutar una aplicación específica para resolver un problema muy concreto. Por ejemplo, leer la información de un sensor y transmitir esa información a un computador.

En este curso vas a utilizar un sistema de desarrollo llamado [raspberry pi pico](https://www.raspberrypi.com/products/raspberry-pi-pico/) que cuenta con un microcontrolador que podrás programar.

## Solución

Adicional a las presentaciones y documentación proporcionada en clase..

Un microcontrolador es un dispositivo compacto y autónomo que integra en un solo chip un procesador central, memoria, periféricos de entrada/salida y otros componentes necesarios para controlar un sistema embebido. Está diseñado para ejecutar programas almacenados en su memoria y realizar tareas específicas en sistemas integrados.

Aquí hay una descripción básica de cómo funciona un microcontrolador:

1. **Procesador Central (CPU):** El corazón del microcontrolador es la unidad central de procesamiento (CPU), que ejecuta instrucciones almacenadas en la memoria para llevar a cabo las operaciones necesarias.

2. **Memoria:** Los microcontroladores tienen dos tipos principales de memoria:
   - **Memoria de programa (Flash o EPROM):** Almacena el código del programa que se ejecutará. Este código se carga durante el desarrollo y se mantiene incluso cuando se apaga la alimentación.
   - **Memoria RAM:** Utilizada para almacenar datos temporales y variables durante la ejecución del programa. La RAM se borra cuando se apaga la alimentación.

3. **Periféricos de Entrada/Salida (E/S):** Los microcontroladores están equipados con pines y circuitos que permiten la comunicación con el entorno exterior. Estos periféricos pueden incluir puertos GPIO (Entrada/Salida de Propósito General), UART (Universal Asynchronous Receiver/Transmitter) para comunicación serie, temporizadores, ADC (Convertidor Analógico-Digital), DAC (Convertidor Digital-Analógico), entre otros.

4. **Reloj:** Un microcontrolador tiene un reloj interno que sincroniza las operaciones del procesador. La velocidad del reloj determina la velocidad de ejecución del programa.

5. **Unidad de Control:** Supervisa y controla la ejecución del programa. Se encarga de la secuencia de ejecución de instrucciones, la gestión de interrupciones y otras funciones de control.

6. **Bus de Datos y Direcciones:** Permiten la transferencia de datos y direcciones entre la CPU, la memoria y los periféricos.

7. **Interfaz de Programación:** Durante el desarrollo, el programador utiliza una interfaz de programación para cargar el código en la memoria de programa del microcontrolador.

8. **Alimentación:** Los microcontroladores suelen operar con bajos niveles de voltaje y tienen pines de alimentación para recibir energía.

El programador escribe el código en un lenguaje de programación específico (como C o ensamblador) y luego compila ese código en un formato que el microcontrolador puede ejecutar. El código compilado se carga en la memoria de programa del microcontrolador, y este ejecuta las instrucciones de manera secuencial para realizar las funciones deseadas en el sistema embebido.

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/b51ca630-5d74-4a7f-8714-3eb5e4404da2)


Sobre RAspberry Pi Pico

La Raspberry Pi Pico es una placa de desarrollo que incorpora el microcontrolador RP2040, diseñado por la Fundación Raspberry Pi. Aquí hay algunos detalles adicionales sobre el Raspberry Pi Pico y cómo puedes comenzar a programarlo:

1. **Microcontrolador RP2040:**
   - El RP2040 es un microcontrolador de doble núcleo ARM Cortex-M0+ que funciona a una velocidad de hasta 133 MHz.
   - Tiene 264 KB de RAM y 2 MB de memoria flash para almacenar el código del programa.
   - Ofrece una variedad de periféricos, como pines GPIO, UART, SPI, I2C, PWM y más.

2. **Desarrollo de Software:**
   - La Raspberry Pi Pico se puede programar en lenguajes como MicroPython, C y CircuitPython.
   - Puedes utilizar el software oficial de desarrollo llamado "Thonny" para escribir y cargar tu código en la Raspberry Pi Pico.

3. **Plataforma de Desarrollo:**
   - La Raspberry Pi Pico se puede programar utilizando varios entornos de desarrollo integrado (IDE) como Thonny, VS Code, o cualquier otro compatible con microcontroladores ARM Cortex-M.

4. **Documentación y Recursos:**
   - La Fundación Raspberry Pi proporciona una amplia documentación y recursos para ayudarte a comenzar con la Raspberry Pi Pico. Puedes encontrar tutoriales, guías y ejemplos de código en su sitio web oficial.

5. **Comunidad:**
   - La Raspberry Pi Pico cuenta con una activa comunidad de desarrolladores. Puedes participar en foros, grupos en línea y otros canales para obtener ayuda, intercambiar ideas y aprender de otros usuarios.

6. **Proyectos y Experimentos:**
   - Con la Raspberry Pi Pico, puedes realizar una variedad de proyectos y experimentos, desde controlar luces y motores hasta crear dispositivos IoT y sistemas embebidos más complejos.

![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/4fe05fc1-e94c-44b5-b49c-559208ea5f71)

