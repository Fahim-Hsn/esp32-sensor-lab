void setup() {
  // ESP32 boards have an internal LED on GPIO 2
  pinMode(2, OUTPUT); 
}

void loop() {
  digitalWrite(2, HIGH); // LED ON
  delay(500);            // Wait 0.5 seconds
  digitalWrite(2, LOW);  // LED OFF
  delay(500);            // Wait 0.5 seconds
}
