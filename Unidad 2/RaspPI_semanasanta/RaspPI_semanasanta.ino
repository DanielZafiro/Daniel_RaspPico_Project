void task()
{
    enum class TaskStates
    {
        INIT, // Inicializamos los protocolos de comunicacion y la maquina de estados
        WAIT_INIT,
        INSERT_KEY,
        START_TRAIN,
        ACCEL_TRAIN,
        BRAKE_TRAIN,
        SEND_EVENT
    };

    static TaskStates taskState = TaskStates::INIT;
    static uint32_t previous = 0;
    static u_int32_t counter = 0;

    static void counter()
    {
            uint32_t current = millis();
            if ((current - previous) > 3000)
            {
                previous = current;
                Serial.print(counter);
                counter++;
            }
    }

    switch (taskState)
    {
        case TaskStates::INIT:
        {
            Serial.begin(115200);
            taskState = TaskStates::WAIT_INIT;
            break;
        }
        case TaskStates::WAIT_INIT:
        {
            if (Serial.available() > 0)
            {
                if (Serial.read() == '1')
                {
                    previous = 0; // Force to send the first value immediately
                    taskState = TaskStates::SEND_EVENT;
                }
            }
            break;
        }
        case TaskStates::INSERT_KEY:
        {
            if (Serial.available() > 0)
            {
                if (Serial.read() == '1')
                {
                    taskState = TaskStates::WAIT_INIT;
                }
            }
            break;
        }
        case TaskStates::START_TRAIN:
        {
            if (Serial.available() > 0)
            {
                if (Serial.read() == '2')
                {
                    taskState = TaskStates::WAIT_INIT;
                }
            }
            break;
        }
        case TaskStates::ACCEL_TRAIN:
        {
            counter()

            if (Serial.available() > 0)
            {
                if (Serial.read() == '2')
                {
                    taskState = TaskStates::WAIT_INIT;
                }
            }
            break;
        }
        case TaskStates::BRAKE_TRAIN:
        {
             counter()

            if (Serial.available() > 0)
            {
                if (Serial.read() == '2')
                {
                    taskState = TaskStates::WAIT_INIT;
                }
            }
            break;
        }

        case TaskStates::SEND_EVENT:
        {
            counter()

            if (Serial.available() > 0)
            {
                if (Serial.read() == '2')
                {
                    taskState = TaskStates::WAIT_INIT;
                }
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
    task();
}

void loop()
{
    task();
}
