# ESP32 Soil Moisture Monitor with 1.3" OLED

A simple IoT project using an ESP32 to monitor soil humidity levels in real-time. Data is displayed on a 1.3-inch I2C OLED screen and sent to the Serial Monitor.

##  Hardware Components
* **Microcontroller:** ESP32 (DevKit V1)
* **Sensor:** YL-69 / HL-69 Soil Hygrometer
* **Display:** 1.3-inch OLED 
* **Jumper Wires**

##  Wiring Diagram
| Component | Pin | ESP32 Pin |
| :--- | :--- | :--- |
| **YL-69 Sensor** | VCC | 3.3V |
| | GND | GND |
| | AO (Analog Out) | GPIO 34 |
| **1.3" OLED** | VCC | 3.3V |
| | GND | GND |
| | SCL | GPIO 22 |
| | SDA | GPIO 21 |

##  Getting Started
1.  Install the **U8g2** library in the Arduino IDE.
2.  Connect the hardware as per the wiring table.
3.  Upload the `.ino` file to your ESP32.
4.  Open Serial Monitor at `115200` baud to see raw data for calibration.

##  Features
* Real-time moisture percentage calculation.
* High-contrast display using the SH1106 driver.
* Low power consumption suitable for smart agriculture prototypes.

##  License
MIT License
