#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Initialize OLED with SH1106 driver
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

#define PH_PIN 34 

// --- Calibration Settings ---
// Set 'calibration_voltage' to the voltage you measured at pH 7.0 (2.08V)
float calibration_voltage = 2.08; 
float neutral_ph = 7.0;

void setup() {
  Serial.begin(115200);
  u8g2.begin();
  
  analogReadResolution(12); // Set ESP32 ADC to 12-bit (0 - 4095)
  pinMode(PH_PIN, INPUT);
  
  // Startup Screen
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(20, 35, "pH Sensor Ready");
  u8g2.sendBuffer();
  delay(2000);
}

void loop() {
  unsigned long int avgValue = 0; 
  int buf[20], temp;
  
  // Take 20 samples to stabilize reading
  for(int i=0; i<20; i++) { 
    buf[i] = analogRead(PH_PIN);
    delay(10);
  }
  
  // Sort samples from small to large (Median Filter algorithm)
  for(int i=0; i<19; i++) {
    for(int j=i+1; j<20; j++) {
      if(buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  
  // Average the middle 10 samples to ignore extreme noise/outliers
  avgValue = 0;
  for(int i=5; i<15; i++) {
    avgValue += buf[i];
  }
  
  // Convert ADC value to Voltage (3.3V logic)
  float avg_adc = (float)avgValue / 10.0;
  float voltage = avg_adc * (3.3 / 4095.0); 
  
  // Calculate pH: Formula is y = mx + c
  // -5.70 is the standard slope for these sensors
  float ph_act = -5.70 * (voltage - calibration_voltage) + neutral_ph;

  // Debugging
  Serial.print("Voltage: "); Serial.print(voltage);
  Serial.print(" | pH: "); Serial.println(ph_act);

  // --- Update OLED Display ---
  u8g2.clearBuffer();          
  
  // Draw Title
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.drawStr(35, 10, "pH Monitor");
  u8g2.drawHLine(0, 14, 128);

  // Draw Voltage (Small Font)
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setCursor(0, 60);
  u8g2.print("Volt: ");
  u8g2.print(voltage);

  // Draw pH Value (Large Font)
  u8g2.setFont(u8g2_font_helvB18_tf); 
  u8g2.setCursor(25, 45);
  u8g2.print("pH: ");
  u8g2.print(ph_act, 1); 

  u8g2.sendBuffer();          
  delay(500);
}
