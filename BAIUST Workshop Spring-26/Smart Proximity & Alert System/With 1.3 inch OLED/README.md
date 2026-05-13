# SafeZone: Smart Proximity & Alert System 

Welcome to the **SafeZone** repository! This project was built as part of the Introductory ESP32 & IoT Workshop. 

SafeZone is a smart proximity alert system that monitors its surroundings using an Infrared (IR) sensor. It features a live OLED dashboard to track how many times the perimeter has been breached, making it a perfect beginner project for learning digital logic, sensor integration, and I2C displays.

##  Features
* **Real-time Obstacle Detection:** Uses an IR sensor to instantly detect physical objects.
* **Visual & Audio Alerts:** Triggers a Red LED and an active buzzer when an object is detected.
* **Live OLED Dashboard:** Displays the current system status (CLEAR / ALERT) and maintains a running count of total detections on a 1.3" OLED screen.
* **Smart Counting (Debouncing):** The system is programmed to only count an object *once* per entry, preventing the counter from rapidly increasing if an object stays still in front of the sensor.

---

##  Hardware Requirements
To build this project, you will need the following components:
1. 1x **ESP32** Development Board
2. 1x **1.3-inch OLED Display** (I2C, SH1106 Controller)
3. 1x **IR Obstacle Avoidance Sensor**
4. 1x **Active Buzzer Module**
5. 1x **Red LED** & 1x **Green LED**
6. 2x **330Ω Resistors**
7. 1x Breadboard & Assorted Jumper Wires

---

##  Connection Diagram

Follow this table to wire your components to the ESP32. **Note:** All GND (Ground) pins should be connected together on the breadboard's negative (-) rail.

| Component | Pin / Leg | ESP32 Connection |
| :--- | :--- | :--- |
| **1.3" OLED Display** | VCC | `3V3` |
| | GND | `GND` |
| | SDA | `GPIO 21` |
| | SCL | `GPIO 22` |
| **IR Sensor** | VCC | `3V3` or `Vin` |
| | GND | `GND` |
| | OUT / D0 | `GPIO 13` |
| **Red LED** | Long Leg (+) | `GPIO 14` *(via 330Ω Resistor)* |
| | Short Leg (-) | `GND` |
| **Green LED** | Long Leg (+) | `GPIO 27` *(via 330Ω Resistor)* |
| | Short Leg (-) | `GND` |
| **Buzzer** | VCC | `3V3` or `Vin` |
| | GND | `GND` |
| | I/O (Signal) | `GPIO 26` |

---

##  Software & Library Setup

Before running the code, you need to set up the Arduino IDE and install the required library for the OLED display.

### 1. Configure ESP32 in Arduino IDE
If you haven't set up the ESP32 yet:
1. Open Arduino IDE -> `File` -> `Preferences`.
2. In "Additional Boards Manager URLs", paste: `https://dl.espressif.com/dl/package_esp32_index.json`
3. Go to `Tools` -> `Board` -> `Boards Manager`, search for **esp32**, and click Install.

### 2. Download the U8g2 Display Library
The 1.3-inch OLED uses the SH1106 controller, which works best with the `U8g2` library.
1. Open Arduino IDE.
2. Go to `Sketch` -> `Include Library` -> `Manage Libraries` (or press `Ctrl+Shift+I`).
3. In the search bar, type **U8g2**.
4. Look for the library named **"U8g2 by oliver"** and click **Install**.

---

##  How to Run the Project

1. Clone this repository or download the `SafeZone_OLED.ino` file.
2. Wire your hardware according to the connection diagram above.
3. Open the file in the Arduino IDE.
4. Go to `Tools` -> `Board` and select your specific ESP32 model (e.g., *DOIT ESP32 DEVKIT V1*).
5. Go to `Tools` -> `Port` and select the COM port your ESP32 is connected to.
6. Click the **Upload** button.
7. Once uploaded, open the **Serial Monitor** (set to `115200` baud rate) to see text outputs, and watch your OLED screen come to life!

---
*Prepared by Fahim Hossain (ID: 1118044, 18th Batch) for the BAIUST IoT Workshop.*
