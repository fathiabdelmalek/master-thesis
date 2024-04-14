// #include <Arduino.h>
// #include "SensorsConfig.h"
// #include "BLEConfig.h"

// #define LED 2

// void setup() {
//   pinMode(LED, OUTPUT);
//   initBLE();
// }

// void loop() {
//   digitalWrite(LED, HIGH);
//   delay(1800);
//   digitalWrite(LED, LOW);
//   delay(200);
//   digitalWrite(LED, HIGH);
//   delay(200);
//   digitalWrite(LED, LOW);
//   delay(200);
// }

// #include <Arduino.h>
// #include "SensorsConfig.h"
// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEScan.h>
// #include <BLEAdvertisedDevice.h>

// int scanTime = 5; //In seconds
// BLEScan* pBLEScan;

// class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
//     void onResult(BLEAdvertisedDevice advertisedDevice) {
//       Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
//     }
// };

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Scanning...");

//   BLEDevice::init("TAKALEM-G1-g2");
//   pBLEScan = BLEDevice::getScan(); //create new scan
//   pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
//   pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
//   pBLEScan->setInterval(100);
//   pBLEScan->setWindow(99);  // less or equal setInterval value
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
//   Serial.print("Devices found: ");
//   Serial.println(foundDevices.getCount());
//   Serial.println("Scan done!");
//   pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
//   delay(2000);
// }


// #include <Arduino.h>
// #include <BLEDevice.h>
// #include "SensorsConfig.h"

// #define SERVICE_UUID "258d13c1-691f-4a68-a79a-15f7f18bdf1b"
// #define CHARACTERISTIC_UUID "691ebc08-3744-4d48-b6fc-e8d229b0113e"

// BLEClient *pClient;

// void characteristicNotifyCallback(BLECharacteristic *pCharacteristic) {
//   Serial.print("Received data: ");
//   // Access data received from server ESP32 and process it (replace with your format)
//   uint8_t *data = pCharacteristic->getData();
//   for (int i = 0; i < pCharacteristic->getDataLength(); i++) {
//     Serial.print(data[i], HEX);
//     Serial.print(" ");
//   }
//   Serial.println();
// }

// void setup() {
//   Serial.begin(115200);

//   // Connect to BLE server (your existing code for scanning and connection)
  
//   // Discover services and characteristics
//   BLEService *pService = pClient->getService(BLEUUID(SERVICE_UUID));
//   if (pService) {
//     BLECharacteristic *pCharacteristic = pService->getCharacteristic(BLEUUID(CHARACTERISTIC_UUID));
//     if (pCharacteristic) {
//       pClient.setNotifyCallback(characteristicNotifyCallback);
//       pCharacteristic->subscribe();
//       Serial.println("Subscribed to characteristic notifications");
//     }
//   }
// }

// void loop() {
//   // ... (your code here) ...
// }


#include <Arduino.h>
#include <BluetoothSerial.h>
#include "SensorsConfig.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
  touchRead(11);
}
