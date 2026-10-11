# Lab 1.1: Single LED Blink and Serial Output

## Learning Objectives
1. Understand how `setup()` runs once while `loop()` runs continuously.
2. Configure GPIO pins as outputs using `pinMode()`.
3. Control digital voltage levels (`HIGH` = 3.3V, `LOW` = 0V).
4. Establish Serial communication at `115200 baud` to log status to the host PC.

---

## Hardware Circuit and Pinout

| Component | Pin / Terminal | ESP32 Connection | Notes |
| :--- | :--- | :--- | :--- |
| **LED** | Anode (Long Leg +) | `GPIO 2` | Digital Output Pin |
| **Resistor (220 Ohm / 330 Ohm)** | One leg | Connected to LED Cathode (-) | Prevents excess current |
| **Resistor** | Other leg | `GND` | Ground rail on ESP32 |

```
  [ESP32 GPIO 2] --------(+) [LED] (-)-------- [220 Ohm Resistor] -------- [ESP32 GND]
```

---

## Step-by-Step Instructions
1. Assemble the circuit on the breadboard while the ESP32 is **unplugged**.
2. Connect the ESP32 to your PC with the USB cable.
3. Open `code.ino` in Arduino IDE.
4. Select `DOIT ESP32 DEVKIT V1` and your device's `COM Port`.
5. Click **Upload**. (Hold the `BOOT` button if upload gets stuck at `Connecting...`).
6. Open **Serial Monitor** (Top right magnifying glass or `Ctrl+Shift+M`) and set the baud rate dropdown to **115200 baud**.
7. Watch the LED flash and check the synchronized logs in the console.
