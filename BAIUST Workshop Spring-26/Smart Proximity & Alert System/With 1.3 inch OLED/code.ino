#include <U8g2lib.h>
#include <Wire.h>

// Initialize the 1.3-inch OLED 
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// Define Hardware Pins
const int irPin = 13;       
const int redLed = 14;      
const int greenLed = 27;    
const int buzzerPin = 26;   

// Variables for counting obstacles
int obstacleCount = 0;
bool isObstaclePresent = false; 

void setup() {
  Serial.begin(115200);
  
  // Setup Pins
  pinMode(irPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initial State: All OFF
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(buzzerPin, LOW);

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
    // BADHA PEYECHE (Obstacle Detected)
    
    // Only increase count if this is a NEW obstacle
    if (isObstaclePresent == false) {
      obstacleCount++;
      isObstaclePresent = true; 
      Serial.print("Obstacle Count: ");
      Serial.println(obstacleCount);
    }

    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    
    // Buzzer Beep
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);

    // Update Display for ALERT
    updateDisplay("ALERT!", obstacleCount);
    
  } else {
    // RASTA FAKA (No Obstacle)
    isObstaclePresent = false; 

    digitalWrite(redLed, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(greenLed, HIGH);
    
    // Update Display for SAFE
    updateDisplay("CLEAR", obstacleCount);
    delay(100);
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
