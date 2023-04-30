# Pedometer Using MPU6050 and ESP8266

An attempt at human activity recognition and a simple but effective solution to count the number of steps taken during the activity using a ESP8266 and MPU6050.

## Getting Started
### Setting Up and Flashing ESP8266

- Download the `esp8266` board package in arduino
- Add this to File->Preferences->Additional Boards managers URLs
```http://arduino.esp8266.com/stable/package_esp8266com_index.json ```
- Select NodeMCU 1.0(ESP-12E Module) and the corresponding port

We flash the ESP8266 with `ESP8266/imu.ino` from the Arduino IDE.

## Directory Structure
### ESP8266
Code to be flashed on ESP8266.

### StepCount
For details and code to perform data acquisition, processing, step counting, and activity recognition.

### Enclosure Design
Contains the final enclosure design files