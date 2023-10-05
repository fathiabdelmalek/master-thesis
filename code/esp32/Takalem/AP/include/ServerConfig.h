#include <WiFi.h>
// #include <esp_now.h>

#define SSID "esp32"
#define PASSWORD "12345678"
#define CHANNEL 1
#define HIDE_SSID true
#define MAX_CONNECTIONS 2
#define SERVER_URL "http://192.168.4.3:5000/"

uint8_t esp_address[] = {0x70, 0xB8, 0xF6, 0x5B, 0xFE, 0x44};

WiFiServer server(80);

// void onDataReceived(const uint8_t* mac, const uint8_t* data, int len) {
//   String receivedData = String((char*)data);
//   Serial.println("Received data: " + receivedData);

//   float sensorValue1, sensorValue2;
//   sscanf(receivedData.c_str(), "%f,%f", &sensorValue1, &sensorValue2);
// }

void createServer() {
  WiFi.mode(WIFI_AP);
  Serial.println("\n[*] Creating ESP32 AP");
  WiFi.softAP(SSID, PASSWORD, CHANNEL, HIDE_SSID, MAX_CONNECTIONS);
  Serial.print("[+] AP Created with IP Gateway ");
  Serial.println(WiFi.softAPIP());
  Serial.print("ESP MAC Address: ");
  Serial.println(WiFi.macAddress());
  server.begin();
  // if (esp_now_init() != ESP_OK) {
  //   Serial.println("Error initializing ESP-NOW");
  //   return;
  // }
  // esp_now_register_recv_cb(onDataReceived);
}

// void sendJson(String word) {
//   String payload = "{\"word\": \"" + word + "\"}";

//   WiFiClient client;
//   HTTPClient http;

//   if (!http.begin(client, SERVER_URL)) {
//     Serial.println("Unable to connect to server");
//     return;
//   }
  
//   http.addHeader("Content-Type", "application/json");
  
//   int httpResponseCode = http.POST(payload);

//   if (httpResponseCode <= 0) {
//     Serial.println("Error sending POST request");
//     Serial.println("HTTP Response code: " + String(httpResponseCode));
//     return;
//   }
//   String response = http.getString();
//   Serial.println("HTTP Response code: " + String(httpResponseCode));
//   Serial.println("Server response: " + response);
// }
