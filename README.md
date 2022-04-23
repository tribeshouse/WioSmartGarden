# Wio Terminal + Blynk Smart Garden

This is a demo project based on <https://github.com/lakshanthad/Wio_Terminal_Classroom_Arduino/blob/main/Classroom%2012/Smart_Garden/Smart_Garden.ino>, extended with Blynk.Cloud connection.

## Features

- Platform.IO setup including all needed libraries
- Measures temperature and humidity using Grove SHT31 sensor module
- Measures soil moisture using capacitive moisture sensor on A0
- Measures light level using built-in light sensor on the back of the Wio Terminal
- Connects to Blynk.Cloud and supplies measured values for temperature, humidity, soil moisture and light
- Automatic LCD backlight timeout of 10s, light turns back on when front button is pressed
- Over-the-Air-Updates are possible using Blynk.Cloud

## Caveats

- Capacitive soil moisture sensor takes about 20 minutes to calibrate before it reports consistent values
- Soil moisture sensor does not have meaningful values, but reports raw measured values
- Light can only be measured on the back of the module, won't work if back is covered
- Even with LCD timeout, battery pack will last only about 5 hours, use USB power for permanent usage
- TFT library and blynk will use too much memory when fully used at the same time. Sprite cannot be used, only basic tft functions are possible

## ToDo

- add value mapping for soil moisture sensor, once enough sample data has been collected
- add filter for first 20 minutes of moisture sensor, which are unreliable and not suitable for alerts
- make LCD timeout configurable
- add "Add water" alert back in (Display and Blynk)
