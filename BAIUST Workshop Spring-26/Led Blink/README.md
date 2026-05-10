# ESP32 Basic LED Blink Workshop

This repository contains the most basic "Hello World" project for the ESP32 microcontroller. It is designed for beginners attending an IoT workshop to understand GPIO (General Purpose Input/Output) control.

## Project Overview
The goal of this project is to interface an external LED with an ESP32 board and program it to blink at 500ms intervals.

## Hardware Requirements
- **ESP32 Development Board** (e.g., DEVKIT V1)
- **LED** (Any color)
- **220Ω Resistor**
- **Breadboard & Jumper Wires**
- **Micro-USB Cable**

## Circuit Connection
Refer to `esp32_led_circuit.png` for the visual guide:
1. **LED Anode (Long Leg):** Connect to **GPIO 2 (D2)** on the ESP32.
2. **LED Cathode (Short Leg):** Connect to one end of the **220Ω Resistor**.
3. **Resistor (Other End):** Connect to the **GND** pin on the ESP32.

## Software Setup
1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Go to **File > Preferences** and add the ESP32 board URL: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`.
3. Go to **Tools > Board > Boards Manager**, search for **esp32**, and install the package.
4. Select your board (e.g., **DOIT ESP32 DEVKIT V1**) from **Tools > Board**.

## How to Run
1. Clone this repository or copy the code from your `.ino` file.
2. Connect your ESP32 to your computer.
3. Select the correct COM port in **Tools > Port**.
4. Click the **Upload** button.

## Troubleshooting
- If the code fails to upload, press and hold the **BOOT** button on the ESP32 until the status changes to "Writing...".
- Ensure the LED is oriented correctly (Long leg is positive).
