#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x94, 0x3C, 0xC6, 0x43, 0x66, 0x08};

float data[11];

struct struct_sensors_message {
  float data[11];
} SensorsReadings;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void InitESPNow() {
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
}

void sendSensorData(float data[11]) {
  memcpy(SensorsReadings.data, data, sizeof(SensorsReadings.data));

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &SensorsReadings, sizeof(SensorsReadings));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}
