# EchoGauge: Ultrasonic Distance Tracker with OLED Display

Welcome to the **EchoGauge** repository! This project demonstrates how to interface an HC-SR04 Ultrasonic Sensor with an ESP32 to measure distance accurately in real-time and display the live output on a 1.3-inch OLED dashboard.

##  Features
* **Non-contact Distance Measurement:** Uses ultrasonic sound waves to compute distance ($2\text{ cm}$ to $400\text{ cm}$).
* **Live OLED Interface:** Smoothly updates the calculated distance on a 1.3" screen using the high-performance `U8g2` library.
* **Error Handling:** Automatically detects and displays "Out of Range" if an object is too close or beyond the sensor's capacity.
* **High-Speed Telemetry:** Transmits concurrent live data to the Arduino Serial Monitor at $115200\text{ Baud}$.

---

##  Components Required
1. 1x **ESP32** Development Board
2. 1x **HC-SR04 Ultrasonic Distance Sensor**
3. 1x **1.3-inch OLED Display** (I2C, SH1106 Controller)
4. 1x Breadboard & Assorted Jumper Wires

---

##  Connection Diagram

Please connect the components to your ESP32 according to the table below. Note that the Ultrasonic sensor performs best when powered by $5\text{V}$ ($Vin$).

| Component | Pin / Leg | ESP32 Connection |
| :--- | :--- | :--- |
| **1.3" OLED Display** | VCC | `3V3` |
| | GND | `GND` |
| | SDA | `GPIO 21` |
| | SCL | `GPIO 22` |
| **HC-SR04 Sensor** | VCC | `Vin` (5V) |
| | GND | `GND` |
| | Trig | `GPIO 5` |
| | Echo | `GPIO 18` |

---

##  Software & Library Setup

### 1. Board Installation
Make sure your Arduino IDE is ready for ESP32. If not, append the ESP32 URL into your IDE Preferences Boards Manager, search for **esp32 by Espressif Systems**, and hit install.

### 2. Dependency Library
This project utilizes the standard **U8g2** graphic library to handle the SH1106 display chip efficiently.
1. In Arduino IDE, navigate to `Sketch` -> `Include Library` -> `Manage Libraries`.
2. Search for **U8g2**.
3. Locate **"U8g2 by oliver"** and install the latest stable version.

---

##  How to Run the Project
1. Clone this repository or copy the code from `Ultrasonic_OLED.ino`.
2. Connect the physical hardware securely as instructed in the wiring diagram.
3. Open the script file in your **Arduino IDE**.
4. Select your specific ESP32 environment and link the operational target COM port under `Tools`.
5. Upload the sketch.
6. Launch the **Serial Monitor** adjusted to `115200` to preview text metrics alongside your live hardware display unit!

---
*Created for the 18th Batch Introductory ESP32 Workshop.*
