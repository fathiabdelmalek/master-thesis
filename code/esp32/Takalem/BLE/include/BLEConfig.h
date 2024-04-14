#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "258d13c1-691f-4a68-a79a-15f7f18bdf1b"
#define CHARACTERISTIC_UUID "691ebc08-3744-4d48-b6fc-e8d229b0113e"

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;

void initBLE() {
  BLEDevice::init("TAKALEM-G1-g1");
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setValue("Hello World says Fathi");
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}
