/*
 * Project: SafeZone - Smart Proximity & Intruder Alert System (Session 02)
 * Target: CSE 19th Batch, BAIUST
 * Description: Interfacing an IR obstacle sensor with a 3-leg buzzer module and dual LEDs.
 *              Green LED stays ON when safe. When obstacle is detected, Red LED lights up
 *              and buzzer sounds continuous alert.
 */

// Pin Assignments
const int IR_SENSOR_PIN = 13; // IR Module Digital Out (Active LOW)
const int RED_LED_PIN   = 14; // Alert Indicator
const int GREEN_LED_PIN = 27; // Safe Status Indicator
const int BUZZER_PIN    = 26; // 3-leg Buzzer Signal (I/O) pin

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("==========================================");
  Serial.println("  BAIUST CSE 19th - ESP32 Workshop Fall-26");
  Serial.println("  Session 02: Smart Proximity Alert System");
  Serial.println("==========================================");

  // Configure sensor pin as INPUT
  pinMode(IR_SENSOR_PIN, INPUT);

  // Configure actuator pins as OUTPUT
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initial state: Safe
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // Read digital state from IR sensor
  int obstacleDetected = digitalRead(IR_SENSOR_PIN);

  // NOTE: Standard IR Obstacle modules output LOW (0) when an object is detected!
  if (obstacleDetected == LOW) {
    // ALARM STATE: Obstacle detected
    Serial.println("[ALERT] Obstacle Detected! Siren Activated!");
    
    digitalWrite(GREEN_LED_PIN, LOW);  // Turn off Green safe LED
    digitalWrite(RED_LED_PIN, HIGH);   // Turn on Red alert LED
    digitalWrite(BUZZER_PIN, HIGH);    // Activate buzzer alarm
  } else {
    // NORMAL / SAFE STATE: No obstacle
    Serial.println("[SAFE] Path Clear.");
    
    digitalWrite(GREEN_LED_PIN, HIGH); // Green safe LED ON
    digitalWrite(RED_LED_PIN, LOW);    // Red alert LED OFF
    digitalWrite(BUZZER_PIN, LOW);     // Buzzer OFF
  }

  delay(100); // 100ms sample interval for smooth responsiveness
}
