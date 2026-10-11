# Session 01: ESP32 Onboarding & Digital I/O
**Target Batch:** CSE 19th Batch, BAIUST  
**Duration:** 2 Hours (120 Minutes)  
**Prerequisites:** Basic C++ syntax (variables, functions, loops)

---

## ⏱️ Session Agenda (120 Minutes)

| Time | Duration | Segment | Key Topics / Actions |
| :--- | :--- | :--- | :--- |
| **00:00 - 00:20** | 20 mins | **Theory: Physical Computing Intro** | Microcontrollers vs Microprocessors, ESP32 specifications, 3.3V logic rule |
| **00:20 - 00:40** | 20 mins | **Toolchain & Board Setup** | Installing Arduino IDE ESP32 core, drivers (CH340/CP2102), COM port check |
| **00:40 - 00:55** | 15 mins | **Hardware Fundamentals** | Anatomy of a Breadboard (rails vs rows), LED polarity, Resistor color codes/Ohm's Law |
| **00:55 - 01:30** | 35 mins | **Hands-on Lab 1: LED Blink** | Connecting external LED on GPIO 2, coding `pinMode`, `digitalWrite`, `delay` |
| **01:30 - 01:55** | 25 mins | **Hands-on Lab 2: Traffic Light & PWM** | Multi-LED sequential logic (Red, Yellow, Green) and brightness control with PWM |
| **01:55 - 02:00** | 5 mins | **Recap & Q/A** | Common errors, Serial Monitor debugging intro, prep for Session 2 |

---

## 🧠 Core Concepts Explained (From C++ to Silicon)

### 1. The 3.3V Logic Rule
- Unlike Arduino Uno (which uses 5V), the **ESP32 is a 3.3V microcontroller**.
- Applying 5V directly to any GPIO pin will permanently destroy the ESP32 chip.
- Always power external components carefully and respect voltage limits.

### 2. Anatomy of a Breadboard
- **Power Rails (+ and -):** Run vertically on both sides; used to distribute `3V3` and `GND`.
- **Terminal Strips:** Run horizontally in 5-hole rows (a-b-c-d-e and f-g-h-i-j). Holes in the same row are electrically connected.
- **Center Divider:** Isolates the two sides. Place ICs or straddle components across this trench.

### 3. LED Polarity & Current Limiting Resistor
- **Anode (+):** Longer leg, connects to GPIO pin via a **220Ω or 330Ω resistor**.
- **Cathode (-):** Shorter leg (flat edge on lens), connects to **GND**.
- **Why a resistor?** LEDs have virtually no internal resistance once forward-biased. Without a resistor, excessive current will burn the LED or the ESP32 pin.

---

## 🛠️ Software Toolchain Setup

1. **Arduino IDE 2.x:** Download and install from [arduino.cc](https://www.arduino.cc/en/software).
2. **ESP32 Board URL:**
   - Go to `File > Preferences`
   - Paste in *Additional boards manager URLs*:
     ```text
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
3. **Install Core:**
   - Go to `Tools > Board > Boards Manager...`
   - Search for `esp32` by Espressif Systems and click **Install**.
4. **Driver Check:**
   - If COM port does not appear in Device Manager, install the USB-to-UART driver for your board's chip (**CP2102** or **CH340**).

---

## 🚀 Hands-on Projects in this Session

1. **[01_LED_Blink](./01_LED_Blink/):**
   - Single LED blinking at custom intervals.
   - Understanding GPIO setup in `setup()` and periodic execution in `loop()`.
2. **[02_Traffic_Light_PWM](./02_Traffic_Light_PWM/):**
   - Simulating an automated traffic junction using 3 LEDs.
   - Smooth LED fading using ESP32 Hardware PWM channels (`ledcAttachPin`, `ledcWrite`).

---

## ⚠️ Troubleshooting Guide for Instructors & Students

- **Problem:** `A fatal error occurred: Failed to connect to ESP32: Timed out waiting for packet header`
  - **Fix:** When `Connecting......____....` appears in the IDE console, **press and hold the BOOT button** on the ESP32 board for 2 seconds until `Writing at 0x...` begins, then release.
- **Problem:** LED does not light up.
  - **Check 1:** Verify polarity — flip the LED.
  - **Check 2:** Verify that the resistor is in series and not plugged into parallel holes on the same row.
  - **Check 3:** Ensure the ground wire is connected to a `GND` pin on the ESP32.
