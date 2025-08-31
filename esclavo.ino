#include <Wire.h>

char respuesta[] = "RECIBIDO"; // mensaje fijo de confirmación

void setup() {
  for (int i = 2; i <= 6; i++) {
    pinMode(i, OUTPUT);
  }

  Wire.begin(1);                // Dirección 1
  Wire.onReceive(receiveEvent); // Callback al recibir
  Wire.onRequest(sendEvent);    // Callback al pedir datos
}

void loop() {
  delay(100);
}

int ultimoPin = -1;
int ultimoEstado = -1;

// Recibir comando del maestro
void receiveEvent(int howMany) {
  if (howMany == 2) {
    ultimoPin = Wire.read();
    ultimoEstado = Wire.read();
    if (ultimoPin >= 2 && ultimoPin <= 6) {
      digitalWrite(ultimoPin, ultimoEstado);
    }
  } else {
    while (Wire.available()) Wire.read(); // limpiar buffer
  }
}

// Enviar confirmación al maestro
void sendEvent() {
  Wire.write(respuesta); // enviamos "OK"
}
