#include <Arduino.h>

#define PH_PIN 34 

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); 
}

void loop() {
  float voltage = 0;
  unsigned long avgValue = 0;
  int buf[10], temp;
  
  for(int i=0; i<10; i++) { 
    buf[i] = analogRead(PH_PIN);
    delay(10);
  }
  
  for(int i=0; i<9; i++) {
    for(int j=i+1; j<10; j++) {
      if(buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  
  for(int i=2; i<8; i++) {
    avgValue += buf[i];
  }
  
  float avg_adc = (float)avgValue / 6.0;
  voltage = avg_adc * (3.3 / 4095.0); 

  Serial.print("Raw ADC: "); Serial.print(avg_adc);
  Serial.print(" | Voltage: "); Serial.println(voltage, 4); 
  
  delay(1000);
}
