const int BUFFER_SIZE = 32; // capacidad de almacenamiento 32 bytes
uint8_t taskBuffer[BUFFER_SIZE]; // Buffer para almacenar datos
uint8_t dataCounter = 0; // lleva la cuenta de la cantidad de datos almacenados en el buffer

enum class TaskStates
{
  INIT,
  WAIT_DATA
};

TaskStates taskState = TaskStates::INIT; // variable que indica el estado actual de la tarea, inicializada en INIT.

void processSerialData() // funcion para leer datos del puerto serial y almacenarlos en el buffer.
{
  // Verifica si hay datos disponibles en el puerto serial
  while (Serial.available() > 0)
  {
    // Lee un byte de datos del puerto serial
    uint8_t newData = Serial.read();

    // Almacena el dato en el buffer si hay espacio disponible
    if (dataCounter < BUFFER_SIZE)
    {
      taskBuffer[dataCounter] = newData;
      dataCounter++;
    } else
      {
      // Si el buffer está lleno, se puede implementar manejo de desbordamiento 
      Serial.println("Buffer lleno. Datos perdidos.");

     delay(1000); // delay para el mensaje 
     break; 
      }
   }
}

void task1() // lógica principal de la tarea
{
  switch (taskState)
    {
    case TaskStates::INIT:
      // Inicialización de la tarea
      Serial.begin(115200);
      taskState = TaskStates::WAIT_DATA; // Cambia al estado de espera de datos
      break;

    case TaskStates::WAIT_DATA:
      // Procesa los datos del puerto serial
      processSerialData();

      // Muestra la cantidad de datos recibidos hasta ahora
      Serial.print("Cantidad de datos: ");
      Serial.println(dataCounter);

      delay(3000);  // Espera 3 segundos entre llamadas a la tarea
      break;

    default:
      break;
   }
}

void setup()
{
  task1(); // Llama a la tarea para la inicialización
}

void loop()
{
  task1(); // Llama a la tarea en el loop principal para que sea un buble infinito
}
