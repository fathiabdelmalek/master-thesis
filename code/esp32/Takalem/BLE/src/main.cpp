#include <Arduino.h>
#include "BLEConfig.h"
#include "SensorsConfig.h"

#define LED 2

void setup() {
  pinMode(LED, OUTPUT);
  initBLE();
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
}
