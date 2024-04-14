// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEClient.h>
// #include <BLEAdvertisedDevice.h>

// #define SERVICE_UUID "691ebc08-3744-4d48-b6fc-e8d229b0113e"
// #define CHARACTERISTIC_UUID "5763e532-cf00-40ff-9210-26a4eaa21d86"

// BLEClient *pClient;
// BLERemoteService *pRemoteService;
// BLERemoteCharacteristic *pCharacteristic;

// void initBLE() {
//   BLEDevice::init("TAKALEM-G1-g2");
//   pClient = BLEDevice::createClient();
//   // pClient->connect("TAKALEM-G1-g1");
//   pClient->connect(new BLEAdvertisedDevice)
//   pRemoteService = pClient->getService(SERVICE_UUID);
//   pCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
//   std::string value = pCharacteristic->readValue();
//   Serial.println("Value read from characteristic: " + String(value.c_str()));
// }
