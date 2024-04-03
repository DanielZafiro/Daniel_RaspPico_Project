void task()
{
    // Definición de los posibles estados de la tarea
    enum class TaskStates
    {
        INIT,         // Estado inicial
        INSERT_KEY,   // Insertar la llave
        START_TRAIN,  // Encender el tren
        ACCEL_TRAIN,  // Acelerar el tren
        BRAKE_TRAIN   // Frenar el tren
    };

    static TaskStates taskState = TaskStates::INIT; // Estado actual de la tarea
    static uint32_t previous = 0; // Variable para llevar el tiempo transcurrido

    // Switch-case para manejar los diferentes estados de la tarea
    switch (taskState)
    {
        case TaskStates::INIT:
        {
            // Inicialización de la comunicación serial
            Serial.begin(115200);
            // Pasar al estado de insertar la llave
            taskState = TaskStates::INSERT_KEY;
            break;
        }
        case TaskStates::INSERT_KEY:
        {
            // Esperar a que se reciba el comando "1" para insertar la llave
            if (Serial.available() > 0)
            {
                if (Serial.read() == '1')
                {
                    // Indicar que se ha insertado la llave y guardar el tiempo actual
                    Serial.print("Key inserted");
                    previous = millis();
                    // Pasar al estado de encender el tren
                    taskState = TaskStates::START_TRAIN;
                }
            }
            break;
        }
        case TaskStates::START_TRAIN:
        {
            // Esperar 3 segundos antes de encender el tren
            if (millis() - previous > 3000)
            {
                // Indicar que se ha encendido el tren y guardar el tiempo actual
                Serial.print("Train started");
                previous = millis();
                // Pasar al estado de acelerar el tren
                taskState = TaskStates::ACCEL_TRAIN;
            }
            break;
        }
        case TaskStates::ACCEL_TRAIN:
        {
            // Esperar 3 segundos antes de acelerar el tren
            if (millis() - previous > 3000)
            {
                // Indicar que se está acelerando el tren y guardar el tiempo actual
                Serial.print("Train accelerating");
                previous = millis();
                // Pasar al estado de frenar el tren
                taskState = TaskStates::BRAKE_TRAIN;
            }
            break;
        }
        case TaskStates::BRAKE_TRAIN:
        {
            // Esperar 3 segundos antes de frenar el tren
            if (millis() - previous > 3000)
            {
                // Indicar que se está frenando el tren y guardar el tiempo actual
                Serial.print("Train braking");
                previous = millis();
                // Regresar al estado inicial de insertar la llave para repetir el ciclo
                taskState = TaskStates::INSERT_KEY;
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
    // Llamar a la función task para iniciar la tarea
    task();
}

void loop()
{
    // Llamar a la función task en cada iteración del loop
    task();
}
