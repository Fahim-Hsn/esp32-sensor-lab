#include <WiFi.h>
#include <HTTPClient.h>

// Wi-Fi 
const char* ssid = "Your Wifi Name";
const char* password = "Your Wifi Password";
const char* serverUrl = "http://Your Ip:3000/api/sensor-data";
const char* checkLedUrl = "http://Your Ip:3000/api/check-led-d2";
// if don't your ip - open command prompt write - "ipconfig"

// pin
const int irPin = 13;
const int redLed = 14;
const int greenLed = 27;
const int buzzerPin = 26;
const int d2Led = 2; 

int detectionCount = 0;
bool lastState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(irPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(d2Led, OUTPUT); 

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // ১. Server to LED and Reset Check
    http.begin(checkLedUrl);
    int httpCode = http.GET();
    if (httpCode == 200) {
      String payload = http.getString(); 

      // LED control (D2)
      if (payload.indexOf("ON") >= 0) digitalWrite(d2Led, HIGH);
      else digitalWrite(d2Led, LOW);

      // count reset logic
      if (payload.indexOf("|1") >= 0) {
        detectionCount = 0; 
        Serial.println("Counter Reset by Web!");
      }
    }
    http.end();

    // sensor read and count logic
    int sensorState = digitalRead(irPin);
    
    // object detection(Edge Detection)
    if (sensorState == LOW && lastState == HIGH) {
      detectionCount++;

      // hardware feedback
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(100); 
      digitalWrite(buzzerPin, LOW);

      // server data sent
      sendUpdate(detectionCount);
      Serial.printf("Object Detected! Count: %d\n", detectionCount);
    }
    
    // if sensor is clear
    if (sensorState == HIGH) {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
    }

    lastState = sensorState;
  }
  delay(1000); 
}

void sendUpdate(int count) {
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
  http.POST("{\"count\":" + String(count) + "}");
  http.end();
}
