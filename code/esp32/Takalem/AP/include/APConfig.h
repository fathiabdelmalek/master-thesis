// #include <esp_now.h>
// #include <WiFi.h>

// uint8_t broadcastAddress[] = {0x70, 0xB8, 0xF6, 0x5B, 0xFE, 0x44};

// int8_t incomingTemp;

// typedef struct struct_message {
//     int8_t temp;
// } struct_message;

// struct_message incomingReadings;

// esp_now_peer_info_t peerInfo;

// void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
//   memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
//   Serial.print("Bytes received: ");
//   Serial.println(len);
//   incomingTemp = incomingReadings.temp;
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
//   esp_now_register_recv_cb(OnDataRecv);
// }

// void updateDisplay(){
//   Serial.print("Temperature: ");
//   Serial.print(incomingReadings.temp);
//   Serial.println(" ºC");
// }

// #include <esp_now.h>
// #include <WiFi.h>

// uint8_t broadcastAddress[] = {0x70, 0xB8, 0xF6, 0x5B, 0xFE, 0x44};

// float** incomingData = nullptr;

// typedef struct struct_sensors_message {
//   float** data;
// } struct_sensors_message;

// struct_sensors_message incomingReadings;

// esp_now_peer_info_t peerInfo;

// // void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
//   // memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
//   // Serial.print("Bytes received: ");
//   // Serial.println(len);
//   // // incomingData = incomingReadings.data;
//   // // memcpy(incomingData[0], incomingReadings.data[0], 11 * sizeof(float));
// // }

// void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
//   if (len >= sizeof(incomingReadings)) {
//     memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
//     size_t dataSize = 11 * sizeof(float);
//     incomingData = new uint8_t*[150];
//     incomingData[0] = new uint8_t[dataSize];
//     memcpy(incomingData[0], incomingReadings.data[0], dataSize);
//   } else {
//     Serial.println("Received data is too short for the expected structure.");
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
//   esp_now_register_recv_cb(OnDataRecv);
// }

#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x70, 0xB8, 0xF6, 0x5B, 0xFE, 0x44};

float incomingData[150];

typedef struct struct_sensors_message {
  float data[150];
} struct_sensors_message;

struct_sensors_message incomingReadings;

esp_now_peer_info_t peerInfo;

void OnDataRecv(const uint8_t *mac, const uint8_t *incoming_data, int len) {
  memcpy(&incomingReadings, incoming_data, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  memcpy((void*)incomingData, incomingReadings.data, sizeof(incomingData));
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
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void updateDisplay(){
  Serial.println("First Row: ");
  Serial.print("Flex 1: ");
  Serial.println(incomingReadings.data[0]);
  Serial.print("Flex 2: ");
  Serial.println(incomingReadings.data[1]);
  Serial.print("Flex 3: ");
  Serial.println(incomingReadings.data[2]);
  Serial.print("Flex 4: ");
  Serial.println(incomingReadings.data[3]);
  Serial.print("Flex 5: ");
  Serial.println(incomingReadings.data[4]);
  Serial.print("Gyro X: ");
  Serial.println(incomingReadings.data[5]);
  Serial.print("Gyro Y: ");
  Serial.println(incomingReadings.data[6]);
  Serial.print("Gyro Z: ");
  Serial.println(incomingReadings.data[7]);
  Serial.print("Acceleration X: ");
  Serial.println(incomingReadings.data[8]);
  Serial.print("Acceleration Y: ");
  Serial.println(incomingReadings.data[9]);
  Serial.print("Acceleration Z: ");
  Serial.println(incomingReadings.data[10]);
  Serial.println();
}

// void updateDisplay(){
//   Serial.println("First Row: ");
//   Serial.print("Flex 1: ");
//   Serial.println(incomingReadings.data[0][0]);
//   Serial.print("Flex 2: ");
//   Serial.println(incomingReadings.data[0][1]);
//   Serial.print("Flex 3: ");
//   Serial.println(incomingReadings.data[0][2]);
//   Serial.print("Flex 4: ");
//   Serial.println(incomingReadings.data[0][3]);
//   Serial.print("Flex 5: ");
//   Serial.println(incomingReadings.data[0][4]);
//   Serial.print("Gyro X: ");
//   Serial.println(incomingReadings.data[0][5]);
//   Serial.print("Gyro Y: ");
//   Serial.println(incomingReadings.data[0][6]);
//   Serial.print("Gyro Z: ");
//   Serial.println(incomingReadings.data[0][7]);
//   Serial.print("Acceleration X: ");
//   Serial.println(incomingReadings.data[0][8]);
//   Serial.print("Acceleration Y: ");
//   Serial.println(incomingReadings.data[0][9]);
//   Serial.print("Acceleration Z: ");
//   Serial.println(incomingReadings.data[0][10]);
//   Serial.println();
// }
