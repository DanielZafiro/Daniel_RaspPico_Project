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

            uint32_t var1 = 5; // Declara la variable var1 inicializadad en 5
            uint32_t var2 = 25; // Declara la variable var2 inicializadad en 25

	          uint32_t *pvar1 = &var1; // Declara un puntero pvar1 que apunta a la direccion var1 y Almacena en pvar1 la dirección de var1
            uint32_t *pvar2 = &var2; // Declara un puntero pvar2 que apunta a la direccion var2 y Almacena en pvar2 la dirección de var2

            // Envía por el serial el contenido de var usando el apuntador pvar. 
            Serial.print("Antes del intercambio: x = ");
            Serial.print(*pvar1);
            Serial.print(", y = ");
            Serial.println(*pvar2);
            Serial.print('\n');

            *pvar1 = 25; // Escribir un nuevo valor en pvar1 mediante el puntero en este caso intercambiado
            *pvar2 = 5;

	    // Envía por el serial el contenido actualizado de var usando el apuntador pvar. 
            Serial.print("Despues del intercambio: x = ");
            Serial.print(*pvar1);
            Serial.print(", y = ");
            Serial.println(*pvar2);
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
