# 🌤 DHT11 Weather Display with I²C LCD (ESP32)

This is a simple project that turns your ESP32 into a mini weather station.  
It reads the temperature and humidity from a DHT11 sensor and shows them on a 16×2 LCD with an I²C interface.

---

## 📺 What You’ll See
The LCD updates every few seconds:
1. A short message: **"Today's Weather..."**  
2. The current temperature in °C  
3. The current humidity in %  

It’s a quick way to check the room’s climate at a glance.

---

## 🛠 What You Need
- **ESP32 board** (e.g., ESP32 DevKit V1)  
- **DHT11 sensor** (temperature & humidity)  
- **16×2 LCD with I²C module** (PCF8574)  
- Jumper wires  
- USB cable to connect ESP32 to your computer  

---

## 🔌 Wiring

### DHT11 → ESP32
- **VCC** → 3.3V (or 5V)  
- **GND** → GND  
- **DATA** → GPIO **4**  

### LCD (I²C) → ESP32
- **VCC** → 5V  
- **GND** → GND  
- **SDA** → GPIO **21**  
- **SCL** → GPIO **22**  

> ESP32 SDA/SCL pins can be changed in code if needed.  
> If your LCD shows nothing, try a different I²C address (0x27 or 0x3F).

---

## 🚀 Getting Started

1. **Install Libraries** in Arduino IDE:  
   - `DHT sensor library` by Adafruit  
   - `LiquidCrystal_I2C` by Frank de Brabander (or similar)

2. **Open the Code** in Arduino IDE:  
   - Check that the DHT pin (GPIO 4) matches your wiring.  
   - Make sure the LCD I²C address (0x27) is correct for your module.  
   - Select your ESP32 board and COM port.  
   - Click **Upload**.

3. **See It Work**:  
   - The LCD will show `"Today's Weather..."` for a moment, then display temperature and humidity.  
   - It refreshes every few seconds.

---

## ⚙ How It Works
1. **Setup** – The ESP32 starts the LCD and DHT11 sensor.  
2. **Read Data** – The ESP32 asks the DHT11 for temperature and humidity.  
3. **Show on LCD** – First shows a welcome message, then the readings.  

---

## 🛠 Troubleshooting
- **Blank LCD** – Check wiring, try changing I²C address, or run an I²C scanner sketch.  
- **NaN Readings** – Check DHT11 wiring and ensure you’re using the correct library.  
- **Screen Flicker** – Reduce `lcd.clear()` calls or add longer delays.

---

## 💡 Ideas to Improve
- Use a **DHT22** for more accurate readings.  
- Add more sensors (light, pressure, etc.) and cycle them on the LCD.  
- Send data to a web page or app using ESP32’s Wi-Fi.  

---

## 📜 License
This project is under the **MIT License** – feel free to use, modify, and share.

