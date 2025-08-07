# I2C 16×2 LCD Text Printer for ESP32

A straightforward guide to hook up and use a 16×2 character LCD display with an ESP32 over I²C, so you can display messages with minimal fuss.

## Overview

This project shows you how to connect a common 16×2 LCD module (with PCF8574 I²C backpack) to an ESP32 board, configure the I²C bus, and send any text you like. You’ll only need a few wires and a library no complex wiring diagrams or bulky drivers.

## Key Features

- Uses ESP32’s built-in I²C interface on two pins  
- Four-wire connection: power, ground, SDA, SCL  
- Backlight on/off control and contrast adjustment  
- Cursor positioning on any of the two rows  
- Room for custom symbols if you want to get creative  

## What You Need

- ESP32 development board (e.g., DevKitC, WROOM, WROVER)  
- 16×2 LCD module with PCF8574 I²C backpack  
- Four jumper wires  
- USB cable for ESP32 power and programming  

## Wiring (ESP32 Default Pins)

- **VCC** → 5 V pin on ESP32  
- **GND** → GND pin on ESP32  
- **SDA** → GPIO 21 on ESP32  
- **SCL** → GPIO 22 on ESP32  

> **Tip:** If you’ve reassigned I²C pins in your setup, connect SDA and SCL accordingly.

## Setup Steps

1. Install an I²C LCD library in your Arduino or PlatformIO environment.  
2. Verify the LCD’s I²C address with a scanner sketch (common addresses are 0x27 or 0x3F).  
3. In your sketch, initialize the display using ESP32’s I²C interface.  
4. Send text strings, clear the screen, move the cursor, and toggle backlight as needed.

Once set up, you’ll be able to show status messages, sensor readings, menus and pretty much any text on your 16×2 display.

## Tips & Troubleshooting

- **Blank screen:** Turn the contrast potentiometer until characters appear.  
- **Wrong address:** Run an I²C scanner to discover the module’s address.  
- **Garbled text:** Double check that you declared a 16×2 display size in your code.  
- **No backlight control:** Some backpacks have the backlight permanently wired on; check the solder jumper if needed.

## Contributing

Suggestions, bug reports, and new feature ideas are very welcome. Feel free to fork this repo, add improvements or examples, and open a pull request.
