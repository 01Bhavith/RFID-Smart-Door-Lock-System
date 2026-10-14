# 🚪 Smart Door System using RFID Authentication

An embedded IoT Level-1 access control system built with the Arduino Uno. This project provides localized, secure authentication using 13.56MHz RFID tags, actuates a physical door latch via a servo motor, and delivers real-time audio-visual feedback through an OLED display, LEDs, and a buzzer.

## 🚀 Features
*   **High-Speed Authentication:** Processes SPI data from the RC522 module to grant or deny access in under 500 milliseconds.
*   **Zero-Latency Offline Security:** Operates entirely on bare-metal firmware without reliance on cloud processing or internet connectivity.
*   **Electrical Isolation:** Utilizes a 4-channel bidirectional MOSFET logic level converter to safely interface the 3.3V sensor domain with the 5V microcontroller domain.
*   **Local UI Feedback:** 0.96" I2C OLED provides clear status instructions (Scan Card, Access Granted, Access Denied).

## 🛠️ Hardware Components
*   **Microcontroller:** Arduino Uno (ATmega328P)
*   **Sensor:** NXP MFRC522 RFID Module
*   **Actuator:** SG90 Micro Servo
*   **Display:** 0.96" SSD1306 OLED
*   **Safety:** 4-Channel Bidirectional Logic Level Converter
*   **Indicators:** Red/Green 5mm LEDs (w/ 220Ω resistors) and 5V Active Buzzer

## 🔌 Pin Mapping
| Component | Pin | Bus/Type | Notes |
| :--- | :--- | :--- | :--- |
| **RC522 SDA (SS)** | Pin 10 | SPI | Stepped down to 3.3V via Logic Converter |
| **RC522 SCK** | Pin 13 | SPI | Stepped down to 3.3V via Logic Converter |
| **RC522 MOSI** | Pin 11 | SPI | Stepped down to 3.3V via Logic Converter |
| **RC522 MISO** | Pin 12 | SPI | Direct connection (No converter needed) |
| **RC522 RST** | Pin 9 | Digital | |
| **OLED SDA** | Pin A4 | I2C | Direct I2C data line |
| **OLED SCL** | Pin A5 | I2C | Direct I2C clock line |
| **Servo Signal** | Pin 3 | PWM | Powered directly from 5V rail |

## 💻 Software Dependencies
Install the following libraries in your Arduino IDE before compiling:
*   `SPI.h` (Built-in)
*   `Wire.h` (Built-in)
*   `Servo.h` (Built-in)
*   [MFRC522](https://github.com/miguelbalboa/rfid) by GithubCommunity
*   [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library) by Adafruit
*   [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) by Adafruit

## 👥 Contribution

*   Bhavith V