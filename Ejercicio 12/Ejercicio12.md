### **Ejercicio 12: punteros**

Vas a explorar un concepto fundamental de los lenguajes de programación C y C++. Se trata de los punteros. Para ello, te voy a proponer que escribas el siguiente programa. Para probarlo usa ScriptCommunicator.

```cpp
void task1()
{
    enum class Task1States    {
        INIT,
        WAIT_DATA
    };
    static Task1States task1State = Task1States::INIT;

    switch (task1State)
    {
    case Task1States::INIT:
    {
        Serial.begin(115200);
        task1State = Task1States::WAIT_DATA;
        break;
    }

    case Task1States::WAIT_DATA:
    {
        // evento 1:        // Ha llegado al menos un dato por el puerto serial? 
       if (Serial.available() > 0)
        {
            // DEBES leer ese dato, sino se acumula y el buffer de recepción del serial se llenará.   
            Serial.read();

            uint32_t var = 0; // Declara la variable var inicializadad en 0
	    uint32_t *pvar = &var; // Declara un puntero pvar que apunta a la direccion var y Almacena en pvar la dirección de var.

            // Envía por el serial el contenido de var usando el apuntador pvar. 
            Serial.print("var content: ");
            Serial.print(*pvar);
            Serial.print('\n');

            *pvar = 10; // Escribir un nuevo valor en pvar mediante el puntero

	    // Envía por el serial el contenido actualizado de var usando el apuntador pvar. 
            Serial.print("var content: ");
            Serial.print(*pvar);
            Serial.print('\n');
        }
        break;
    }

    default:
    {
        break;
    }
    }
}

void setup()
{
    task1();
}

void loop()
{
    task1();
}
```

¿No te está funcionando? No olvides que en un ESTADO siempre esperas eventos. Si estás enviando el evento?

La variable `pvar` se conoce como puntero. Simplemente es una variable en la cual se almacenan direcciones de otras variables. En este caso, en pvar se almacena la dirección de `var`. Nota que debes decirle al compilador el tipo de la variable (uint32_t en este caso) cuya dirección será almacenada en pvar.

Ejecuta el programa. Observa lo que hace. Ahora responde las siguientes preguntas mediante un ejercicio de ingeniería inversa:

- ¿Cómo se declara un puntero?
- ¿Cómo se define un puntero? (cómo se inicializa)
- ¿Cómo se obtiene la dirección de una variable?
- ¿Cómo se puede leer el contenido de una variable por medio de un puntero?
- ¿Cómo se puede escribir el contenido de una variable por medio de un puntero?

**Advertencia**

IMPORTANTE

No avances hasta que este ejercicio no lo tengas claro.

## Solución

El codigo me devuelve esto
![image](https://github.com/DanielZafiro/Daniel_RaspPico_Project/assets/66543657/cc15ca40-180d-4277-b544-aa6480f6fcaa)

var content: 0 

var content: 10

Este código utiliza punteros para trabajar con variables en memoria. muestra cómo utilizar un puntero para acceder y modificar el contenido de una variable en memoria.
paso a paso del código:

1. **Declaración de la variable `var` y el puntero `pvar`:**
   ```cpp
   uint32_t var = 0;
   uint32_t *pvar = &var;
   ```
   - Se declara una variable `var` de tipo `uint32_t` (entero sin signo de 32 bits) e inicializada en 0.
   - Se declara un puntero `*pvar` de tipo `uint32_t` que apunta a la dirección de memoria de la variable `var`.

2. **Impresión del contenido de `var` usando el puntero:**
   ```cpp
   Serial.print("var content: ");
   Serial.print(*pvar);
   Serial.print('\n');
   ```
   - Se imprime el contenido de la variable `var` utilizando el puntero `pvar` y el operador de desreferencia `*`. El operador `*pvar` accede al valor almacenado en la dirección de memoria apuntada por `pvar`.

3. **Escritura del valor de `var` usando el puntero:**
   ```cpp
   *pvar = 10;
   ```
   - Se utiliza el puntero `pvar` y el operador de desreferencia `*` para asignar el valor 10 a la variable `var`. Esto cambia el contenido de la memoria a la que apunta `pvar`.

4. **Impresión del contenido actualizado de `var` usando el puntero:**
   ```cpp
   Serial.print("var content: ");
   Serial.print(*pvar);
   Serial.print('\n');
   ```
   - Se imprime nuevamente el contenido de la variable `var` después de la actualización, utilizando el puntero `pvar`.

Un puntero es una variable que almacena la dirección de memoria de otra variable. Aquí te explico cómo se declara un puntero, cómo se define (inicializa) y cómo se obtiene la dirección de una variable:

### 1. Declaración de un Puntero:

```cpp
// Declaración de un puntero a un entero
int *ptr;
```

- `int *ptr;`: Declara un puntero llamado `ptr` que apunta a un entero (`int`). El asterisco (*) indica que `ptr` es un puntero.

### 2. Definición (Inicialización) de un Puntero:

#### a. Inicialización directa con la dirección de una variable existente:

```cpp
int x = 10;
int *ptr = &x;
```

- `int x = 10;`: Declara e inicializa una variable `x` con el valor 10.
- `int *ptr = &x;`: Inicializa el puntero `ptr` con la dirección de memoria de la variable `x` utilizando el operador de dirección (`&`).

  en el codigo del ejercicio es:

```cpp
  uint32_t var = 0;
  uint32_t *pvar = &var;
```

#### b. Inicialización a nullptr (puntero nulo):

```cpp
int *ptr = nullptr;
```

- `int *ptr = nullptr;`: Inicializa el puntero `ptr` con un valor nulo. Es una buena práctica inicializar los punteros que no apuntan a ninguna dirección de memoria con `nullptr`.

### 3. Obtención de la Dirección de una Variable:

```cpp
int y = 20;
int *ptr = &y;
```

- `int y = 20;`: Declara e inicializa una variable `y` con el valor 20.
- `int *ptr = &y;`: Obtiene la dirección de memoria de la variable `y` y la asigna al puntero `ptr` utilizando el operador de dirección (`&`).


### 4. Leer el Contenido de una Variable mediante un Puntero:

```cpp
int x = 42;
int *ptr = &x;  // Inicializar el puntero con la dirección de x

// Leer el contenido de x mediante el puntero
int valor = *ptr;

// Ahora 'valor' contiene el mismo valor que 'x'
```

En este ejemplo, `*ptr` se utiliza para acceder al contenido de la variable a la que apunta el puntero. El contenido de `x` se copia en la variable `valor`. Si `x` es modificada posteriormente, `valor` no se actualiza automáticamente.

### 5. Escribir en el Contenido de una Variable mediante un Puntero:

```cpp
int x = 42;
int *ptr = &x;  // Inicializar el puntero con la dirección de x

// Escribir un nuevo valor en x mediante el puntero
*ptr = 99;

// Ahora, el contenido de x se ha actualizado a 99
```

En este caso, `*ptr` se utiliza para asignar un nuevo valor a la variable a la que apunta el puntero. Después de esta operación, el contenido de `x` se ha modificado a 99.

Es importante asegurarse de que el puntero esté inicializado correctamente y de que apunte a una dirección de memoria válida. Además, tener cuidado con el uso de punteros nulos y evita acceder a la memoria de manera desreferenciada si no se está seguro de que contiene datos válidos.
