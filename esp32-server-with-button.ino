// https://tinkeriot.com
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);
const int lightPin = 2;

void handleRoot() {
  String html = "<h1>ESP32 Smart Light</h1><button onclick=\"fetch('/on')\">ON</button><button onclick=\"fetch('/off')\">OFF</button>";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(lightPin, HIGH);
  server.send(200, "text/plain", "Light ON");
}

void handleOff() {
  digitalWrite(lightPin, LOW);
  server.send(200, "text/plain", "Light OFF");
}

void setup() {
  pinMode(lightPin, OUTPUT);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
}

void loop() {
  server.handleClient();
}
