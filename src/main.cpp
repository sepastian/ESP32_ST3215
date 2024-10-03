/*
Control an ST3215 magnetic encoder servo via UART from an ESP32,
without using a dedicated controler board.
*/

#include <Arduino.h>
#include <SCServo.h>

// Pins for DOIT DevKit V1, adapt as required.
#define RX 16
#define TX 17
#define LED 2      // built-in LED
#define SERVO_ID 1 // default ID for new servos

SMS_STS st;

/*
Blink the ESP32 built-in LED for a certain number of times.
*/
void blink(int times, int on_ms, int off_ms)
{
  digitalWrite(LED, LOW);
  for (int i = 0; i < times; ++i)
  {
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

  st.WritePosEx(SERVO_ID, 0, 500, 100); // Rotate to position 0 at speed 500, acceleration 50 at start/stop.
  for (auto i = 0; i < 360; ++i)
  {
    st.WritePosEx(SERVO_ID, 4096 / 360 * i, 500, 100); // Step forward.
    delay(100);
  }
  delay(1000);
  blink(2, 100, 100);
}
