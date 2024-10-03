Demonstrate how to control an ST3215 magnetic encoder servo via UART from an ESP32, without using a dedicated controler board, such as [this one](https://www.waveshare.com/wiki/Servo_Driver_with_ESP32).

# Hardware

Based on ["Secondary Development Tutorial"](https://www.waveshare.com/wiki/ST3215_Servo).

The ESP32 used is an "ESP32 DOIT DevKit V1", the ST3215 is from [Waveshare](https://www.waveshare.com/st3215-servo.htm).

# Software

The ST3215 Servo uses a half-duplex serial communication, baud rate 1000000. Make sure to set `monitor_speed` in `platform.ini` to that speed when debugging over serial.

# Wiring

On the ESP32, connect RX (pin 16) to TX (pin 17) using a 10 K resistor; then connect both to RX on the ST3215 (white).

Connect the ESP32 to 5V and GND, connect the ST3215 to 12V (red) and GND (black).

**Make sure to use common ground for the ESP32 and the ST3215!**

            .------------.
            | .--------. |                  .--------.
            | | ESP32  | |                  |        |=||
            | `--------' |                  | ST3215 |
            |            |                  |  Servo |
     5V ----| VIN  17 TX |-- 10K -----------| RX     |
    GND ----| GND  16 RX |--------'         |    PWR |---- 12V
            `------------'                  |    GND |---- GND
                                            `--------'
