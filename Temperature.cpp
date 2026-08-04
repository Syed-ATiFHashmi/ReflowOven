#include <SPI.h>
#include "Config.h"
#include "Temperature.h"
#include <MAX6675.h>

static MAX6675 thermoCouple(PIN_MAX6675_CS, PIN_MAX6675_SO, PIN_MAX6675_SCK);
static float currentTemp = 0.0f;
static unsigned long lastReadMillis = 0;

void beginTemperature() {
  SPI.begin();
  thermoCouple.begin();
  currentTemp = 0.0f;
  lastReadMillis = 0;
}

void updateTemperature() {
  if (millis() - lastReadMillis > 250) {
    lastReadMillis = millis();
    thermoCouple.read();
    currentTemp = thermoCouple.getCelsius();
  }
}

float getTemperature() {
  return currentTemp;
}
