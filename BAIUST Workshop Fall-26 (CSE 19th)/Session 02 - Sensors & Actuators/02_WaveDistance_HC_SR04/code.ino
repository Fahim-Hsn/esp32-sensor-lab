/*
 * Project: WaveDistance - Ultrasonic Range Finder & Reverse Parking Radar (Session 02)
 * Target: CSE 19th Batch, BAIUST
 * Description: Interfacing HC-SR04 ultrasonic sensor with ESP32 to measure distance in cm.
 *              Includes proportional buzzer feedback: closer objects cause faster beeping.
 *              Updated to use tone() for passive 3-leg buzzers.
 */

// Pin definitions
const int TRIG_PIN   = 5;   // Sends 10µs ultrasonic burst
const int ECHO_PIN   = 18;  // Measures pulse width of returned echo
const int BUZZER_PIN = 26;  // 3-leg passive buzzer module

// Speed of sound constant in air (~343 m/s = 0.0343 cm/µs)
const float SOUND_SPEED = 0.0343;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("==========================================");
  Serial.println("  BAIUST CSE 19th - ESP32 Workshop Fall-26");
  Serial.println("  Session 02: WaveDistance Ultrasonic Radar");
  Serial.println("==========================================");

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);
  noTone(BUZZER_PIN); // Ensure buzzer is silent on startup
}

void loop() {
  // Step 1: Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Step 2: Send a clean 10-microsecond HIGH pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Step 3: Measure the duration of the incoming pulse on ECHO_PIN (in microseconds)
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout (~5 meters max)

  // Step 4: Calculate distance in centimeters
  // Distance = (Duration * Sound Speed) / 2
  float distanceCm = (duration * SOUND_SPEED) / 2.0;

  // Step 5: Process and print readings
  if (duration == 0 || distanceCm > 400.0) {
    Serial.println("[RADAR] Out of range or no echo received.");
    noTone(BUZZER_PIN);
    delay(200);
  } else {
    Serial.print("[RADAR] Target Distance: ");
    Serial.print(distanceCm, 1);
    Serial.println(" cm");

    // Smart Parking Radar Logic:
    // If distance < 10 cm: Critical proximity (continuous warning sound)
    // If distance between 10 cm and 30 cm: Proportional pulsing beep
    // If distance > 30 cm: Safe zone (silent)
    if (distanceCm < 10.0) {
      tone(BUZZER_PIN, 1500); // 1500 Hz high pitch tone
      delay(50);
      noTone(BUZZER_PIN);     // Stop the tone
      delay(50);
    } else if (distanceCm <= 30.0) {
      int beepDelay = map((int)distanceCm, 10, 30, 80, 400);
      tone(BUZZER_PIN, 1000); // 1000 Hz standard tone
      delay(40);
      noTone(BUZZER_PIN);
      delay(beepDelay);
    } else {
      noTone(BUZZER_PIN);     // Silence the buzzer
      delay(200);
    }
  }
}
