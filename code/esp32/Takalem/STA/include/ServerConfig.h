#include <WiFi.h>
#include <esp_now.h>

#define WIFI_TIMEOUT 20000
#define SSID "esp32"
#define PASSWORD "12345678"

uint8_t esp_address[] = {0x70, 0xB8, 0xF6, 0x5B, 0xFE, 0x44};

void connectToWiFi() {
  Serial.print("\n[*] Connecting to WiFi");
  WiFi.begin(SSID, PASSWORD);

  unsigned long start_time = millis();

  while ((WiFi.status() != WL_CONNECTED) && (millis() - start_time < WIFI_TIMEOUT)) {
    delay(100);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\n[-] Failed to connect to WiFi");
    Serial.println(WiFi.status());
    return;
  }
  Serial.println("\n[+] Connected to WiFi");
  Serial.println(WiFi.localIP());
  Serial.print("ESP MAC Address: ");
  Serial.println(WiFi.macAddress());
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
