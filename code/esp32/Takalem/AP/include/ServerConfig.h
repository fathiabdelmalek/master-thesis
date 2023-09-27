#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <esp_now.h>

#define SSID "esp32"
#define PASSWORD "12345678"
#define SERVER_URL "http://192.168.4.3:5000/"

WiFiServer server(80);

void onDataReceived(const uint8_t* mac, const uint8_t* data, int len) {
  String receivedData = String((char*)data);
  Serial.println("Received data: " + receivedData);

  float sensorValue1, sensorValue2;
  sscanf(receivedData.c_str(), "%f,%f", &sensorValue1, &sensorValue2);
}

void createServer() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(SSID, PASSWORD);
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(onDataReceived);
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
