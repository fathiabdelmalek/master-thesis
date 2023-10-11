#include "STAConfig.h"
#include "SensorsConfig.h"

void setup() {
  Serial.begin(115200);
  InitESPNow();
}

void loop() {
  float *data = getData();
  sendSensorData(data);
  delay(1000);
}
