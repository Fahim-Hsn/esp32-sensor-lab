# Lab 1.2: Traffic Light Controller and PWM Fading

## Learning Objectives
1. Control multiple GPIO output lines simultaneously.
2. Structure procedural states representing real-world state machines.
3. Understand **Pulse Width Modulation (PWM)**: Simulating analog output (variable brightness/voltage) using digital switching with duty cycles (0 to 255).

---

## Hardware Circuit and Pinout

| Component | Pin / Leg | ESP32 Pin | Current Resistor |
| :--- | :--- | :--- | :--- |
| **Red LED** | Anode (+) | `GPIO 25` | 220 Ohm / 330 Ohm to GND |
| **Yellow LED** | Anode (+) | `GPIO 26` | 220 Ohm / 330 Ohm to GND |
| **Green LED** | Anode (+) | `GPIO 27` | 220 Ohm / 330 Ohm to GND |
| **Common GND** | All Cathodes (-) | `GND` rail | Connected to ESP32 `GND` |

---

## Concept: How PWM Works on ESP32
Since digital pins can only output 0V or 3.3V, we cannot directly output e.g. 1.65V. Instead, PWM turns the pin HIGH and LOW thousands of times per second:
- **0% Duty Cycle (0):** Always LOW (0V) - LED completely OFF
- **50% Duty Cycle (128):** HIGH half the time - LED glows at 50% perceived brightness
- **100% Duty Cycle (255):** Always HIGH (3.3V) - LED at full brightness
