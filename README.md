# Pedometer Using MPU6050 and ESP8266

An attempt at human activity recognition and a simple but effective solution to count the number of steps taken during the activity.

## Getting Started
### Setting Up and Flashing ESP8266

- Download the `esp8266` board package in arduino
- Add this to File->Preferences->Additional Boards managers URLs
```http://arduino.esp8266.com/stable/package_esp8266com_index.json ```
- Select NodeMCU 1.0(ESP-12E Module) and the corresponding port

We flash the ESP8266 with `ESP8266/imu.ino` from the Arduino IDE.

### Data Ingestion
- Verify that the ESP8266 is connected to the programmed hotspot.
```ip neigh```
This command gives us the ip addresses of all connected devices. Find the ip of the ESP8266.