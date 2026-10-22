# ESP32 Sensor Lab

A comprehensive, open-source collection of beginner to advanced IoT projects, sensor integrations, display interfaces, camera streaming systems, arcade games, and university workshop materials built on the **Espressif ESP32** platform.

---

## Repository Table of Contents

- [Project Catalog](#project-catalog)
  - [1. Camera and Vision Systems](#1-camera-and-vision-systems)
  - [2. Environmental and Physical Sensors](#2-environmental-and-physical-sensors)
  - [3. Displays and User Interfaces](#3-displays-and-user-interfaces)
  - [4. Arcade Games and Graphics](#4-arcade-games-and-graphics)
  - [5. Wireless and Networking](#5-wireless-and-networking)
  - [6. University Workshops and Curricula](#6-university-workshops-and-curricula)
- [Hardware and Sensor Interface Reference](#hardware-and-sensor-interface-reference)
- [Development Environment Setup](#development-environment-setup)
  - [Option A: Arduino IDE Setup](#option-a-arduino-ide-setup)
  - [Option B: PlatformIO IDE Setup (Recommended for Camera)](#option-b-platformio-ide-setup-recommended-for-camera)
- [Troubleshooting Common Issues](#troubleshooting-common-issues)
- [Author and License](#author-and-license)

---

## Project Catalog

### 1. Camera and Vision Systems

| Project / Folder | Hardware / Sensor | Description | Tools / Framework |
| :--- | :--- | :--- | :--- |
| [`esp32s3_cam_config`](./esp32s3_cam_config) | **ESP32-S3 N16R8 CAM**<br>(OV2640 / OV3660 / OV5640) | Comprehensive dual-mode camera testing suite with two standalone projects:<br>• **`01_wifi_ap_cam_server`**: Independent Wi-Fi SoftAP server with instant Captive Portal DNS (Port 53), isolated MJPEG video streaming (Port 81), and responsive Glassmorphism dashboard.<br>• **`02_usb_type_c_streamer`**: High-speed direct Type-C streaming at 921,600 baud / Native USB CDC paired with a hardware-accelerated, zero-flicker HTML5 Web Serial Canvas viewer. | PlatformIO (VS Code)<br>Web Serial API |

---

### 2. Environmental and Physical Sensors

| Project / Folder | Sensor / Module | Interface | Description |
| :--- | :--- | :--- | :--- |
| [`dht11-sensor`](./dht11-sensor) | DHT11 | Digital (1-Wire) | Reads ambient temperature and relative humidity with wiring diagrams and Arduino sketches. |
| [`Fire-Sensor`](./Fire-Sensor) | Flame Sensor (IR Phototransistor) | Digital / Analog | Detects open flames and fire sources via IR wave detection; triggers alerts upon threshold breach. |
| [`IR-sensor`](./IR-sensor) | TCRT5000 / LM393 IR Module | Digital | Detects physical obstacles and proximity using infrared reflectance; includes onboard sensitivity tuning. |
| [`LDR-sensor`](./LDR-sensor) | Light Dependent Resistor | Analog (ADC) | Measures ambient light intensity for automatic day/night detection and automated lighting switches. |
| [`Motion-sensor`](./Motion-sensor) | HC-SR501 PIR Motion Sensor | Digital | Passive infrared motion detector identifying human and animal movement with adjustable hold-time. |
| [`soil_moisture-sensor`](./soil_moisture-sensor) | Resistive Soil Moisture Sensor | Analog / Digital | Measures soil volumetric water content for automated plant irrigation systems. |
| [`pH Sensor`](./pH%20Sensor) | Analog pH Meter & Turbidity Probe | Analog (ADC) | Liquid quality monitoring system measuring water acidity/alkalinity (pH) and optical turbidity. |
| [`PN532-NFC`](./PN532-NFC) | PN532 NFC / RFID Module | I2C / SPI / HSU | Reads and writes 13.56 MHz RFID cards, keyfobs, and NFC-enabled mobile devices. |
| [`gps-tracker`](./gps-tracker) | NEO-6M GPS Module | UART (Serial) | Fetches global positioning coordinates (Latitude, Longitude, Altitude, Speed, Satellites) and renders them live on 0.96" and 1.3" I2C OLED displays. |

---

### 3. Displays and User Interfaces

| Project / Folder | Display / Output | Interface | Description |
| :--- | :--- | :--- | :--- |
| [`led-blink`](./led-blink) | Onboard / External LED | GPIO Output | Fundamental Hello-World project demonstrating GPIO state toggling, timer delays, and circuit wiring. |
| [`i2c-lcd-display`](./i2c-lcd-display) | 16x2 Character LCD (PCF8574) | I2C | Displays multi-line alphanumeric text and custom characters using a 2-wire I2C backpack. |
| [`i2c-OLED display`](./i2c-OLED%20display) | 0.96" SSD1306 OLED (128x64) | I2C | High-contrast graphical OLED display showing text, geometrical shapes, icons, and real-time sensor charts. |

---

### 4. Arcade Games and Graphics

| Project / Folder | Hardware Target | Display | Description |
| :--- | :--- | :--- | :--- |
| [`snake-game`](./snake-game) | ESP32 + Push Buttons | 0.96" SSD1306 OLED | Fully interactive classic retro Snake arcade game with collision detection, real-time score tracking, and smooth frame updates. |
| [`dx-ball`](./dx-ball) | ESP32 + Push Buttons | 0.96" SSD1306 OLED | Classic brick-breaker arcade game featuring ball physics, paddle bouncing mechanics, destructible bricks, and game-over states. |

---

### 5. Wireless and Networking

| Project / Folder | Protocol / Module | Description |
| :--- | :--- | :--- |
| [`connect-esp32-to-wifi`](./connect-esp32-to-wifi) | 802.11 b/g/n Wi-Fi | Dual-mode networking example containing: (1) `wifi_scan.ino` to scan and list all nearby 2.4 GHz SSID networks and RSSI signal strengths, and (2) `connect_wifi.ino` to authenticate with a WPA2 network and obtain a DHCP IP address. |

---

### 6. University Workshops and Curricula

| Workshop Directory | Target Audience / Batch | Topics Covered |
| :--- | :--- | :--- |
| [`BAIUST Workshop Fall-26 (CSE 19th)`](./BAIUST%20Workshop%20Fall-26%20(CSE%2019th)) | CSE 19th Batch, BAIUST | Structured two-part hands-on workshop curriculum:<br>• **Session 01**: ESP32 architecture onboarding, toolchains, digital input/output, and PWM control.<br>• **Session 02**: Analog sensors, threshold triggers, relays, actuators, and OLED display integration. |
| [`BAIUST Workshop Spring-26`](./BAIUST%20Workshop%20Spring-26) | Engineering Students, BAIUST | Practical laboratory projects including:<br>• Basic GPIO Led Blink.<br>• Smart Proximity & Alert System (Ultrasonic + Buzzer + Multi-color LEDs).<br>• WaveMeter ultrasonic distance measuring system. |

---

## Hardware and Sensor Interface Reference

The following table provides the default hardware communication interfaces and typical pin connections for standard ESP32 boards (ESP32-WROOM-32 / ESP32-DevKitC):

| Interface Type | Standard ESP32 Default Pins | Typical Connected Modules |
| :--- | :--- | :--- |
| **I2C Bus** | **SDA:** GPIO 21<br>**SCL:** GPIO 22 | 16x2 I2C LCD, SSD1306 OLED, PN532 NFC |
| **Hardware UART1** | **RX1:** GPIO 9 / 16<br>**TX1:** GPIO 10 / 17 | NEO-6M GPS Module |
| **Hardware UART2** | **RX2:** GPIO 16<br>**TX2:** GPIO 17 | Serial Debugging / Secondary Microcontroller |
| **Analog Inputs (ADC1)** | GPIO 32, 33, 34, 35, 36 (VP), 39 (VN) | LDR Light Sensor, Soil Moisture, pH Meter, Flame Sensor |
| **Digital GPIO** | GPIO 2, 4, 5, 12, 13, 14, 15, 18, 19, 23, 25, 26, 27 | DHT11, PIR Motion Sensor, Ultrasonic HC-SR04, Buttons, Relays |
| **Camera DVP Interface** | Defined in [`camera_pins.h`](./esp32s3_cam_config/01_wifi_ap_cam_server/src/camera_pins.h) | OV2640, OV3660, OV5640 Image Sensors |

> **Note on ADC2:** Avoid using ADC2 pins (GPIO 0, 2, 4, 12, 13, 14, 15, 25, 26, 27) for analog reads when Wi-Fi is actively transmitting, as the Wi-Fi driver shares and restricts ADC2. Always prefer **ADC1** pins (GPIO 32–39) for analog sensors.

---

## Development Environment Setup

### Option A: Arduino IDE Setup

1. **Install Arduino IDE:** Download version 2.0+ from [arduino.cc](https://www.arduino.cc/en/software).
2. **Add ESP32 Board Package URL:**
   - Open **File** -> **Preferences**.
   - In the **Additional Board Manager URLs** field, enter:
     ```text
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Click **OK**.
3. **Install the Core:**
   - Go to **Tools** -> **Board** -> **Boards Manager**.
   - Search for `esp32` and install **esp32 by Espressif Systems**.
4. **Install Required Libraries via Library Manager (`Ctrl + Shift + I`):**
   - `Adafruit GFX Library` (for OLED and graphical games)
   - `Adafruit SSD1306` (for 0.96" and 1.3" OLED displays)
   - `LiquidCrystal_I2C` (for 16x2 character displays)
   - `DHT sensor library` by Adafruit (for DHT11/DHT22)
   - `TinyGPSPlus` (for NEO-6M GPS parsing)
5. **Select Your Board & Port:**
   - **Board:** Select `ESP32 Dev Module` (or `ESP32S3 Dev Module` for S3 projects).
   - **Port:** Select your corresponding COM port (e.g., `COM3`, `COM4`, `/dev/ttyUSB0`).
   - Click **Upload**.

---

### Option B: PlatformIO IDE Setup (Recommended for Camera)

For complex projects with external PSRAM, custom partition tables, and dual HTTP servers like [`esp32s3_cam_config`](./esp32s3_cam_config):

1. Install **Visual Studio Code**.
2. Open the **Extensions** panel (`Ctrl + Shift + X`), search for **PlatformIO IDE**, and click **Install**.
3. Open any subproject folder directly in VS Code (e.g., `File` -> `Open Folder` -> select `esp32s3_cam_config/01_wifi_ap_cam_server`).
4. PlatformIO will automatically read `platformio.ini`, download the toolchain, and configure dependencies.
5. Click the checkmark icon in the bottom status bar to **Build**, or the arrow icon (`->`) to **Upload**.

---

## Troubleshooting Common Issues

### 1. `A fatal error occurred: Failed to connect to ESP32: Timed out waiting for packet header`
- **Cause:** The ESP32 bootloader did not automatically enter flash download mode.
- **Solution:** Press and hold down the **BOOT** button on the ESP32 board, click **Upload** in the IDE, and release the BOOT button once the terminal displays `Connecting........_____`.

### 2. COM Port Not Detected / Missing in Device Manager
- **Cause:** Missing USB-to-UART bridge drivers on Windows.
- **Solution:** Install the driver matching your board's interface chip:
  - [WCH CH340 / CH341 Driver](https://www.wch-ic.com/downloads/CH341SER_EXE.html)
  - [Silicon Labs CP210x Universal Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

### 3. `Brownout detector was triggered`
- **Cause:** Insufficient supply current during Wi-Fi transmission or camera initialization.
- **Solution:** Connect the ESP32 directly to a primary motherboard USB 3.0 port or an external 5V 2A power supply. Avoid unpowered USB hubs or long, thin USB cables.

### 4. I2C Device Not Found / Blank Screen
- **Cause:** Incorrect I2C address or reversed SDA/SCL wiring.
- **Solution:** Run an I2C scanner sketch. Standard addresses are `0x27` or `0x3F` for 16x2 LCDs, and `0x3C` or `0x3D` for SSD1306 OLED displays.

---

## Author and License

- **Author:** [Fahim Hossain](https://github.com/Fahim-Hsn)
- **Repository:** [https://github.com/Fahim-Hsn/esp32-sensor-lab](https://github.com/Fahim-Hsn/esp32-sensor-lab)
- **License:** Open source for academic, personal, and experimental IoT development.
