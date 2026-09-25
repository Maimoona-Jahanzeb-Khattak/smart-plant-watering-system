# 🌱 Smart Plant Watering System

An automated plant watering system built with an ESP32, a soil moisture sensor, and a water pump. The system checks soil moisture at regular intervals and waters the plant automatically when the soil gets too dry — no manual watering needed.

## How It Works
1. A capacitive soil moisture sensor measures how wet or dry the soil is.
2. The ESP32 reads this value and compares it to a set "dry" threshold.
3. If the soil is too dry, the ESP32 activates a relay, which powers a small water pump for a few seconds.
4. This check repeats automatically (default: every hour).

## Components
| Component | Purpose |
|---|---|
| ESP32 (or Arduino Uno) | Microcontroller running the logic |
| Capacitive soil moisture sensor | Measures soil water content |
| 5V relay module | Switches the pump on/off |
| Small submersible water pump | Delivers water to the plant |
| Jumper wires + breadboard | Wiring |
| LED (optional) | Lights up while watering |

## Wiring
| Sensor/Module | ESP32 Pin |
|---|---|
| Soil Moisture Sensor (Signal) | GPIO 34 (analog input) |
| Relay Module (IN) | GPIO 26 |
| Onboard LED | GPIO 2 |
| VCC (sensor & relay) | 3.3V / 5V (check module spec) |
| GND | GND |


## Setup Instructions
1. Wire the components as shown above.
2. Open `smart_plant_watering.ino` in the Arduino IDE.
3. Install the ESP32 board package (Tools → Board → Boards Manager → search "ESP32").
4. Select your board and COM port under Tools.
5. Upload the sketch.
6. Open the Serial Monitor (115200 baud) to see moisture readings and watering status.
7. Calibrate `DRY_THRESHOLD` in the code: dip the sensor in dry soil and wet soil, note the readings, and set the threshold between them.

## Possible Improvements
- Add an OLED/LCD screen to show live moisture % without a computer.
- Send watering alerts to a phone via Wi-Fi (e.g., using Blynk or a Telegram bot).
- Log moisture history to a file or cloud database for tracking plant health over time.
- Add a water-level sensor in the reservoir so the pump doesn't run dry.
- Support multiple plants/sensors with individual thresholds.
