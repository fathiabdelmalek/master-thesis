#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_TIMEOUT 20000
// #define SSID "idoom"
// #define PASSWORD "0672631822f"
// #define SERVER_URL "http://192.168.1.21:5000/"
#define SSID "D-Link_DAP-1360"
#define PASSWORD ""
#define SERVER_URL "http://172.16.7.53:5000/"


void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(SSID, PASSWORD);

  unsigned long start_time = millis();

  while ((WiFi.status() != WL_CONNECTED) && (millis() - start_time < WIFI_TIMEOUT)) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect to WiFi");
    Serial.println(WiFi.status());
    return;
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
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
