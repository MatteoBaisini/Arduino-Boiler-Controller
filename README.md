# Arduino Boiler Controller

This project is a smart dual-boiler temperature monitoring and control system built with Arduino. Designed for efficiency and reliability, it monitors the temperatures of two distinct boilers using DS18B20 1-Wire sensors and automates heating elements via relays.

## Key Features

- **Dual Boiler Monitoring:** Reads temperatures from two DS18B20 sensors via the 1-Wire protocol.
- **Automated Relay Control:** Actuates relays to control boilers based on temperature thresholds and hysteresis logic to prevent rapid switching.
- **LCD Interface with Auto-Backlight:** Features an I2C 16x2 LCD display that shows current temperatures and boiler status (using a custom arrow character). The LCD backlight automatically turns on in low-light conditions using a photoresistor.
- **LED Status Indicators:** Uses PWM-controlled LEDs with varying blink patterns to indicate different temperature ranges (e.g., solid for >70°C, fast blink for 50-70°C, slow blink for <50°C).
- **Serial Telemetry:** Outputs status codes and telemetry via Serial for debugging and monitoring.

## Hardware Requirements

- Arduino Board (e.g., Uno/Nano)
- 2x DS18B20 Temperature Sensors
- 16x2 I2C LCD Display
- 2x Relays (for Boiler and Caldaia control)
- Photoresistor (LDR) for ambient light sensing
- 2x LEDs (for status indication)
- Resistors and jumper wires

## Dependencies

Make sure to install the following libraries in your Arduino IDE:
- `OneWire.h`
- `DallasTemperature.h`
- `Wire.h`
- `LiquidCrystal_I2C.h`

## Code Overview

- `ONE_WIRE_BUS_1`, `ONE_WIRE_BUS_2`: Pins for the DS18B20 sensors.
- `RELAY_PIN_BOILER`, `RELAY_PIN_CALDAIA`: Pins to control the heating relays.
- `TEMPERATURE_TRIGGER_BOILER_1`, `HYSTERESIS`: Threshold parameters for automated temperature control.
- **Custom LCD Character:** A custom arrow `freccia` is defined to clearly indicate which relay is currently active on the LCD.

## Setup & Usage

1. Connect the hardware components according to the pin definitions in the code.
2. Upload the `23-08-26_---_programma_arduino_funzionante_DEFINITIVO.ino` file to your Arduino.
3. Open the Serial Monitor at `9600` baud to observe the initialization and running telemetry.
4. The system will start measuring temperatures and automatically control the boiler relays and indicator LEDs based on the predefined logic.

---
*Created by Matteo Baisini*
