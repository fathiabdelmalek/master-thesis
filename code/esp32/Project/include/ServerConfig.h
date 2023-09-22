#include <WiFi.h>
#include <WiFiAP.h>
#include <HTTPClient.h>

#define WIFI_TIMEOUT 20000
#define SSID "ESP32-Fathi"
#define PASSWORD "fathi2001"
#define SERVER_URL "http://192.168.4.2:5000/"

WiFiServer server(80);

void createServer() {
  WiFi.softAP(SSID, PASSWORD);
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
}

void sendJson(String word) {
  String payload = "{\"word\": \"" + word + "\"}";

  WiFiClient client;
  HTTPClient http;

  if (!http.begin(client, SERVER_URL)) {
    Serial.println("Unable to connect to server");
    return;
  }
  
  http.addHeader("Content-Type", "application/json");
  
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode <= 0) {
    Serial.println("Error sending POST request");
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    return;
  }
  String response = http.getString();
  Serial.println("HTTP Response code: " + String(httpResponseCode));
  Serial.println("Server response: " + response);
}
