#include "ServerConfig.h"

#define led 2

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  createServer();
}

void loop() {
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(100);
}
