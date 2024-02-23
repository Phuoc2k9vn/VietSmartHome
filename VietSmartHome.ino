#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "VietSmartHome";
const char* password = "12345678";

ESP8266WebServer server(80);

// Khai báo các chân GPIO mà bạn muốn điều khiển
const int ledPin1 = D1;  // Chân GPIO cho bóng LED 1
const int ledPin2 = D2;  // Chân GPIO cho bóng LED 2

int ledState1 = LOW;  // Trạng thái bóng LED 1 (BẬT/ TẮT)
int ledState2 = LOW;  // Trạng thái bóng LED 2 (BẬT/ TẮT)

void handleRoot() {
  String html = "<html><head><style>body{background-color:#6495ED;}</style></head><body>";
  html += "<h1>Smart Home Control</h1>";
  html += "<h2>LED Control:</h2>";
  html += "<form method='POST' action='/ledon1'><input type='submit' value='LED 1 ON'></form>";
  html += "<form method='POST' action='/ledoff1'><input type='submit' value='LED 1 OFF'></form>";
  html += "<form method='POST' action='/ledon2'><input type='submit' value='LED 2 ON'></form>";
  html += "<form method='POST' action='/ledoff2'><input type='submit' value='LED 2 OFF'></form>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleLEDOn1() {
  ledState1 = HIGH;  // Bật bóng LED 1
  digitalWrite(ledPin1, ledState1);
  server.send(200, "text/plain", "LED 1 turned ON");
}

void handleLEDOff1() {
  ledState1 = LOW;  // Tắt bóng LED 1
  digitalWrite(ledPin1, ledState1);
  server.send(200, "text/plain", "LED 1 turned OFF");
}

void handleLEDOn2() {
  ledState2 = HIGH;  // Bật bóng LED 2
  digitalWrite(ledPin2, ledState2);
  server.send(200, "text/plain", "LED 2 turned ON");
}

void handleLEDOff2() {
  ledState2 = LOW;  // Tắt bóng LED 2
  digitalWrite(ledPin2, ledState2);
  server.send(200, "text/plain", "LED 2 turned OFF");
}

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/ledon1", handleLEDOn1);
  server.on("/ledoff1", handleLEDOff1);
  server.on("/ledon2", handleLEDOn2);
  server.on("/ledoff2", handleLEDOff2);

  server.begin();

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  Serial.println("Access Point started");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  server.handleClient();
}
