void setup() {
  pinMode(2, OUTPUT);              // GPIO 2 controls LED
  Serial.begin(115200);            // Start Serial Monitor at 115200 baud
  Serial.println("ESP32 LED Blink Started!");
}

void loop() {
  digitalWrite(2, HIGH);           // Turn ON LED
  Serial.println("LED is ON");     // Print status to Serial Monitor
  delay(1000);                     // Wait 1 second

  digitalWrite(2, LOW);            // Turn OFF LED
  Serial.println("LED is OFF");    // Print status to Serial Monitor
  delay(1000);                     // Wait 1 second
}
