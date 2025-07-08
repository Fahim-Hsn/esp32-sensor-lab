## ESP32 Sensor Lab 

Welcome to the **ESP32 Sensor Lab** a personal learning collection of beginner friendly IoT projects using ESP32 and various sensors.

Each folder inside this repo contains:
- Arduino code (`main.ino`)
- Simple wiring diagram (if available)
- Short explanation of what the project does

---

##  Projects

| Folder Name            | Sensor/Module             | What it Does                                |
|------------------------|---------------------------|---------------------------------------------|
| `led-blink`            | Built in LED              | Blinks the ESP32 onboard LED every second   |
| `i2c-lcd-display`      | 16x2 I2C LCD              | Displays simple text like "Hello ESP32"     |
| `dht11-sensor`         | DHT11                     | Shows temperature and humidity              |
| `ir-sensor`            | IR Obstacle Sensor        | Detects objects in front of the sensor      |
| `ultrasonic-sensor`    | HC-SR04                   | Measures distance using sound waves         |
| `connect_esp32_to_wifi`| ESP32 & i2c lcd display   | Scan WiFi SSID and connect to the WiFi      |
| `wifi-repeater`        | ESP32 WiFi                | Repeats WiFi signal like a mini extender    |
| `gps-tracker`          | GPS Module (e.g., NEO-6M) | Gets live coordinates on Serial & in dispaly|


---

## What You Need

- ESP32 Dev Board  
- Arduino IDE with ESP32 Board support  
- Jumper wires + Breadboard  
- Sensors and modules listed above



## How to Use This Repo

1. Pick any folder (e.g., `dht11-sensor`)
2. Open the `main.ino` file with Arduino IDE
3. Upload the code to your ESP32
4. Connect your components as shown in the wiring diagram (circuit-diagram.png))
5. Open Serial Monitor or watch output on LCD

---

##  How to Add ESP32 Board in Arduino IDE

If you're using ESP32 for the first time in Arduino IDE follow these simple steps:

### Step 1: Add Board URL

1. Open **Arduino IDE**
2. Go to **File → Preferences**
3. In the **"Additional Board Manager URLs"** field, paste this:
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
4. Click **OK**


### Step 2: Install ESP32 Board

1. Go to **Tools → Board → Boards Manager**
2. Search for **esp32**
3. Click **Install** on **"esp32 by Espressif Systems"**
4. After installation, go to **Tools → Board**, and select:


## Quick Test Code (LED Blink)

To test your ESP32 board try this simple blink code:

```cpp
void setup() {
  pinMode(2, OUTPUT); // GPIO 2 is usually the built in LED
}

void loop() {
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}
```
Upload this code, and your ESP32’s onboard LED should start blinking

### Tip:
Make sure to select the correct COM Port:
Tools → Port → [Your ESP32 COM Port] (like COM3 or /dev/ttyUSB0)

---

## Why I Made This
I'm learning how to use ESP32 with sensors. This repo helps me:
- Track my learning progress
- Keep everything in one place
- Help others who are just getting started








