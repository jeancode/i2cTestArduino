#include <Wire.h>

// Dirección del esclavo I2C
const int i2cAddress = 8;
String receivedString = "";

void setup() {
  // Inicializar el bus I2C como esclavo con la dirección especificada
  Wire.begin(i2cAddress);

  // Establecer la función de recepción de datos
  Wire.onReceive(receiveEvent);

  // Establecer la función de solicitud de datos
  Wire.onRequest(sendData);

  // Iniciar el monitor serial
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Esclavo I2C ESP32 listo.");
}

void loop() {
  // No es necesario hacer nada en el bucle principal
  delay(100);
}

// Función para manejar la recepción de datos del maestro
void receiveEvent(int numBytes) {
  while (Wire.available()) {
    char receivedChar = Wire.read();
    if (receivedChar == '\n') { // Carácter '\n' indica fin de la cadena
      Serial.print("Datos recibidos desde el maestro: ");
      Serial.println(receivedString);
       Wire.write(receivedString.c_str());
      receivedString = ""; // Limpiar la cadena para recibir nuevos datos
    } else {
      receivedString += receivedChar;
    }
  }


}

// Función para enviar datos al maestro cuando se solicita
void sendData() {
  // Datos a enviar al maestro
  String dataToSend = "Datos desde el esclavo";

  for(int i = 25; i <= 500;i++){
    dataToSend += String(i);
  }

  // Enviar los datos al maestro a través de I2C
  Wire.write(dataToSend.c_str());
}
