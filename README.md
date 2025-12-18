# XIAO_W5500_Ethernet_Adapter

## Overview

This repository provides three example projects demonstrating how to use the Seeed Studio XIAO series microcontroller with the W5500 Ethernet module. These examples cover basic Ethernet connectivity, running a web server, and streaming video from a camera module over Ethernet.

## Hardware Requirements

- Seeed Studio XIAO (e.g., XIAO ESP32S3)
- W5500 Ethernet module
- Ethernet cable
- Jumper wires
- Breadboard (optional)
- (For camera example) Camera module compatible with XIAO ESP32S3

### W5500 Ethernet Module Wiring (default in all examples)
- **ETH_PHY_CS**: D1
- **ETH_SPI_SCK**: D8
- **ETH_SPI_MISO**: D9
- **ETH_SPI_MOSI**: D10
- **ETH_INTn**: D16

### Camera Module Wiring (for XIAO ESP32S3)
See `XIAO_PoE_CameraWebServer/camera_pins.h` for full pin mapping. Default mapping for XIAO ESP32S3:
- PWDN_GPIO_NUM: -1
- RESET_GPIO_NUM: -1
- XCLK_GPIO_NUM: 10
- SIOD_GPIO_NUM: 40
- SIOC_GPIO_NUM: 39
- Y9_GPIO_NUM: 48
- Y8_GPIO_NUM: 11
- Y7_GPIO_NUM: 12
- Y6_GPIO_NUM: 14
- Y5_GPIO_NUM: 16
- Y4_GPIO_NUM: 18
- Y3_GPIO_NUM: 17
- Y2_GPIO_NUM: 15
- VSYNC_GPIO_NUM: 38
- HREF_GPIO_NUM: 47
- PCLK_GPIO_NUM: 13

---

## Example Projects

### 1. XIAO_PoE_Ethernet_Test
A simple test sketch that logs Ethernet events, MAC address, and IP address to the serial console. It can also make a test HTTP request to a server (default: baidu.com).

**How to use:**
1. Wire the W5500 module to your XIAO as described above.
2. Open `XIAO_PoE_Ethernet_Test/XIAO_PoE_Ethernet_Test.ino` in Arduino IDE or PlatformIO.
3. Upload to your XIAO board.
4. Open the serial monitor at 115200 baud to view Ethernet status and IP address.

---

### 2. XIAO_PoE_Ethernet_WebServer
Implements a simple web server over Ethernet. After uploading, the board will print its IP address to the serial monitor. Access this IP in your browser to see a greeting message. The `/inline` endpoint is also supported.

**How to use:**
1. Wire the W5500 module to your XIAO as described above.
2. Open `XIAO_PoE_Ethernet_WebServer/XIAO_PoE_Ethernet_WebServer.ino` in Arduino IDE or PlatformIO.
3. Upload to your XIAO board.
4. Open the serial monitor at 115200 baud to find the assigned IP address.
5. Enter the IP address in your browser to access the web server.

---

### 3. XIAO_PoE_CameraWebServer
Streams video from a camera module over Ethernet. After uploading, the board will print its IP address to the serial monitor. Access this IP in your browser to view the camera stream.

**How to use:**
1. Wire the W5500 module and camera module to your XIAO as described above.
2. Open `XIAO_PoE_CameraWebServer/XIAO_PoE_CameraWebServer.ino` in Arduino IDE or PlatformIO.
3. Upload to your XIAO board.
4. Open the serial monitor at 115200 baud to find the assigned IP address.
5. Enter the IP address in your browser to view the camera stream.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments
- Seeed Studio for the XIAO microcontroller series
- WIZnet for the W5500 Ethernet module
