// Define the ESP32 pin connections
const int irPin = 13;       // IR Sensor OUT pin connected to GPIO 13
const int redLed = 14;      // Red LED connected to GPIO 14
const int greenLed = 27;    // Green LED connected to GPIO 27
const int buzzerPin = 26;   // 3-Leg Buzzer Signal (S) pin connected to GPIO 26

void setup() {
  // Start the Serial Monitor to see the output on the computer
  Serial.begin(115200);
  
  // Configure the pins as INPUT or OUTPUT
  pinMode(irPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT); // Configure the buzzer signal pin as OUTPUT

  // Initial State: Turn everything off
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  noTone(buzzerPin);          // Ensure the 3-leg buzzer is quiet at startup
  
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
    
    // Generate a beeping sound using tone() 
    // Works perfectly for both Active and Passive 3-leg modules
    tone(buzzerPin, 1000);        // Send 1000Hz sound frequency to the buzzer
    delay(100);                   // Keep the sound ON for 0.1 seconds
    noTone(buzzerPin);            // Turn the sound OFF
    delay(100);                   // Keep it silent for 0.1 seconds to create the beep effect
    
  } else {
    // NO OBSTACLE
    Serial.println("Path is Clear.");
    
    digitalWrite(redLed, LOW);    // Turn OFF Red LED
    noTone(buzzerPin);            // Ensure the buzzer remains completely OFF
    digitalWrite(greenLed, HIGH); // Turn ON Green LED
    
    delay(200); // Small delay to stabilize readings
  }
}
