# ESP32-S3 N16R8 CAM Module: PlatformIO Setup and Upload Guide

This document provides a comprehensive, step-by-step technical guide for configuring, building, uploading, and testing firmware on the **Freenove ESP32-S3 WROOM CAM** development board (N16R8 variant: 16 MB Flash, 8 MB Octal OPI PSRAM).

---

## 1. Hardware Specifications and Dual USB-C Architecture

The Freenove ESP32-S3 CAM board features two distinct USB Type-C ports. Understanding the difference between these ports is critical for reliable flashing and communication.

### Port Definitions

1. **UART Port (USB-to-UART Bridge):**
   - Connected to an onboard USB-to-UART bridge controller (such as CH340K or CP2102).
   - Connects to ESP32-S3 UART0 (GPIO 43 TX, GPIO 44 RX).
   - **Primary Use:** Firmware uploading, flashing, debugging, and viewing Serial Monitor output. This port is the recommended connection for flashing.

2. **USB Port (Native ESP32-S3 USB OTG):**
   - Connected directly to the ESP32-S3 native USB D- and D+ pins (GPIO 19 and GPIO 20).
   - **Primary Use:** Native USB CDC communication, USB UVC webcam mode, and direct high-speed data transfer.

### Camera Pin Mapping (Freenove ESP32-S3 CAM)

The camera interface uses a parallel DVP bus compatible with the `CAMERA_MODEL_ESP32S3_EYE` pinout definition:

| Signal Name | ESP32-S3 GPIO | Description |
| :--- | :--- | :--- |
| **PWDN** | -1 | Power down (tied internally or not connected) |
| **RESET** | -1 | Hardware reset (tied internally) |
| **XCLK** | GPIO 15 | External Master Clock |
| **SIOD (SDA)**| GPIO 4 | SCCB / I2C Data |
| **SIOC (SCL)**| GPIO 5 | SCCB / I2C Clock |
| **VSYNC** | GPIO 6 | Vertical Sync |
| **HREF** | GPIO 7 | Horizontal Reference |
| **PCLK** | GPIO 13 | Pixel Clock |
| **D0 (Y2)** | GPIO 11 | Data Bit 0 |
| **D1 (Y3)** | GPIO 9 | Data Bit 1 |
| **D2 (Y4)** | GPIO 8 | Data Bit 2 |
| **D3 (Y5)** | GPIO 10 | Data Bit 3 |
| **D4 (Y6)** | GPIO 12 | Data Bit 4 |
| **D5 (Y7)** | GPIO 18 | Data Bit 5 |
| **D6 (Y8)** | GPIO 17 | Data Bit 6 |
| **D7 (Y9)** | GPIO 16 | Data Bit 7 |
| **RGB LED** | GPIO 48 | Onboard WS2812 addressable LED |

Supported camera sensors include OmniVision OV2640 (2 MP), OV3660 (3 MP), and OV5640 (5 MP).

---

## 2. Development Environment Setup

### Step 2.1: Install Visual Studio Code
Download and install Visual Studio Code for Windows, macOS, or Linux from the official website:
https://code.visualstudio.com/

### Step 2.2: Install the PlatformIO IDE Extension
1. Open Visual Studio Code.
2. Click on the **Extensions** icon on the left sidebar (or press `Ctrl + Shift + X`).
3. Search for `PlatformIO IDE`.
4. Click **Install**.
5. Once installation completes, restart Visual Studio Code. An alien-head icon will appear on the left activity bar, indicating PlatformIO is active.

### Step 2.3: Install Windows USB-to-UART Drivers
If your computer does not automatically recognize the board when connected via the UART port:
- **CH340/CH341 Driver:** Download and install the WCH CH341SER driver from the manufacturer's website.
- **CP210x Driver:** Download and install the Silicon Labs CP210x Universal Windows Driver if your specific revision uses a CP2102 chip.

