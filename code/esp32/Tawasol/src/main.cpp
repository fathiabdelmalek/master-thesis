#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

#define SSID "idoom"
// #define SSID "D-Link_DAP-1360"
#define PASSWORD "0672631822f"
#define WIFI_TIMEOUT 20000
#define SERVER_URL "http://192.168.1.21:5000/"
// #define SERVER_URL "http://172.16.7.138:5000/"

#define MAX_ 1200
#define MIN_ 4095

#define FLEX1_PIN 32
#define FLEX2_PIN 33
#define FLEX3_PIN 34
#define FLEX4_PIN 35
#define FLEX5_PIN 36

Adafruit_MPU6050 mpu;

void connect_to_mpu();
void connect_to_wifi();
char*** get_data();
String create_json_payload(char***);
char* extract_prediction(const String&);

void setup() {
  Serial.begin(115200);
  connect_to_mpu();
  connect_to_wifi();
}

void loop() {
  char*** data;
  Serial.println("Begin reading data");
  data = get_data();
  Serial.println("Done reading data");
  Serial.println("Begin printing data");
  for (int i = 0; i < 150; i++) {
    for (int j = 0; j < 11; j++) {
      Serial.print(data[i][j]);
      Serial.print(", ");
    }
    Serial.println();
  }
  Serial.println("Done printing data");
  String payload = create_json_payload(data);

  WiFiClient client;
  HTTPClient http;

  if (!http.begin(client, SERVER_URL)) {
    Serial.println("Unable to connect to server");
    return;
  }
  
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode <= 0) {
    Serial.println("Error sending POST request");
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    return;
  }
  String response = http.getString();
  Serial.println("HTTP Response code: " + String(httpResponseCode));
  Serial.println("Server response: " + response);

  char* prediction = extract_prediction(response);
  Serial.println(prediction);

  http.end();

  delay(1000);
}

void connect_to_mpu() {
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

  Serial.println("Flex Sensor and MPU6050 Initialized");
}

void connect_to_wifi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(SSID, PASSWORD);

  unsigned long start_time = millis();

  while ((WiFi.status() != WL_CONNECTED) && (millis() - start_time < WIFI_TIMEOUT)) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect to WiFi");
    Serial.println(WiFi.status());
    return;
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}

char*** get_data() {
  char*** data = new char**[150];
  for (int i = 0; i < 150; i++) {
    data[i] = new char*[11];
    for (int j = 0; j < 11; j++) {
      data[i][j] = new char[8];
    }
  }

  for (int i = 0; i < 150; i++) {
    sensors_event_t a, g, temp;
    if (!mpu.getEvent(&a, &g, &temp)) {
      Serial.println("Error, can't read MPU6050 data");
    }
    // data[i][0] = dtostrf(map(analogRead(FLEX1_PIN), MAX_, MIN_, 0, 90), 2, 0, data[i][0]);
    // data[i][1] = dtostrf(map(analogRead(FLEX2_PIN), MAX_, MIN_, 0, 90), 2, 0, data[i][1]);
    // data[i][2] = dtostrf(map(analogRead(FLEX3_PIN), MAX_, MIN_, 0, 90), 2, 0, data[i][2]);
    // data[i][3] = dtostrf(map(analogRead(FLEX4_PIN), MAX_, MIN_, 0, 90), 2, 0, data[i][3]);
    // data[i][4] = dtostrf(map(analogRead(FLEX5_PIN), MAX_, MIN_, 0, 90), 2, 0, data[i][4]);
    data[i][0] = "90";
    data[i][1] = "90";
    data[i][2] = "90";
    data[i][3] = "90";
    data[i][4] = "90";
    data[i][5] = dtostrf(g.gyro.x, 4, 2, data[i][5]);
    data[i][6] = dtostrf(g.gyro.y, 4, 2, data[i][6]);
    data[i][7] = dtostrf(g.gyro.z, 4, 2, data[i][7]);
    data[i][8] = dtostrf(a.acceleration.x, 4, 2, data[i][8]);
    data[i][9] = dtostrf(a.acceleration.y, 4, 2, data[i][9]);
    data[i][10] = dtostrf(a.acceleration.z, 4, 2, data[i][10]);
    delay(10);
  }
  return data;
}

String create_json_payload(char*** data) {
  String payload = "{\"data\": [";
  for (int i = 0; i < 150; i++) {
    payload += "{";
    payload += "\"row" + String(i + 1) + "\": [{";
    payload += "\"flex_1\":" + String(data[i][0]) + ",";
    payload += "\"flex_2\":" + String(data[i][1]) + ",";
    payload += "\"flex_3\":" + String(data[i][2]) + ",";
    payload += "\"flex_4\":" + String(data[i][3]) + ",";
    payload += "\"flex_5\":" + String(data[i][4]) + ",";
    payload += "\"gyro_x\":" + String(data[i][5]) + ",";
    payload += "\"gyro_y\":" + String(data[i][6]) + ",";
    payload += "\"gyro_z\":" + String(data[i][7]) + ",";
    payload += "\"accel_x\":" + String(data[i][8]) + ",";
    payload += "\"accel_y\":" + String(data[i][9]) + ",";
    payload += "\"accel_z\":" + String(data[i][10]);
    payload += "}]}";
    if (i != 149) {
      payload += ",";
    }
  }
  payload += "]}";

  return payload;
}

char* extract_prediction(const String& response) {
  // Parse JSON response using ArduinoJson
  StaticJsonDocument<200> responseDoc;
  DeserializationError error = deserializeJson(responseDoc, response);

  if (error) {
    Serial.print("JSON parsing failed! Error code: ");
    Serial.println(error.c_str());
    return nullptr;
  }

  // Extract the prediction value from JSON response
  const char* prediction = responseDoc["prediction"];

  // Create a dynamic char array and copy the prediction value
  size_t predictionLength = strlen(prediction) + 1;
  char* predictionVariable = new char[predictionLength];
  strncpy(predictionVariable, prediction, predictionLength);

  return predictionVariable;
}
