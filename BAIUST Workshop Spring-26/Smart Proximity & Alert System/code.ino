// Define the ESP32 pin connections
const int irPin = 13;       // IR Sensor OUT pin connected to GPIO 13
const int redLed = 14;      // Red LED connected to GPIO 14
const int greenLed = 27;    // Green LED connected to GPIO 27
const int buzzerPin = 26;   // Buzzer connected to GPIO 26

void setup() {
  // Start the Serial Monitor to see the output on the computer
  Serial.begin(115200);
  
  // Configure the pins as INPUT or OUTPUT
  pinMode(irPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initial State: Turn everything off
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(buzzerPin, LOW);
  
  Serial.println("SafeZone System Started!");
}

void loop() {
  // Read the state from the IR Sensor
  // Most IR sensors output LOW (0) when an obstacle is detected
  int sensorState = digitalRead(irPin);

  if (sensorState == LOW) {
    // OBSTACLE DETECTED
    Serial.println("ALERT! Obstacle Detected!");
    
    digitalWrite(greenLed, LOW);  // Turn OFF Green LED
    digitalWrite(redLed, HIGH);   // Turn ON Red LED
    
    // Create a beeping sound
    digitalWrite(buzzerPin, HIGH);
    delay(100);                   // Beep for 0.1 seconds
    digitalWrite(buzzerPin, LOW);
    delay(100);                   // Silence for 0.1 seconds
    
  } else {
    // NO OBSTACLE (Rasta Faka)
    Serial.println("Path is Clear.");
    
    digitalWrite(redLed, LOW);    // Turn OFF Red LED
    digitalWrite(buzzerPin, LOW); // Turn OFF Buzzer
    digitalWrite(greenLed, HIGH); // Turn ON Green LED
    
    delay(200); // Small delay to stabilize readings
  }
}
