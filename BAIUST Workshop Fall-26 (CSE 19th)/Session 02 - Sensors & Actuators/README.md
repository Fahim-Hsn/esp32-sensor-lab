# Session 02: Sensors & Actuators (IR, Ultrasonic & Buzzer)
**Target Batch:** CSE 19th Batch, BAIUST  
**Duration:** 2 Hours (120 Minutes)  
**Prerequisites:** Session 01 completion, understanding `pinMode`, `digitalWrite`, basic C++ `if-else` conditionals

---

## ⏱️ Session Agenda (120 Minutes)

| Time | Duration | Segment | Key Topics / Actions |
| :--- | :--- | :--- | :--- |
| **00:00 - 00:20** | 20 mins | **Theory: Digital Inputs & Logic Levels** | Digital Read concepts, Active LOW sensor logic (why IR module output drops to 0V upon detection) |
| **00:20 - 00:35** | 15 mins | **Actuators: 3-Leg Buzzer Module** | Pinout (VCC, GND, Signal), Active vs Passive buzzers, tone generation vs digital toggle |
| **00:35 - 01:10** | 35 mins | **Hands-on Lab 1: Smart Proximity Alarm** | Interfacing IR Obstacle Sensor + Buzzer + Status LEDs (Safe vs Alarm state machine) |
| **01:10 - 01:25** | 15 mins | **Theory: Ultrasonic Physics** | HC-SR04 Trigger/Echo timing, Speed of sound formula, pulse duration measurement with `pulseIn()` |
| **01:25 - 01:55** | 30 mins | **Hands-on Lab 2: WaveDistance Parking Radar** | Distance measurement in cm, serial telemetry, proportional buzzer beeping frequency |
| **01:55 - 02:00** | 5 mins | **Wrap-up & Preview of Session 3** | Analog inputs (ADC), MQ gas sensor, connecting ESP32 to WiFi |

---

## 🔬 Core Engineering Concepts

### 1. Active LOW Logic (IR Sensor Module)
- Most commercial IR obstacle modules use an LM393 comparator with active-LOW output:
  - **No Obstacle Detected:** Output pin is `HIGH` (3.3V).
  - **Obstacle Detected:** Output pin is `LOW` (0V), and onboard indicator LED illuminates.
- **In C++:**
  ```cpp
  int sensorState = digitalRead(IR_PIN);
  if (sensorState == LOW) {
      // Obstacle present! Trigger alarm
  }
  ```

### 2. 3-Leg Buzzer Module Pinout
- Usually labeled as:
  - `-` or `GND` -> Connect to ESP32 `GND`
  - `+` or `VCC` -> Connect to `3V3` (or `Vin`/5V)
  - `S` or `I/O` (Signal) -> Connect to ESP32 GPIO pin

### 3. Ultrasonic Distance Calculation (HC-SR04)
- **Physics:** Sound travels at approximately $343\text{ m/s}$ in dry air at 20°C, which is $0.0343\text{ cm/}\mu\text{s}$.
- The sound pulse travels to the obstacle and bounces back (double distance):
  $$\text{Distance (cm)} = \frac{\text{Duration in microseconds} \times 0.0343}{2}$$

---

## 🚀 Hands-on Projects in this Session

1. **[01_Smart_Proximity_IR_Buzzer](./01_Smart_Proximity_IR_Buzzer/):**
   - Autonomous security barrier detecting obstacles within range.
   - Triggers red LED alert and buzzer alarm while shutting off green safe indicator.
2. **[02_WaveDistance_HC_SR04](./02_WaveDistance_HC_SR04/):**
   - Precise distance measuring station.
   - Dynamic alert intervals: beeps faster as objects get closer (automotive reverse parking assist).
