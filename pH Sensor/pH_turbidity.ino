
#include <Wire.h>
#include <U8g2lib.h>

/* OLED */
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

/* Pins */
#define PH_PIN   34
#define TURB_PIN 35
#define ADC_SAMPLES 10

/* pH calibration */
const float PH_MID_VOLTAGE = 2.50;
const float PH_SLOPE = 0.18;

/* Display control */
float displayPH = -1.0;
const float PH_THRESHOLD = 0.2;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(PH_PIN, ADC_11db);
  analogSetPinAttenuation(TURB_PIN, ADC_11db);
  u8g2.begin();
}

/* Read averaged pH and voltage */
float readPH(float &voltageOut) {
  int sum = 0;
  for (int i = 0; i < ADC_SAMPLES; i++) sum += analogRead(PH_PIN);
  float adcAvg = sum / (float)ADC_SAMPLES;
  voltageOut = adcAvg * (3.3 / 4095.0);
  return 7.0 + (PH_MID_VOLTAGE - voltageOut) / PH_SLOPE;
}

/* Read averaged turbidity voltage */
float readTurbidity(float &voltageOut) {
  int sum = 0;
  for (int i = 0; i < ADC_SAMPLES; i++) sum += analogRead(TURB_PIN);
  float adcAvg = sum / (float)ADC_SAMPLES;
  voltageOut = adcAvg * (3.3 / 4095.0);
  return voltageOut;
}

void loop() {
  float phVolt, turbVolt;
  float currentPH = readPH(phVolt);
  float turbVoltage = readTurbidity(turbVolt);

  // Update displayed pH only if change ≥ 0.2
  if (displayPH < 0 || abs(currentPH - displayPH) >= PH_THRESHOLD) displayPH = currentPH;

  // Water status based on turbidity voltage
  const char* waterStatus;
  if (turbVoltage > 1.4) waterStatus = "CLEAR";
  else if (turbVoltage > 0.9) waterStatus = "CLOUDY";
  else waterStatus = "DIRTY";

  /* OLED display */
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tf);
  u8g2.drawStr(2, 12, "WATER QUALITY");

  u8g2.drawStr(2, 26, "pH");

  // Big pH value
  u8g2.setFont(u8g2_font_logisoso24_tf);
  char phStr[8]; sprintf(phStr, "%.1f", displayPH);
  u8g2.drawStr(2, 52, phStr);

  // Water details
  u8g2.setFont(u8g2_font_6x12_tf);
  u8g2.drawStr(78, 26, waterStatus);
  char turbStr[16]; sprintf(turbStr, "T: %.2fV", turbVoltage);
  u8g2.drawStr(78, 42, turbStr);

  // Small pH sensor voltage
  char voltStr[18]; sprintf(voltStr, "pH V: %.3fV", phVolt);
  u8g2.drawStr(2, 64, voltStr);

  u8g2.sendBuffer();
  delay(1000);
}
