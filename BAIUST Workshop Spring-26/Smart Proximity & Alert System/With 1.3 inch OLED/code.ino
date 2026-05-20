#include <U8g2lib.h>
#include <Wire.h>

// Initialize the 1.3-inch OLED (SH1106 via I2C)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// Define Hardware Pins
const int irPin = 13;        // IR Sensor OUT pin connected to GPIO 13
const int redLed = 14;       // Red LED connected to GPIO 14
const int greenLed = 27;     // Green LED connected to GPIO 27
const int buzzerPin = 26;    // 3-Leg Buzzer Signal (S) pin connected to GPIO 26

// Variables for counting obstacles
int obstacleCount = 0;
bool isObstaclePresent = false; 

// Declaration of custom function
void updateDisplay(String statusText, int count);

void setup() {
  Serial.begin(115200);
  
  // Setup Pins
  pinMode(irPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT); // Configure buzzer signal pin as OUTPUT

  // Initial State: All OFF
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  noTone(buzzerPin);          // Ensure the 3-leg buzzer is completely silent at startup

  // Initialize the OLED Display
  u8g2.begin();
  
  // Show a welcome screen
  u8g2.clearBuffer();					
  u8g2.setFont(u8g2_font_ncenB08_tr);	// Choose a suitable font
  u8g2.drawStr(15, 30, "SafeZone System");
  u8g2.drawStr(30, 45, "Initializing...");
  u8g2.sendBuffer();
  delay(2000); // Show welcome screen for 2 seconds
}

void loop() {
  int sensorState = digitalRead(irPin);

  // --- LOGIC BLOCK ---
  if (sensorState == LOW) { 
    // Obstacle Detected
    
    // Only increase count if this is a NEW obstacle
    if (isObstaclePresent == false) {
      obstacleCount++;
      isObstaclePresent = true; 
      Serial.print("Obstacle Count: ");
      Serial.println(obstacleCount);
    }

    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    
    // 3-Leg Buzzer Beep using tone()
    tone(buzzerPin, 1000);        // Send 1000Hz frequency to generate beep
    delay(100);                   // Beep for 0.1 seconds
    noTone(buzzerPin);            // Turn OFF the sound
    delay(100);                   // Silence for 0.1 seconds

    // Update Display for ALERT
    updateDisplay("ALERT!", obstacleCount);
    
  } else {
    // No Obstacle (Path is Clear)
    isObstaclePresent = false; 

    digitalWrite(redLed, LOW);
    noTone(buzzerPin);            // Keep the 3-leg buzzer strictly OFF
    digitalWrite(greenLed, HIGH); 
    
    // Update Display for SAFE
    updateDisplay("CLEAR", obstacleCount);
    delay(100);                   // Small delay to stabilize readings
  }
}

// --- CUSTOM FUNCTION TO UPDATE THE OLED ---
void updateDisplay(String statusText, int count) {
  u8g2.clearBuffer(); // Clear internal memory
  
  // 1. Draw Title
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.drawStr(0, 15, "SafeZone Monitor");
  u8g2.drawLine(0, 20, 128, 20);      

  // 2. Draw Status
  u8g2.setFont(u8g2_font_ncenB10_tr); 
  u8g2.setCursor(0, 40);
  u8g2.print("Status: ");
  u8g2.print(statusText);

  // 3. Draw Counter
  u8g2.setCursor(0, 60);
  u8g2.print("Count: ");
  u8g2.print(count);

  u8g2.sendBuffer(); 
}
