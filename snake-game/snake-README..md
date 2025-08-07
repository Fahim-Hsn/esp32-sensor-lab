# Snake Game on 1.3" SSD1306 OLED

A simple Snake game running on an ESP32 with a 128×64 OLED display and five buttons.

## Overview

This project turns your ESP32 into a classic Snake game console. The snake moves around a bordered grid, eats food to grow, and the game ends if it runs into walls or itself. Use the UP, DOWN, LEFT, RIGHT buttons to steer, and RESET to start a new game.

## Hardware Required

- ESP32 development board  
- 1.3" SSD1306 I²C OLED display (128×64)  
- Five push-buttons or tactile switches  
- Breadboard and jumper wires  

## Wiring

| OLED Pin | ESP32 Pin    | Notes                     |
| -------- | ------------ | ------------------------- |
| VCC      | 3V3          | (or 5V if your display supports it) |
| GND      | GND          |                           |
| SDA      | GPIO 21      | ESP32 default SDA         |
| SCL      | GPIO 22      | ESP32 default SCL         |

| Button    | ESP32 Pin |
| --------- | --------- |
| UP        | GPIO 32   |
| DOWN      | GPIO 33   |
| LEFT      | GPIO 25   |
| RIGHT     | GPIO 26   |
| RESET     | GPIO 27   |

Buttons should be wired between the GPIO pin and ground, using the internal pull-ups.

## Setup & Installation

1. **Library Requirements**  
   - [U8g2](https://github.com/olikraus/u8g2) for OLED graphics  
   - Arduino-style environment with ESP32 board support  

2. **Load the Code**  
   - Copy the provided `snake.ino` (or `.cpp`) into your Arduino IDE or PlatformIO project.  
   - Select the correct ESP32 board and port.  
   - Upload to your ESP32.

3. **Start Playing**  
   - After reset, the game initializes automatically.  
   - Use the directional buttons to guide the snake.  
   - Press RESET to restart if you hit a wall or yourself.

## Gameplay

- **Objective:** Eat the food squares to grow longer.  
- **Controls:**  
  - UP, DOWN, LEFT, RIGHT — change snake direction  
  - RESET — restart the game  
- **Scoring:** Each food eaten increases your score by 1 and lengthens the snake.  
- **Game Over:** Collision with the border or your own tail ends the round.

## Tips & Troubleshooting

- If the display is blank, check I²C wiring and run an I²C scanner sketch to confirm the OLED address.  
- Adjust button wiring or debounce in software if inputs seem unreliable.  
- Feel free to tweak `moveDelay` in the code to make the game faster or slower.

## Contributing

Improvements, bug fixes, and feature ideas are welcome! Please fork the repo, make your changes, and open a Pull Request.

## License

This project is released under the MIT License. Feel free to use and modify it as you like.  
