static void interchangeVar(uint32_t &a, uint32_t &b)
{
    uint32_t temp = a;
    a = b;
    b = temp;
}

static void printInterchange(uint32_t x, uint32_t y)
{
    Serial.print("Intercambio: x = ");
    Serial.print(x);
    Serial.print(", y = ");
    Serial.println(y);
    Serial.print('\n');
}

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
            Serial.read();
            uint32_t x = 5;
            uint32_t y = 25;
            printInterchange(x, y);
            interchangeVar(x, y);
            printInterchange(x, y);
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
