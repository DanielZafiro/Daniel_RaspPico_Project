static void processData(uint8_t *pData, uint8_t size, uint8_t *res)
{
  uint8_t sum = 0;
  for(int i = 0; i < size; i++)
    {
     sum = sum + (pData[i] - 0x30);
    }
  *res = sum;
}

enum class Task1States
{
  INIT,
  WAIT_DATA
};

static Task1States task1State = Task1States::INIT;
static uint8_t rxData[5];
static uint8_t dataCounter = 0;

void task1()
{
  switch(task1State)
    {
    case Task1States::INIT:
        {
      Serial.begin(115200);
      task1State = Task1States::WAIT_DATA;
      break;
        }
    
    case Task1States::WAIT_DATA:
    {
      // Evento 1:

      if(Serial.available() > 0)
        {
        rxData[dataCounter] = Serial.read();
        dataCounter++;
        if(dataCounter == 5)
            {
              uint8_t result = 0;
              processData(rxData, dataCounter, &result);
              dataCounter = 0;
              Serial.print("result: ");
              Serial.print(result);
              Serial.print('\n');
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
  task1();
}

void loop()
{
  task1();
}
