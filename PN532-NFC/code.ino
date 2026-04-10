#include <WiFi.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 22, 21);

// Initialize PN532
#define PN532_IRQ   (4)
#define PN532_RESET (5)
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

// WiFi
const char* ssid = "Fahim";
const char* password = "Fahim1212";

// Hardware pins
const int GREEN_LED = 14;
const int RED_LED = 12;
const int BUZZER = 27;

unsigned long messageTimer = 0;
bool showingMessage = false;

void setup() {
  Serial.begin(115200);
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr); 

  // Initialize NFC module
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {

    u8g2.clearBuffer();
    u8g2.setCursor(0, 15);
    u8g2.print("NFC Module Error!");
    u8g2.sendBuffer();
    while (1);
  }
  nfc.SAMConfig(); 

  connectWiFi();

  showDefaultScreen();
}

void loop() {
  // Return to default screen after 2 seconds
  if (showingMessage && (millis() - messageTimer >= 2000)) {
    showingMessage = false;
    showDefaultScreen();
  }

  if (!showingMessage) {
    uint8_t success;
    uint8_t uid[7];
    uint8_t uidLength;
    
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 50);

    if (success) {
      String cardUID = "";
      for (uint8_t i = 0; i < uidLength; i++) {
        if(uid[i] < 0x10) cardUID += "0";
        cardUID += String(uid[i], HEX);
      }
      cardUID.toUpperCase();

      Serial.println("Card UID: " + cardUID);

      // Beep sound
      digitalWrite(BUZZER, HIGH);
      delay(100); 
      digitalWrite(BUZZER, LOW);

      // Show UID on display
      showScannedCard(cardUID);

      showingMessage = true;
      messageTimer = millis();
    }
  }
}

void showDefaultScreen() {
  u8g2.clearBuffer();
  u8g2.setCursor(0, 20);
  u8g2.print("BAIUST TRANSPORT");
  u8g2.setCursor(15, 45);
  u8g2.print("Scan Your Card");
  u8g2.sendBuffer();
}

// Show scanned card UID
void showScannedCard(String uid) {
  u8g2.clearBuffer();
  u8g2.setCursor(0, 20);
  u8g2.print("Card Detected:");
  u8g2.setCursor(0, 45);
  u8g2.print(uid);
  u8g2.sendBuffer();
}

// Connect to WiFi
void connectWiFi() {
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print("Connecting WiFi...");
  u8g2.sendBuffer();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  u8g2.clearBuffer();
  u8g2.setCursor(0, 25);
  u8g2.print("WiFi Connected!");
  u8g2.sendBuffer();
  delay(1000); 
}
