#include "Arduino.h"
#include "Pir.h"

Pir::Pir(int pin) {
  this->pin = pin;
  pinMode(pin, INPUT);
}

bool Pir::isDetected() {
  return digitalRead(pin) == HIGH;
}

