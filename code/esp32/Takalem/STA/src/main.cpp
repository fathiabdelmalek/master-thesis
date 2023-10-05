#include "ServerConfig.h"

#define led 2

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  connectToWiFi();
}

void loop() {
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(500);
  // sendJson("Data");
}