### Step 2.4: Verify Port Detection in Windows Device Manager
1. Connect a USB Type-C data cable between your computer and the **UART** port of the ESP32-S3 board.
2. Open Windows Device Manager (`Win + X` -> select **Device Manager**).
3. Expand the **Ports (COM & LPT)** section.
4. Verify that an entry such as `USB-SERIAL CH340 (COMx)` or `Silicon Labs CP210x USB to UART Bridge (COMx)` is present without any warning indicators. Note the assigned COM port number.

---

## 3. Project Structure

This workspace includes two distinct testing projects:

```text
cam module test/
|
|-- 01_wifi_ap_cam_server/
|   |-- platformio.ini
|   |-- partitions.csv
|   |-- src/
|       |-- camera_pins.h
|       |-- web_ui.h
|       |-- main.cpp
|
|-- 02_usb_type_c_streamer/
|   |-- platformio.ini
|   |-- partitions.csv
|   |-- src/
|   |   |-- camera_pins.h
|   |   |-- main.cpp
|   |-- web_viewer/
|       |-- index.html
|
|-- README.md
```

---

## 4. Project 1: Wi-Fi Access Point (SoftAP) Web Streaming

This project configures the ESP32-S3 as an independent Wi-Fi Access Point (`ESP32S3-CAM-AP`). No local network, Wi-Fi router, or internet connection is required. The device hosts a web server that delivers a responsive glassmorphism dashboard with live video streaming, snapshot capture, and image sensor adjustments.

### Key Configuration: `platformio.ini`
The configuration file specifies the exact parameters required for the ESP32-S3 N16R8 module:
- Microcontroller: `esp32s3` running at 240 MHz.
- Flash: 16 MB configured with `qio` mode.
- PSRAM: 8 MB Octal SPI (`opi`) enabled via `-DBOARD_HAS_PSRAM` and `board_build.arduino.memory_type = qio_opi`.
- Partition Scheme: Custom `partitions.csv` allocating 7 MB for each application slot to prevent size overruns.

### Build and Upload Instructions

#### Method A: Using the VS Code PlatformIO Interface
1. In VS Code, go to **File** -> **Open Folder...** and select:
   `c:\Users\Fahim Hossain\Desktop\projects\cam module test\01_wifi_ap_cam_server`
2. Connect your USB cable to the **UART** port on the board.
3. Look at the blue status bar at the bottom of VS Code:
   - Click the **PlatformIO: Build** checkmark icon to compile the code.
   - Click the **PlatformIO: Upload** right-arrow icon (`->`) to flash the firmware.
   - Click the **PlatformIO: Serial Monitor** plug icon to open the console at 115200 baud.

#### Method B: Using the PlatformIO Terminal (CLI)
1. Open the integrated terminal in VS Code (`Ctrl + ~`).
2. Navigate to the project directory:
   ```powershell
   cd "c:\Users\Fahim Hossain\Desktop\projects\cam module test\01_wifi_ap_cam_server"
   ```
3. Compile the firmware:
   ```powershell
   pio run
   ```
4. Upload the firmware to the connected board:
   ```powershell
   pio run -t upload
   ```
5. Open the serial monitor:
   ```powershell
   pio device monitor -b 115200
   ```

### Connecting to the Live Stream
1. Once upload completes, observe the serial output. The ESP32-S3 will initialize the camera, detect the sensor type (OV2640, OV3660, or OV5640), and launch the SoftAP.
2. On your computer, phone, or tablet, search for available Wi-Fi networks.
3. Connect to:
   - **SSID:** `ESP32S3-CAM-AP`
   - **Password:** *None (Open Network)*
4. Open any web browser (Google Chrome, Microsoft Edge, Mozilla Firefox, or Safari) and navigate to:
   ```text
   http://192.168.4.1
   ```
5. The web interface will load, displaying the live video feed along with controls for resolution, quality, brightness, contrast, vertical flip, and snapshot download.

---

## 5. Project 2: Direct USB Type-C Cable Streaming (Web Serial)

This project allows direct video streaming through the USB Type-C cable to a web browser, completely bypassing Wi-Fi.

