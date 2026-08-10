# ESP32 OTA Update Methods

This repository contains three different ways to perform Over-The-Air (OTA) firmware updates on ESP32:

1. ArduinoOTA (Classic Network Port method)
2. Web-based OTA (ESP32 hosts a webpage for uploading `.bin`)
3. Python Web Server OTA (ESP32 automatically pulls firmware from a Python server)



## Features

- Constant glowing internal LED (GPIO 2)
- Multiple OTA methods for different use cases
- Easy to use and beginner friendly
- Works with Arduino IDE and PlatformIO


## Hardware

1.ESP32 Development Board (e.g. DOIT ESP32 DEVKIT V1)
2.USB cable (only needed for the first upload)



# Method 1: ArduinoOTA (Network Port)

This is the classic method using the `ArduinoOTA` library. After the first USB upload, you can upload new code wirelessly from Arduino IDE.
# How to use

1.Upload once via USB.
2.Open Serial Monitor and note the IP address.
3.In Arduino IDE go to Tools → Port and select the network port (e.g. ESP32-LED at 192.168.x.x).
4.Upload new sketches wirelessly.

# Method 2: Web-based OTA (ESP32 Hosts Upload Page)
In this method, the ESP32 hosts a simple webpage. You open the IP in a browser and upload the .bin file directly.

# How to use

1.Upload the code via USB.
2.Open Serial Monitor and copy the IP address.
3.Open browser → go to http://ESP32_IP
4.Select the .bin file and click Upload Firmware.

# Method 3: Python Web Server OTA (Recommended for Automatic Updates)
In this method, you run a Python server on your computer. The ESP32 automatically downloads the .bin file and updates itself on every boot.

# How to use

1.Upload the ESP32 code once via USB.
2.Start the Python server.
3.Export new .bin file (Sketch → Export Compiled Binary).
4.Place the .bin file in the Python server folder.
5.Restart the ESP32 → it will automatically update.
