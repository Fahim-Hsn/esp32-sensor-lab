
# IR Obstacle/Proximity Sensor 

A simple, human-friendly guide to using a common **IR obstacle / proximity sensor** with an **ESP32**.  
This is the little board with an IR LED, IR receiver, a tiny trim pot (screw), and pins labeled **VCC**, **GND**, **DO** (digital out) and sometimes **AO** (analog out).

---

## What this does

- Detects when something is close in front of the sensor by bouncing infrared light off it.  
- Gives you a **digital signal** on `DO` when an object is within range (think: yes/no).  
- Many modules also expose **analog** `AO` that varies with distance (rough estimate, not precise).  
- You can **tune the range** using the small potentiometer on the board.

Typical detection range: **~2–30 cm**, but it depends on the surface (matte vs. glossy/black), angle, and ambient light.

---

## What you need

- **ESP32** dev board (DevKitC, WROOM, WROVER, etc.)
- **IR obstacle/proximity sensor module** (ideally 3.3–5 V compatible, LM393-style)
- **Jumper wires**
- **USB cable** (power/programming)

---

## Power & voltage (important)

- Prefer powering the sensor from **3.3 V** on the ESP32.  
- If your module **requires 5 V**, **do not** connect its `DO` directly to the ESP32 (5 V on a GPIO can damage it).  
  - Use a **level shifter** or a simple voltage divider (e.g., 10k + 20k) on `DO`.  
- Many popular LM393 modules happily run at **3.3–5 V**; check your specific board.

---

## Wiring (ESP32)

**Digital-only usage (recommended to start):**
- `VCC` → **3V3**
- `GND` → **GND**
- `DO`  → **GPIO 23** (or any free digital-capable pin)

**If your module also has `AO` (analog):**
- `AO` → one of the **ADC1** pins (e.g., **GPIO 34**, 35, 32, 33, 36, 39)  
  > Use **ADC1** pins; **ADC2** pins conflict with Wi-Fi on the ESP32.

> The small on-board LED usually toggles when an object is detected (some boards are active-low: LED ON = object detected).

---

## How it works (plain English)

The IR LED sends out invisible light. If an object is close, some of that light bounces back and hits the receiver.  
A tiny comparator compares that signal to a threshold (set by the trim pot). If it’s strong enough, it flips the **digital output**.

- **`DO` (digital):** “Object detected?” → **YES/NO**  
- **`AO` (analog):** “How strong is the reflection?” → a **voltage** you can read with `analogRead()` (rough distance clue)

---

## Quick start (no code here)

1. **Wire it** as shown above (start with `DO` to keep it simple).  
2. **Power the ESP32.** The sensor’s power LED should light.  
3. **Turn the trim pot** slowly while moving your hand in front of the sensor until the **DO LED** toggles at the distance you like.  
4. In your sketch, **read the `DO` pin** like a push-button:
   - If it reads as “object detected” when nothing is there, just **invert your logic** (some modules are active-low).  
5. (Optional) If using `AO`, read the value with `analogRead()` and observe how it changes with distance. Calibrate thresholds in software.

---

## Tips & troubleshooting

- **No detection at all**
  - Double-check **VCC/GND** (really).
  - Sweep the **trim pot** fully one way, then the other, while testing.
  - Try a **matte object** at ~5–10 cm; glossy/black can be tricky.

- **False triggers / flicker**
  - Strong **sunlight** or nearby **IR sources** (remotes, heaters) can confuse it.
  - Add a small **shroud** (tube/hood) around the sensor to block stray light.
  - In code, require a few **consecutive hits** before reacting (simple debounce/filter).

- **Analog reads look noisy on ESP32**
  - **Average** multiple samples.
  - Keep wires **short** and away from motors/relays.
  - Stick to **ADC1** pins (32–39). Avoid ADC2 when Wi-Fi is on.

- **Need accurate distance?**
  - These modules are best for **presence** detection.  
  - For real distance measurements, consider **Sharp IR** or **ToF (VL53L0X/53L1X)** sensors.

---

## Common use cases

- Obstacle avoidance for small robots  
- Simple “hand wave” triggers for menus/lights  
- Entry/exit counters (with careful placement & software filtering)  
- Line-following helpers (often paired with dedicated line sensors)

---

## Customize it

- Invert the logic if your module’s `DO` is **active-low**.  
- Use `AO` to set **soft thresholds** (e.g., “near”, “very near”).  
- Add **multiple sensors** (left/right/front) for better coverage.  
- Combine with a **buzzer** or **LED** to make a proximity alarm.

---

## License

Unless specified otherwise in this repo, treat this guide as **MIT-licensed**.  
Have fun building—keep it simple, keep it safe!
