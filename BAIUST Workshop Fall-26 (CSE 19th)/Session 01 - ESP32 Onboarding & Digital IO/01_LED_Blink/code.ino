/*
 * Project: ESP32 Basic LED Blink (Session 01)
 * Target: CSE 19th Batch, BAIUST
 * Description: The "Hello World" of physical computing. Controls an external LED
 *              connected to GPIO 2 with serial telemetry.
 */

// Define the GPIO pin connected to the LED anode
const int LED_PIN = 2; // Onboard blue LED is usually on GPIO 2, also wired to external LED

void setup() {
  // Initialize Serial Monitor at 115200 baud rate for debugging
  Serial.begin(115200);
  delay(1000); // Small delay to let serial connection stabilize

  Serial.println("==========================================");
  Serial.println("  BAIUST CSE 19th - ESP32 Workshop Fall-26");
  Serial.println("  Session 01: LED Blink Started");
  Serial.println("==========================================");

  // Configure the LED pin as an OUTPUT pin
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Turn LED ON (3.3V applied to pin)
  digitalWrite(LED_PIN, HIGH);
  Serial.println("[STATUS] LED is ON  (HIGH)");
  delay(1000); // Wait for 1000 milliseconds (1 second)

  // Turn LED OFF (0V applied to pin)
  digitalWrite(LED_PIN, LOW);
  Serial.println("[STATUS] LED is OFF (LOW)");
  delay(1000); // Wait for 1000 milliseconds (1 second)
}
