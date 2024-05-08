void task()
{
    enum class TaskStates
    {
        INIT,
        WAIT_INIT,
        SEND_EVENT,
        VARIABLE_CHANGE
    };
    static TaskStates taskState = TaskStates::INIT;
    uint32_t volumen[] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    static uint32_t toPrint = 0;
    static bool sigue = false;
  
    

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
          if (Serial.available()>0)
          {
            const char c = Serial.read();
            if (c == 's')
            {
              Serial.println("dijo si");
              taskState = TaskStates::VARIABLE_CHANGE;
            }
          }          
            break;
        }
        case TaskStates::VARIABLE_CHANGE:
        {
          Serial.println("escriba un numero entre 0 y 20");
          while(sigue==false){
            
          if (Serial.available() > 0)
            {
              uint32_t input = Serial.parseInt();
              if(input < 0 || input > 20)
              {
                Serial.println("debe estar entre 0 y 20");
              }
              else
              {
              for(int i = 0; i < 21; i++)
              {
                if (input == i)
                {
                  toPrint=volumen[i];
                  Serial.println("si dio");
                  sigue=true;
                  taskState = TaskStates::SEND_EVENT;
                }                
              } 
              }
            }  
          }                
          break;
        }
        case TaskStates::SEND_EVENT:
        {
          Serial.println("Volumen: ");
          Serial.println(toPrint);
           sigue=false;
          taskState = TaskStates::VARIABLE_CHANGE;
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
  pinMode(LED_BUILTIN, OUTPUT);
    task();
}

void loop()
{   
  static bool ledState = true;
  uint32_t currentTime = millis();
  static uint32_t previousTime = 0;

  if( (currentTime - previousTime) > 100){
    previousTime = currentTime;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }
  task();
}
