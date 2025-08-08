#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

//#define DHTPIN 4         // DHT11 data pin
//#define DHTTYPE DHT11    // DHT11 sensor

DHT dht11_sensor(4, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27 or 0x3F

void setup() {
  lcd.init();
  lcd.backlight();
  dht11_sensor.begin();
}

void loop() {
  int temp = dht11_sensor.readTemperature();
  int hum = dht11_sensor.readHumidity();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Todays Weather...");
  delay(1500);
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(hum);
  lcd.print(" %");

  delay(3000);
}

