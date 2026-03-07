#include <Wire.h>
#include <TinyGPS++.h>
#include <U8g2lib.h>

#define DHAKA_UTC_OFFSET_HRS 6

// GPS UART pins
#define GPS_RX_PIN 16   // ESP32 RX2 ← GPS TX
#define GPS_TX_PIN 17   // ESP32 TX2 → GPS RX

#define OLED_INTERVAL_MS 1000
#define DEVICE_ID "bus01"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

TinyGPSPlus gps;
HardwareSerial GPSserial(2);

unsigned long lastOled = 0;

// Filters
const int   MIN_SATS        = 5;    
const float MAX_HDOP        = 2.5;  
const float MOVE_DEADBAND_M = 1.0;  
const float SPEED_CLAMP_KPH = 5.0;  
const float EMA_ALPHA       = 0.40; 

double lastLatFiltered = NAN, lastLonFiltered = NAN;
float  speedEMA = 0.0f;

struct FiltOut {
  bool   valid;
  double lat, lon;
  float  speedKph;
};

static inline String formatTwo(uint8_t v) { 
  char b[3]; 
  snprintf(b, sizeof(b), "%02u", v); 
  return String(b); 
}

double haversineMeters(double lat1, double lon1, double lat2, double lon2) {
  const double R = 6371000.0;
  double dLat = (lat2 - lat1) * DEG_TO_RAD;
  double dLon = (lon2 - lon1) * DEG_TO_RAD;
  double a = sin(dLat/2) * sin(dLat/2) + cos(lat1 * DEG_TO_RAD) * cos(lat2 * DEG_TO_RAD) * sin(dLon/2) * sin(dLon/2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  return R * c;
}

FiltOut filterReading() {
  FiltOut out{false, 0, 0, 0};
  if (!gps.location.isValid()) return out;

  int sats = gps.satellites.isValid() ? gps.satellites.value() : 0;
  float hdop = gps.hdop.isValid() ? gps.hdop.hdop() : 99.0f;

  double lat = gps.location.lat();
  double lon = gps.location.lng();

  if (isnan(lastLatFiltered)) { lastLatFiltered = lat; lastLonFiltered = lon; }

  if (sats < MIN_SATS || hdop > MAX_HDOP) {
    out.valid = true; out.lat = lastLatFiltered; out.lon = lastLonFiltered; out.speedKph = 0;
    return out;
  }

  double dist = haversineMeters(lastLatFiltered, lastLonFiltered, lat, lon);
  if (dist <= MOVE_DEADBAND_M) { 
    lat = lastLatFiltered; lon = lastLonFiltered; 
  } else { 
    lastLatFiltered = lat; lastLonFiltered = lon; 
  }

  float sp = gps.speed.isValid() ? gps.speed.kmph() : 0.0f;
  if (sp <= SPEED_CLAMP_KPH) sp = 0.0f;
  speedEMA = EMA_ALPHA * sp + (1.0f - EMA_ALPHA) * speedEMA;

  out.valid = true; out.lat = lat; out.lon = lon; out.speedKph = speedEMA;
  return out;
}

void oledDraw() {
  FiltOut fo = filterReading();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);

  // Header
  u8g2.setDrawColor(1); u8g2.drawBox(0, 0, 128, 14);
  u8g2.setDrawColor(0);
  u8g2.setCursor(2, 11); u8g2.print("ID: "); u8g2.print(DEVICE_ID);
  u8g2.setDrawColor(1);

  if (fo.valid) {
    u8g2.setCursor(0, 26); u8g2.print("Lat: "); u8g2.print(fo.lat, 6);
    u8g2.setCursor(0, 38); u8g2.print("Lon: "); u8g2.print(fo.lon, 6);

    u8g2.setCursor(0, 50); u8g2.print("Sats: ");
    if (gps.satellites.isValid()) u8g2.print(gps.satellites.value()); else u8g2.print("-");

    u8g2.setCursor(64, 50); u8g2.print("Spd: "); u8g2.print(fo.speedKph, 1); u8g2.print("k");

    u8g2.setCursor(0, 62); u8g2.print("Time: ");
    if (gps.time.isValid()) {
      int h = ((int)gps.time.hour() + DHAKA_UTC_OFFSET_HRS) % 24;
      u8g2.print(formatTwo(h)); u8g2.print(':'); 
      u8g2.print(formatTwo(gps.time.minute())); u8g2.print(':'); 
      u8g2.print(formatTwo(gps.time.second()));
    } else {
      u8g2.print("--:--:--");
    }

    // Heading dial
    if (gps.course.isValid()) {
      float c = gps.course.deg(); 
      int cx = 118, cy = 26;
      float rad = (c - 90) * DEG_TO_RAD;
      int x2 = cx + (int)(10 * cos(rad)); 
      int y2 = cy + (int)(10 * sin(rad));
      u8g2.drawCircle(cx, cy, 12, U8G2_DRAW_ALL); 
      u8g2.drawLine(cx, cy, x2, y2);
    }
  } else {
    u8g2.setCursor(0, 26); u8g2.print("Searching GPS...");
    u8g2.setCursor(0, 38); u8g2.print("Fix: None");
    u8g2.setCursor(0, 50); u8g2.print("Sats: -   Spd: -");
    u8g2.setCursor(0, 62); u8g2.print("Time: --:--:--");
  }

  u8g2.sendBuffer();
}

void setup() {
  Serial.begin(115200);
  u8g2.begin();
  GPSserial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_9x18B_tr);
  u8g2.drawStr(0, 25, "GPS System");
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(0, 45, "Initializing...");
  u8g2.sendBuffer();
  delay(1000);
}

void loop() {
  // Read GPS data
  while (GPSserial.available() > 0) {
    gps.encode(GPSserial.read());
  }

  // Update OLED at defined interval
  unsigned long now = millis();
  if (now - lastOled >= OLED_INTERVAL_MS) {
    lastOled = now;
    oledDraw();
  }
}
