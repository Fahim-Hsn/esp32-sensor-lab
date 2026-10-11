# Lab 2.1: Smart Proximity and Intruder Alert System

## Learning Objectives
1. Read digital signals from an active sensor module using `digitalRead()`.
2. Comprehend inverted logic: why IR sensors output `LOW` upon detecting obstacles.
3. Drive a 3-leg active buzzer module and coordinate multiple outputs based on input state.
4. Practice writing clean, responsive conditional branching in C++.

---

## Hardware Circuit and Pinout

| Module / Component | Pin Name / Leg | ESP32 Pin | Details |
| :--- | :--- | :--- | :--- |
| **IR Sensor Module** | `OUT` / `D0` | `GPIO 13` | Digital Input |
| | `VCC` | `3V3` or `Vin` | Power Supply |
| | `GND` | `GND` | Ground |
| **3-Leg Buzzer Module**| `S` / `I/O` (Signal) | `GPIO 26` | Digital Output control |
| | `+` (VCC) | `3V3` or `Vin` | Power Supply |
| | `-` (GND) | `GND` | Ground |
| **Red LED** | Anode (+) | `GPIO 14` | via 330 Ohm resistor to GND |
| **Green LED** | Anode (+) | `GPIO 27` | via 330 Ohm resistor to GND |

---

## Calibration Tip
- IR modules have a small blue potentiometer onboard.
- If the sensor always stays `LOW` or never triggers:
  1. Place your hand ~10cm in front of the IR diodes.
  2. Use a small screwdriver to turn the potentiometer until the onboard sensor indicator LED just triggers when your hand is present and turns off when removed.
