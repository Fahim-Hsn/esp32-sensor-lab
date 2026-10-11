# Lab 2.2: WaveDistance - Ultrasonic Range Finder & Reverse Parking Radar

## 🎯 Learning Objectives
1. Understand time-of-flight acoustic sensing using ultrasonic waves (40 kHz).
2. Measure microsecond pulse widths using `pulseIn()`.
3. Apply physics formulas in C++ to compute real-time metric distance.
4. Implement dynamic actuator feedback: frequency-modulated buzzer beeps (mimicking automotive reverse parking sensors).

---

## 🔌 Hardware Circuit & Pinout

| HC-SR04 Pin | ESP32 Pin | Function / Description |
| :--- | :--- | :--- |
| **VCC** | `5V` / `Vin` (or `3V3` for HC-SR04P) | Sensor Power |
| **GND** | `GND` | Ground reference |
| **TRIG** | `GPIO 5` | Trigger input from ESP32 |
| **ECHO** | `GPIO 18` | Echo output to ESP32 |
| **Buzzer Signal** | `GPIO 26` | Parking beep output |

> [!TIP]
> **Voltage Safety Note for Echo Pin:**
> Standard classic HC-SR04 runs on 5V and outputs a 5V Echo pulse. While most ESP32 dev boards tolerate transient pulses during lab testing, using a simple resistor voltage divider (e.g., 1kΩ + 2kΩ) on the ECHO pin or using a 3.3V-compatible HC-SR04+ / HC-SR04P module is ideal practice for hardware longevity.

---

## 📐 The Math Behind the Code
1. The ESP32 triggers a high pulse of $10\,\mu\text{s}$ on `TRIG_PIN`.
2. The transducer sends an 8-cycle sonic burst at $40\,\text{kHz}$.
3. When the reflected sound hits the receiver, `ECHO_PIN` goes `HIGH` for the duration of the round-trip travel time.
4. Using $v = 343\,\text{m/s} = 0.0343\,\text{cm/}\mu\text{s}$:
   $$\text{Distance} = \frac{\text{Duration} \times 0.0343}{2}$$
