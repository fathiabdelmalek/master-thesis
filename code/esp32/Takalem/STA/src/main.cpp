#include "STAConfig.h"
#include "SensorsConfig.h"

void setup() {
  Serial.begin(115200);
  InitESPNow();
}

void loop() {
  Serial.println("Begin reading data");
  float** data = getData();
  Serial.println("Done reading data");
  sendSensorData(data);


  // sendData();
  delay(1000);
}
