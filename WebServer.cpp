#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WebServer.h"
#include "Temperature.h"
#include "WebPage.h"

const char* ssid = "ActNet";
const char* password = "Syed$%254825";

ESP8266WebServer server(80);

static void handleRoot() {
  server.send_P(200, "text/html", PAGE);
}

static void handleData() {
  float temp = getTemperature();
  String json = "{\"temp\":" + String(temp, 1) + "}";
  server.send(200, "application/json", json);
}

void beginWebServer() {
  Serial.println();
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void handleWebServer() {
  server.handleClient();
}
