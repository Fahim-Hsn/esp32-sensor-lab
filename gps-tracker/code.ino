#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
TinyGPSPlus gps;
HardwareSerial GPSserial(2);

unsigned long lastDisplayMillis = 0;

void setup() {
  Serial.begin(115200);
  GPSserial.begin(9600, SERIAL_8N1, 16, 17);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Starting up...");
  delay(2000);
  lcd.clear();
}

void loop() {
  while (GPSserial.available()) {
    gps.encode(GPSserial.read());
  }

  unsigned long now = millis();

  if (now - lastDisplayMillis > 1000) {
    lastDisplayMillis = now;
    lcd.clear();

    if (gps.location.isValid()) {
      lcd.setCursor(0, 0);
      lcd.print("Lat: ");
      lcd.print(gps.location.lat(), 6);

      lcd.setCursor(0, 1);
      lcd.print("Lon: ");
      lcd.print(gps.location.lng(), 6);
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Waiting for GPS fix...");
    }
  }
}

