#include <U8g2lib.h>
#include <Wire.h>

// Initialize the 1.3-inch OLED (SH1106 via I2C)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// Define Ultrasonic Sensor Pins
const int trigPin = 5;    // Trigger pin connected to GPIO 5
const int echoPin = 18;   // Echo pin connected to GPIO 18

// Variables for calculation
long duration;
float distanceCm;

// Declaration of custom function
void updateDisplay(float distance);

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  
  // Configure Ultrasonic Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize the OLED Display
  u8g2.begin();
  
  // Show a welcome screen
  u8g2.clearBuffer();					
  u8g2.setFont(u8g2_font_ncenB08_tr);	// Choose a bold font
  u8g2.drawStr(10, 30, "Distance Tracker");
  u8g2.drawStr(30, 45, "Initializing...");
  u8g2.sendBuffer();
  delay(2000); // Show welcome screen for 2 seconds
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
  
  // Print distance to Serial Monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");
  
  // Update the OLED display with the calculated distance
  updateDisplay(distanceCm);
  
  // Wait for 200 milliseconds before the next reading
  delay(200);
}

// --- CUSTOM FUNCTION TO UPDATE THE OLED ---
void updateDisplay(float distance) {
  u8g2.clearBuffer(); // Clear internal screen memory
  
  // 1. Draw Title Dashboard
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.drawStr(0, 15, "OLED Radar Dashboard");
  u8g2.drawLine(0, 20, 128, 20);      

  // 2. Draw Measurement Label
  u8g2.setFont(u8g2_font_ncenB10_tr); 
  u8g2.drawStr(0, 42, "Distance:");

  // 3. Draw Dynamic Distance Value
  u8g2.setFont(u8g2_font_ncenB14_tr); // Larger font for the number
  u8g2.setCursor(10, 62);
  
  // Handle out-of-range readings
  if (distance > 400 || distance < 2) {
    u8g2.print("Out of Range");
  } else {
    u8g2.print(distance, 1); // Print distance with 1 decimal place
    u8g2.print(" cm");
  }

  u8g2.sendBuffer(); // Push data to the physical display
}
