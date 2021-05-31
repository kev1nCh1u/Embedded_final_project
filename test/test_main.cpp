#include <Arduino.h>

int JoyStick_X = 14; //x

int JoyStick_Y = 15; //y

int JoyStick_Z = 16; //key

void setup()
{
  pinMode(JoyStick_X, INPUT);

  pinMode(JoyStick_Y, INPUT);

  pinMode(JoyStick_Z, INPUT);

  Serial.begin(9600); // 9600 bps
}

void loop()
{

  int x, y, z;
  x = analogRead(JoyStick_X);
  y = analogRead(JoyStick_Y);
  z = digitalRead(JoyStick_Z);

  Serial.print(x, DEC);
  Serial.print(",");

  Serial.print(y, DEC);
  Serial.print(",");

  Serial.println(z, DEC);
}