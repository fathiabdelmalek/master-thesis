#include <Wire.h>
#include <Adafruit_MPU6050.h>


#define MAX_ 1200
#define MIN_ 4095

#define SDA 21
#define SCL 22

#define FLEX1_PIN 36
#define FLEX2_PIN 34
#define FLEX3_PIN 35
#define FLEX4_PIN 32
#define FLEX5_PIN 33

Adafruit_MPU6050 mpu;


bool connectToMPU() {
  Wire.begin(SDA, SCL);
  Serial.println("Connect to MPU6050");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(200);
      Serial.print(".");
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  return true;
}

float* getData() {
  float* data = new float[11];
  sensors_event_t a, g, temp;
  if (!mpu.getEvent(&a, &g, &temp)) {
    Serial.println("Error, can't read mpu6050 data");
  }
  data[0] = map(analogRead(FLEX1_PIN), MIN_, MAX_, 0, 90);
  data[1] = map(analogRead(FLEX2_PIN), MIN_, MAX_, 0, 90);
  data[2] = map(analogRead(FLEX3_PIN), MIN_, MAX_, 0, 90);
  data[3] = map(analogRead(FLEX4_PIN), MIN_, MAX_, 0, 90);
  data[4] = map(analogRead(FLEX5_PIN), MIN_, MAX_, 0, 90);
  data[5] = g.gyro.x;
  data[6] = g.gyro.y;
  data[7] = g.gyro.z;
  data[8] = a.acceleration.x;
  data[9] = a.acceleration.y;
  data[10] = a.acceleration.z;
  return data;
}
