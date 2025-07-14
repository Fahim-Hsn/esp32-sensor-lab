#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "WFAF";
const char* password = "WFAF1212";

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  lcd.init();            
  lcd.backlight();       
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");
  
  WiFi.begin(ssid, password); 

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");

  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP()); 
}

void loop() {

}
