#include "Config.h"
#include "Temperature.h"
#include "Heater.h"
#include "ReflowEngine.h"
#include "WebServer.h"

void setup(){
  beginTemperature();
  beginHeaters();
  beginEngine();
  beginWebServer();
}
void loop(){
  updateTemperature();
  updateEngine();
  handleWebServer();
}
