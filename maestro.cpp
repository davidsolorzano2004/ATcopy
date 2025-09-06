#include "maestro.h"
#include <Arduino.h>

#include <Wire.h>
#define SLAVE_ADDR 1

byte pin[] = {2, 3, 4, 5, 6};//Cambio Sara Machado
byte estado = 0;

const int ledMaestro = 2; // LED local (pin 13 del Arduino)

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(ledMaestro, OUTPUT);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    // Enviar comando al esclavo
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(pin[i]);      // Pin
    Wire.write(estado);      // Estado
    Wire.endTransmission();

    delay(10); // Esperar antes de pedir confirmación

    // Solicitar confirmación
    Wire.requestFrom(SLAVE_ADDR, 8); // "Recibido" = 8 letras
    String respuesta = "";
    while (Wire.available()) {
      char c = Wire.read();
      respuesta += c;
    }

    // Mostrar confirmación
    Serial.println(respuesta);

    // Si el esclavo respondió "Recibido", encender LED local
    if (respuesta == "RECIBIDO") {
      digitalWrite(ledMaestro, HIGH);
      delay(200); // LED encendido un momento
      digitalWrite(ledMaestro, LOW);
    }

    delay(500);
  }

  estado = !estado; // Alternar entre 0 y 1
}

