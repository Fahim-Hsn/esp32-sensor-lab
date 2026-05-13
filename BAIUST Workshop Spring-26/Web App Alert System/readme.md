##  Hardware Configuration
The system uses specific GPIO pins on the ESP32 to manage sensors and actuators.

| Component | Pin (ESP32) | Function |
| :--- | :--- | :--- |
| **IR Sensor (OUT)** | GPIO 13 | Detects incoming objects/obstacles |
| **Red LED** | GPIO 14 | Alerts on object detection |
| **Green LED** | GPIO 27 | Indicates safe/clear status |
| **Active Buzzer** | GPIO 26 | Audible alert during detection |
| **Status LED** | GPIO 2 | Remote-controlled status light |
| **Power/Ground** | 3V3 / GND | System power supply |

##  Software Architecture
The project is built using a modern 3-tier architecture:
1.  **Firmware (ESP32):** Written in C++, handles sensor logic and HTTP communication.
2.  **Backend (Node.js):** An Express server that acts as the data hub and manages API endpoints.
3.  **Frontend (Web UI):** A JavaScript-powered dashboard that fetches and displays live telemetry.

##  Setup & Installation

### 1. Backend Setup
1.  Navigate to the project directory.
2.  Install dependencies:
    ```bash
    npm install
    npm install express cors
    ```
3.  Run the server:
    ```bash
    node server.js