### Operational Overview
The ESP32-S3 continuously streams MJPEG video frames over the USB Serial interface at 921,600 baud. The bundled web application (`web_viewer/index.html`) utilizes the browser's native Web Serial API to receive, synchronize, decode, and render the frames in real time.

### Build and Upload Instructions
1. In VS Code, go to **File** -> **Open Folder...** and select:
   `c:\Users\Fahim Hossain\Desktop\projects\cam module test\02_usb_type_c_streamer`
2. Connect the board via the **UART** port.
3. Click the **Upload** button in the bottom status bar (or execute `pio run -t upload` in the terminal).
4. After the firmware is written, disconnect the Serial Monitor in VS Code (the serial port must be free for the browser to open it).

### Launching the Web Serial Viewer
1. Open File Explorer and navigate to:
   `02_usb_type_c_streamer/web_viewer/index.html`
2. Right-click `index.html` and choose **Open with** -> **Google Chrome** or **Microsoft Edge** (browsers supporting the Web Serial API).
3. On the web page, click the **Connect Type-C ESP32** button.
4. A browser permissions dialog will appear listing available serial devices.
5. Select your ESP32-S3 COM port and click **Connect**.
6. The viewer will synchronize with the stream and render live video at up to 30 frames per second, complete with FPS and transfer rate indicators.

---

## 6. Manual Bootloader / Download Mode Procedure

Normally, the USB-to-UART bridge automatically pulses the DTR and RTS lines to enter download mode. If the uploader reports `A fatal error occurred: Failed to connect to ESP32-S3: No serial data received`, manually enter bootloader mode:

1. Locate the two push buttons on the board: **BOOT** (or `IO0`) and **RST** (or `EN`).
2. Press and hold down the **BOOT** button.
3. While continuing to hold the **BOOT** button, press and release the **RST** button once.
4. Release the **BOOT** button after 1 second.
5. The ESP32-S3 is now locked in ROM Download Mode.
6. Re-run the upload command (`pio run -t upload`).
7. Once flashing completes, press the **RST** button once to boot the newly flashed firmware.

---

## 7. Troubleshooting Guide

### 1. Camera Initialization Failure (`0x20003` or `Camera init failed`)
- **Root Cause:** The camera ribbon cable is loose, inserted backwards, or not properly locked into the connector.
- **Fix:** Locate the 24-pin FPC connector on the board. Carefully flip open the black retaining latch. Ensure the golden contacts of the camera ribbon cable face downward toward the PCB pins. Insert the cable fully and evenly, then push the black latch down until it snaps closed.

### 2. Port Busy or Access Denied (`could not open port 'COMx': PermissionError`)
- **Root Cause:** Another application currently has an exclusive lock on the serial port.
- **Fix:** Close the PlatformIO Serial Monitor in VS Code, close the Arduino IDE Serial Monitor, or disconnect any active Web Serial browser sessions before initiating a new upload.

### 3. ESP32 Brownout Reset (`Brownout detector was triggered`)
- **Root Cause:** Video streaming and Wi-Fi transmission cause instantaneous current spikes up to 400-500 mA. If the USB cable is thin or connected through an unpowered USB hub, the supply voltage drops below the 2.8 V threshold.
- **Fix:** Connect the board directly to a primary USB 3.0 port on your computer motherboard using a high-quality, short USB Type-C cable.

### 4. Blurry or Out-of-Focus Image
- **Root Cause:** The optical lens is set to a fixed focal distance that does not match your subject distance.
- **Fix:** The camera lens barrel is threaded. Gently rotate the outer lens bezel clockwise or counter-clockwise by hand until the image appears sharp.

### 5. PSRAM Not Detected
- **Root Cause:** Incorrect memory flags in `platformio.ini`.
- **Fix:** Confirm that `board_build.arduino.memory_type = qio_opi`, `board_build.psram_type = opi`, and `-DBOARD_HAS_PSRAM` are present in your `platformio.ini`. Without these settings, frame buffers for resolutions above VGA cannot be allocated.
