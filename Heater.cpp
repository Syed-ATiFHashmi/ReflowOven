#include "Heater.h"
#include "Config.h"
#include <Arduino.h>

static int currentPower = 0;

void beginHeaters() {
  pinMode(PIN_HEATER1, OUTPUT);
  pinMode(PIN_HEATER2, OUTPUT);
  pinMode(PIN_FAN, OUTPUT);

  digitalWrite(PIN_HEATER1, LOW);
  digitalWrite(PIN_HEATER2, LOW);
  digitalWrite(PIN_FAN, LOW);
  currentPower = 0;
}

void setHeaterPower(int power) {
  if (power <= 0) {
    currentPower = 0;
    analogWrite(PIN_HEATER1, 0);
    analogWrite(PIN_HEATER2, 0);
    return;
  }

  if (power > 1023) {
    power = 1023;
  }

  currentPower = power;
  analogWrite(PIN_HEATER1, power);
  analogWrite(PIN_HEATER2, power);
}

void setFan(bool enabled) {
  digitalWrite(PIN_FAN, enabled ? HIGH : LOW);
}

void stopHeaters() {
  setHeaterPower(0);
  setFan(false);
}

int getHeaterPower() {
  return currentPower;
}
