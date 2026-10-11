/*
 * Project: Traffic Light Controller & PWM Fading (Session 01)
 * Target: CSE 19th Batch, BAIUST
 * Description: Simulates a real-world 3-way traffic light intersection (Red, Yellow, Green),
 *              and demonstrates analog-like brightness fading via PWM (Pulse Width Modulation).
 */

// Pin definitions
const int RED_LED_PIN    = 25;
const int YELLOW_LED_PIN = 26;
const int GREEN_LED_PIN  = 27;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("==========================================");
  Serial.println("  BAIUST CSE 19th - ESP32 Workshop Fall-26");
  Serial.println("  Session 01: Traffic Light & PWM System");
  Serial.println("==========================================");

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // Turn all off initially
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
}

void loop() {
  // Phase 1: STOP (Red LED ON)
  Serial.println("[TRAFFIC STATE] RED - Stop!");
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  delay(3000); // 3 seconds red

  // Phase 2: GET READY (Yellow LED ON)
  Serial.println("[TRAFFIC STATE] YELLOW - Prepare to go...");
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  delay(1500); // 1.5 seconds yellow

  // Phase 3: GO (Green LED ON)
  Serial.println("[TRAFFIC STATE] GREEN - Go!");
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(3000); // 3 seconds green

  // Phase 4: CAUTION / SLOW DOWN (Yellow LED Breathing Fade Effect)
  Serial.println("[TRAFFIC STATE] YELLOW - Caution (PWM Breathing effect)");
  digitalWrite(GREEN_LED_PIN, LOW);
  
  // Demonstrating PWM Fading (analogWrite supports ESP32 0-255 duty cycle)
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    analogWrite(YELLOW_LED_PIN, brightness);
    delay(15);
  }
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    analogWrite(YELLOW_LED_PIN, brightness);
    delay(15);
  }
}
