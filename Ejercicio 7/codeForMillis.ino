unsigned long myTime; //variable global que almacena el tiempo en myTime

void setup() {
  Serial.begin(9600); // Velocidad de transmision de de 9600 baudios entre Raspberry Pi Pico y el dispos. conectado
}
void loop() {
  Serial.print("Time: "); // Imprime el texto predecesor "Time: "
  myTime = millis(); 

  Serial.println(myTime); // Imprime el tiempo desde que el programa inició
  delay(1000);          // Espera un segundo  para no enviar cantidades de datos masivos 
}
