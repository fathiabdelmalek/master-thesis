#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x70, 0xB8, 0xF6, 0x5B, 0xFE, 0x44};

float incomingData[11];

typedef struct struct_sensors_message {
  float data[11];
} struct_sensors_message;

struct_sensors_message incomingReadings;

esp_now_peer_info_t peerInfo;

void OnDataRecv(const uint8_t *mac, const uint8_t *incoming_data, int len) {
  if (len == sizeof(incomingReadings)) {
    memcpy(&incomingReadings, incoming_data, sizeof(incomingReadings));
  } else {
    Serial.println("Received data is not the expected size.");
    Serial.print("Supposed size: ");
    Serial.println(sizeof(incomingReadings));
    Serial.print("Bytes received: ");
    Serial.println(len);
  }
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

float* getReceivedData() {
  float *data = new float[11];
  for (int i = 0; i < 11; i++) {
    data[i] = incomingReadings.data[i];
  }
  return data;
}

void updateDisplay(){
  Serial.println("Receiving data: ");
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
