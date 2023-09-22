// #include <Arduino.h>
// #include <WiFi.h>
// #include <WiFiAP.h>
// #include <WiFiClient.h>

// #define led 2

// const char *ssid = "F-ESP32";
// const char *password = "fathi2211";

// WiFiServer server(80);

// void setup() {
//   pinMode(led, OUTPUT);
//   Serial.begin(115200);
  
//   WiFi.softAP(ssid, password);
//   IPAddress ip_addr = WiFi.softAPIP();
//   Serial.print("AP IP Address: ");
//   Serial.println(ip_addr);
//   server.begin();
// }

// void loop() {
//   IPAddress ip_addr = WiFi.softAPIP();
//   Serial.print("AP IP Address: ");
//   Serial.println(ip_addr);
//   WiFiClient client = server.available();   // listen for incoming clients

//   if (client) {                             // if you get a client,
//     Serial.println("New Client.");           // print a message out the serial port
//     String currentLine = "";                // make a String to hold incoming data from the client
//     while (client.connected()) {            // loop while the client's connected
//       if (client.available()) {             // if there's bytes to read from the client,
//         char c = client.read();             // read a byte, then
//         Serial.write(c);                    // print it out the serial monitor
//         if (c == '\n') {                    // if the byte is a newline character

//           // if the current line is blank, you got two newline characters in a row.
//           // that's the end of the client HTTP request, so send a response:
//           if (currentLine.length() == 0) {
//             // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
//             // and a content-type so the client knows what's coming, then a blank line:
//             client.println("HTTP/1.1 200 OK");
//             client.println("Content-type:text/html");
//             client.println();

//             // the content of the HTTP response follows the header:
//             client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
//             client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

//             // The HTTP response ends with another blank line:
//             client.println();
//             // break out of the while loop:
//             break;
//           } else {    // if you got a newline, then clear currentLine:
//             currentLine = "";
//           }
//         } else if (c != '\r') {  // if you got anything else but a carriage return character,
//           currentLine += c;      // add it to the end of the currentLine
//         }

//         // Check to see if the client request was "GET /H" or "GET /L":
//         if (currentLine.endsWith("GET /H")) {
//           digitalWrite(led, HIGH);
//         }
//         if (currentLine.endsWith("GET /L")) {
//           digitalWrite(led, LOW);
//         }
//       }
//     }
//     // close the connection:
//     client.stop();
//     Serial.println("Client Disconnected.");
//   }
// }



#include <WiFi.h>

const char* ssid_sta = "idoom"; // SSID of your existing Wi-Fi network
const char* password_sta = "0672631822m"; // Password for your Wi-Fi network
const char* ssid_ap = "ESP32_AP"; // SSID for the ESP32 Access Point
const char* password_ap = "fathi2001"; // Password for the ESP32 Access Point

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);

    Serial.println("\n[*] Creating ESP32 AP");
    WiFi.softAP(ssid_ap, password_ap);
    Serial.print("[+] AP Created with IP Gateway ");
    Serial.println(WiFi.softAPIP());

    WiFi.begin(ssid_sta, password_sta);
    Serial.println("\n[*] Connecting to WiFi Network");

    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }

    Serial.print("\n[+] Connected to the WiFi network with local IP : ");
    Serial.println(WiFi.localIP());
}

void loop() {
  // Your main code here
}
