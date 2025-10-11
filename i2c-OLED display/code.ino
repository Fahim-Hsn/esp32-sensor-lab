#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Wire.begin(21, 22);  // SDA=21, SCL=22 (ESP32)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  
    Serial.println(F("OLED not found"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);    
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Hello ESP32!");
  display.setCursor(0, 30);
  display.println("OLED Display Working!");
  display.display();          
}

void loop() {

}
