#include <Wire.h>
#include <Adafruit_MPU6050.h>


#define MAX_ 1200
#define MIN_ 4095

#define FLEX1_PIN 32
#define FLEX2_PIN 33
#define FLEX3_PIN 34
#define FLEX4_PIN 35
#define FLEX5_PIN 36

Adafruit_MPU6050 mpu;


bool connectToMPU() {
  Wire.begin(21, 22);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  return true;
}

float** getData() {
  float** data = new float*[150];
  for (int i = 0; i < 150; i++) {
    data[i] = new float[11];
    sensors_event_t a, g, temp;
    if (!mpu.getEvent(&a, &g, &temp)) {
      Serial.println("Error, can't read mpu6050 data");
    }
    // data[i][0] = map(analogRead(FLEX1_PIN), MAX_, MIN_, 0, 90);
    // data[i][1] = map(analogRead(FLEX2_PIN), MAX_, MIN_, 0, 90);
    // data[i][2] = map(analogRead(FLEX3_PIN), MAX_, MIN_, 0, 90);
    // data[i][3] = map(analogRead(FLEX4_PIN), MAX_, MIN_, 0, 90);
    // data[i][4] = map(analogRead(FLEX5_PIN), MAX_, MIN_, 0, 90);
    data[i][0] = 0;
    data[i][1] = 0;
    data[i][2] = 0;
    data[i][3] = 0;
    data[i][4] = 0;
    data[i][5] = g.gyro.x;
    data[i][6] = g.gyro.y;
    data[i][7] = g.gyro.z;
    data[i][8] = a.acceleration.x;
    data[i][9] = a.acceleration.y;
    data[i][10] = a.acceleration.z;
    delay(10);
  }
  return data;
}
