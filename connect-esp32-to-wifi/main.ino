#include<Wire.h>
#include<WiFi.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  //Wire.begin(21,22);
  //lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("wifi scanning...");
  delay(2000);

}

void loop()
{
  int n = WiFi.scanNetworks();
  
  lcd.clear();
  if (n == 0) {
    lcd.setCursor(0, 0);
    lcd.printf("no wifi");
  } else {
    lcd.setCursor(0, 0);
    lcd.printf("wifi found:");
    lcd.setCursor(0, 1);
    lcd.print(n);
    lcd.setCursor(3, 1);
    lcd.printf("SSID");

    lcd.setCursor(0, 0);
    String ssid = WiFi.SSID(0);
    int rssi = WiFi.RSSI(0);
    lcd.print(ssid);
    lcd.print(" ");
    lcd.print(rssi);
    
  }
   delay(2000);
}
