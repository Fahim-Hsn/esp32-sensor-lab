# SafeZone: Smart Proximity & Alert System 


Welcome to the **SafeZone** repository! This is a beginner-friendly IoT and Hardware project designed for our ESP32 Workshop. 

##  Project Overview
The SafeZone system acts as an automated security or proximity alert system. Using an Infrared (IR) sensor, the ESP32 monitors its surroundings. 
* **Path Clear:** The Green LED remains ON, indicating a safe zone.
* **Obstacle Detected:** The Red LED turns ON, the Green LED turns OFF, and a 3-leg buzzer module sounds a frequency-based alarm.

This project introduces beginners to handling digital inputs (Sensors) and outputs (LEDs and Buzzers) simultaneously using conditional logic and frequency generation.

##  Components Required
1. 1x ESP32 Development Board
2. 1x IR Obstacle Avoidance Sensor
3. 1x 3-Leg Buzzer Module (Active or Passive)
4. 1x Red LED & 1x Green LED
5. 2x 330Ω Resistors
6. Breadboard & Jumper Wires

##  Wiring Diagram

| Component | Pin / Leg | ESP32 Pin |
| :--- | :--- | :--- |
| **IR Sensor** | OUT / D0 | `GPIO 13` |
| **Red LED** | Long Leg (+) | `GPIO 14` (via 330Ω resistor) |
| **Green LED** | Long Leg (+) | `GPIO 27` (via 330Ω resistor) |
| **3-Leg Buzzer Module** | I/O / S (Signal) | `GPIO 26` |
| | VCC / (+) | `3V3` or `5V` |
| | GND / (-) | `GND` |
| **All Other VCC pins** | VCC / (+) | `3V3` or `Vin` |
| **All Other GND pins** | GND / (-) | `GND` |

##  How to Run the Project
1. Clone this repository or copy the code from `SafeZone.ino`.
2. Open the file in the **Arduino IDE**.
3. Ensure you have the ESP32 Board Manager installed. Select your exact ESP32 board and the correct COM port.
4. Set the Baud Rate in your Serial Monitor to `115200`.
5. Click **Upload**. 
6. Open the Serial Monitor to see real-time status updates!

---
*Created for the 18th Batch Introductory ESP32 Workshop.*
