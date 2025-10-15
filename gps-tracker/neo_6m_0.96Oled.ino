#include <Wire.h>
#include <U8g2lib.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
TinyGPSPlus gps;
HardwareSerial GPSserial(2);
unsigned long lastDisplayMillis = 0;

void setup() {
  Serial.begin(115200);
  GPSserial.begin(9600, SERIAL_8N1, 16, 17);
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 12, "Starting up...");
  u8g2.sendBuffer();
}

void loop() {
  while (GPSserial.available()) {
    gps.encode(GPSserial.read());
  }

  unsigned long now = millis();

  if (now - lastDisplayMillis > 1000) {
    lastDisplayMillis = now;

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);

    if (gps.location.isValid()) {
      char latbuf[32], lonbuf[32], satbuf[16];
      snprintf(latbuf, sizeof(latbuf), "Lat: %.6f", gps.location.lat());
      snprintf(lonbuf, sizeof(lonbuf), "Lon: %.6f", gps.location.lng());
      snprintf(satbuf, sizeof(satbuf), "Sats: %u", gps.satellites.value());
      u8g2.drawStr(0, 12, latbuf);
      u8g2.drawStr(0, 28, lonbuf);
      u8g2.drawStr(0, 44, satbuf);
    } else {
      u8g2.drawStr(0, 24, "Waiting for Satellites...");
    }

    u8g2.sendBuffer();
  }
}
