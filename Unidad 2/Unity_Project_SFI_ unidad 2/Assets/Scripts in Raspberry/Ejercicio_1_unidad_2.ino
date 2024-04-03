void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  if(Serial.available())
  {
    if(Serial.read() == '1')
    {
      Serial.print("Hello from Raspberry Pi Pico");
    }
  }
}
