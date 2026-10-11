# BAIUST Workshop Fall-26 (CSE 19th Batch)
## Embedded Systems & IoT Engineering: From Silicon to Full-Stack Web

Welcome to the official curriculum repository for the **CSE 19th Batch IoT & Embedded Systems Workshop** at **BAIUST**.

---

## 🎯 Target Audience & Pedagogical Philosophy
- **Students' Background:** Strong foundation in **C++** programming, but starting from **zero level in electronics, breadboarding, and microcontrollers**.
- **Pedagogy:** Leveraging their existing C++ concepts (variables, conditionals, loops, functions, memory awareness) to explain physical computing, while teaching electronics safely step-by-step.
- **Structure:** 5 Sessions | 2 Hours per Session (Theory + Interactive Hands-on Lab).

---

## 🗺️ Master 5-Session Roadmap

| Session | Phase | Core Topics | Hands-on Deliverables |
| :--- | :--- | :--- | :--- |
| **Session 01** | **Basics** | ESP32 Architecture, Breadboard Basics, Digital Output, PWM & Serial Debugging | Single LED Blink & Multi-LED Traffic Light System |
| **Session 02** | **Basics** | Digital/Analog Input Theory, IR Obstacle Sensor, Ultrasonic Ranging, 3-Leg Buzzer | Smart Proximity Alarm & WaveDistance Parking Radar |
| **Session 03** | **Intermediate** | MQ Gas Sensor (Analog ADC), Calibration, ESP32 WiFi STA/AP, HTTP Client & REST | Environmental Gas & Safety Node sending data over WiFi |
| **Session 04** | **Advanced** | Backend Architecture (Node.js & Express), WebSockets / REST API, Live Ingestion | Local Server receiving telemetry from ESP32 |
| **Session 05** | **Capstone** | Full-Stack IoT Web Dashboard, Real-time Visualizations, Bidirectional Control | Complete End-to-End IoT Web App Alert & Monitoring System |

---

## 📂 Active Sessions (Basics Phase)

### 📌 [Session 01: ESP32 Onboarding & Digital I/O](./Session%2001%20-%20ESP32%20Onboarding%20%26%20Digital%20IO/README.md)
*Duration: 2 Hours (45m Theory/Setup + 75m Hands-on Lab)*
- **Theory:** Microcontroller vs Microprocessor, ESP32 Pinout (3.3V logic level caution), Breadboard internal bus connections, avoiding short circuits.
- **Hands-on 1:** [01_LED_Blink](./Session%2001%20-%20ESP32%20Onboarding%20%26%20Digital%20IO/01_LED_Blink) — GPIO output control, current-limiting resistors, understanding `pinMode`, `digitalWrite`, `delay`.
- **Hands-on 2:** [02_Traffic_Light_PWM](./Session%2001%20-%20ESP32%20Onboarding%20%26%20Digital%20IO/02_Traffic_Light_PWM) — State machine traffic signal & LED brightness fading using ESP32 PWM (`ledcWrite`).

### 📌 [Session 02: Sensors & Actuators](./Session%2002%20-%20Sensors%20%26%20Actuators/README.md)
*Duration: 2 Hours (40m Theory + 80m Hands-on Lab)*
- **Theory:** Digital Inputs vs Outputs, Active LOW / Active HIGH logic, Speed of sound formula, ultrasonic echo pulse timing, active vs passive buzzers.
- **Hands-on 1:** [01_Smart_Proximity_IR_Buzzer](./Session%2002%20-%20Sensors%20%26%20Actuators/01_Smart_Proximity_IR_Buzzer) — IR obstacle detection with 3-leg buzzer tone/frequency alerts and LED indicators.
- **Hands-on 2:** [02_WaveDistance_HC_SR04](./Session%2002%20-%20Sensors%20%26%20Actuators/02_WaveDistance_HC_SR04) — Distance measurement in centimeters using HC-SR04 with threshold alert and Serial Monitor telemetry.

---

## 🧰 Required Hardware Inventory for Sessions 1 & 2
1. **ESP32 DevKit V1** (30-pin or 38-pin) + Micro-USB / Type-C Data Cable
2. **Half-size or Full-size Breadboard**
3. **LEDs** (Red, Yellow, Green)
4. **Resistors** (220Ω / 330Ω)
5. **IR Obstacle Avoidance Sensor Module**
6. **HC-SR04 Ultrasonic Sensor Module**
7. **3-Leg Buzzer Module** (VCC, GND, I/O)
8. **Jumper Wires** (Male-to-Male, Male-to-Female)
