// #include <esp_now.h>
// #include <WiFi.h>

// uint8_t broadcastAddress[] = {0x94, 0x3C, 0xC6, 0x43, 0x66, 0x08};

// int8_t temperature = 12;

// typedef struct struct_message {
//     int8_t temp;
// } struct_message;

// struct_message BME280Readings;

// esp_now_peer_info_t peerInfo;
// String success;

// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   Serial.print("\r\nLast Packet Send Status:\t");
//   Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
//   if (status ==0){
//     success = "Delivery Success :)";
//   }
//   else{
//     success = "Delivery Fail :(";
//   }
// }

// void InitESPNow() {
//   WiFi.mode(WIFI_STA);

//   if (esp_now_init() != ESP_OK) {
//     Serial.println("Error initializing ESP-NOW");
//     return;
//   }
//   memcpy(peerInfo.peer_addr, broadcastAddress, 6);
//   peerInfo.channel = 0;  
//   peerInfo.encrypt = false;
//   if (esp_now_add_peer(&peerInfo) != ESP_OK){
//     Serial.println("Failed to add peer");
//     return;
//   }
//   esp_now_register_send_cb(OnDataSent);
// }

// void sendData() {
//   temperature++;

//   BME280Readings.temp = temperature;

//   esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &BME280Readings, sizeof(BME280Readings));
//   if (result == ESP_OK) {
//     Serial.println("Sent with success");
//   }
//   else {
//     Serial.println("Error sending the data");
//   }
// }

#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x94, 0x3C, 0xC6, 0x43, 0x66, 0x08};

float** data;

typedef struct struct_sensors_message {
    float** data;
} struct_sensors_message;

struct_sensors_message SensorsReadings;

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

void sendSensorData(float** data) {

  SensorsReadings.data = data;

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &SensorsReadings, sizeof(SensorsReadings));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  if (data != nullptr) {
    // Release the memory
    for (int i = 0; i < 150; i++) {
      delete[] data[i];
    }
    delete[] data;
    data = nullptr;
  }
}
