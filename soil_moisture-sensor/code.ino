#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// SH1106 driver for 1.3" I2C OLED
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

const int sensorPin = 34; 

void setup() {
  Serial.begin(115200);
  u8g2.begin();
}

void loop() {
  int rawValue = analogRead(sensorPin);
  
  // Map 4095 (Dry) to 0 and 0 (Wet) to 100
  int moisturePercent = map(rawValue, 4095, 0, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  u8g2.clearBuffer();					
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 20, "Soil Moisture:");
  
  u8g2.setFont(u8g2_font_logisoso24_tf); 
  u8g2.setCursor(0, 55);
  u8g2.print(moisturePercent);
  u8g2.print("%");
  u8g2.sendBuffer();

  Serial.printf("Raw: %d | Percent: %d%%\n", rawValue, moisturePercent);
  delay(2000);
}
