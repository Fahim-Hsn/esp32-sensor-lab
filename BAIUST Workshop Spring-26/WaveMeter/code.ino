// Define Ultrasonic Sensor Pins
const int trigPin = 5;    // Trigger pin connected to GPIO 5
const int echoPin = 18;   // Echo pin connected to GPIO 18

// Variables for calculation
long duration;
float distanceCm;

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  
  // Configure Ultrasonic Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor by sending a 10 microsecond HIGH pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in cm
  // Speed of sound wave is 0.0343 cm/microsecond. Divide by 2 (go and back)
  distanceCm = (duration * 0.0343) / 2;
  
  // Print distance to Serial Monitor
  if (distanceCm > 400 || distanceCm < 2) {
    Serial.println("Distance: Out of Range");
  } else {
    Serial.print("Distance: ");
    Serial.print(distanceCm, 1); // Print distance with 1 decimal place
    Serial.println(" cm");
  }
  
  // Wait for 200 milliseconds before the next reading
  delay(200);
}
