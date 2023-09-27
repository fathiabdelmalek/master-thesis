#include <WiFi.h>
#include <HTTPClient.h>
#include <esp_now.h>

#define WIFI_TIMEOUT 20000
#define SSID "esp32"
#define PASSWORD "12345678"

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

  esp_err_t result = esp_now_send(NULL, (uint8_t*) payload.c_str(), payload.length());
  if (result == ESP_OK)
    Serial.println("Data sent successfully");
  else
    Serial.println("Error sending data");
  delay(1000);
}
