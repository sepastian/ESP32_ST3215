/*
Control an ST3215 magnetic encoder servo via UART from an ESP32,
without using a dedicated controler board, for example [1].

Based on "Secondary Development Tutorial" at [2].

The ESP32 used is an "ESP32 DOIT DevKit V1",
the ST3215 is from Waveshare [3].

The ST3215 Servo uses a half-duplex serial communication,
baud rate 1000000. Make sure to set `monitor_speed` in
`platform.ini` to that speed when debugging over serial.

Wiring:

          .------------.
          | .--------. |                  .--------.
          | | ESP32  | |                  |        |=||
          | `--------' |                  | ST3215 |
          |            |                  |  Servo |
   5V ----| VIN  17 TX |-- 10K -----------| RX     |
  GND ----| GND  16 RX |--------'         |    PWR |---- 12V
          `------------'                  |    GND |---- GND
                                          `--------'

[1] https://www.waveshare.com/wiki/Servo_Driver_with_ESP32.
[2] https://www.waveshare.com/wiki/ST3215_Servo
[3] https://www.waveshare.com/st3215-servo.htm
*/

#include <Arduino.h>
#include <SCServo.h>


#define RX 16
#define TX 17
#define LED 2
#define SERVO_ID 1 // default for new servos

SMS_STS st;

void blink(int times, int on_ms, int off_ms)
{
  digitalWrite(LED, LOW);
  for (int i = 0; i < times; ++i)
  {
    Serial.println(i);
    Serial.println(times);
    Serial.println(on_ms);
    Serial.println(off_ms);
    delay(off_ms);
    digitalWrite(LED, HIGH);
    delay(on_ms);
    digitalWrite(LED, LOW);
  }
}

void setup()
{
  Serial.begin(1000000);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, HIGH);
  Serial2.begin(1000000, SERIAL_8N1, RX, TX); // custom serial port
  st.pSerial = &Serial2;
  while (!Serial2)
  {
  }
  digitalWrite(LED, LOW);
}

void loop()
{
  blink(1, 100, 100);

  st.WritePosEx(1, 0, 500, 100); // Control the servo with ID 1 to rotate to the position of 1000 at a speed of 1500 and start and stop the acceleration of 50.
  for (auto i = 0; i < 360; ++i)
  {
    st.WritePosEx(1, 4096 / 360 * i, 500, 100); // Control the servo with ID 1 to rotate to the position 20 at a speed of 1500 and start and stop the acceleration at 50.
    delay(100);
  }
  delay(1000); //[(P1-P0)/V]*1000+100
  blink(2, 100, 100);
}
