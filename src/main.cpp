#include <Arduino.h>
#include <Servo.h> //載入函式庫，這是內建的，不用安裝

#define JOYSTICK_X 14 //x
#define JOYSTICK_Y 15 //y
#define JOYSTICK_Z 16 //key

Servo servo_x; // 建立SERVO物件
Servo servo_y;

void setup()
{
  servo_x.attach(9); // 設定要將伺服馬達接到哪一個PIN腳
  servo_y.attach(8);

  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(JOYSTICK_Z, INPUT);

  Serial.begin(115200); // bps
}

void loop()
{
  int input_x, input_y, input_z;
  input_x = analogRead(JOYSTICK_X);
  input_y = analogRead(JOYSTICK_Y);
  input_z = digitalRead(JOYSTICK_Z);

  int pose_x, pose_y;
  pose_y = map(input_x, 1, 1023, 80, 100);
  pose_x = map(1024-input_y, 1, 1023, 80, 100);
  servo_x.write(pose_x); //旋轉到
  servo_y.write(pose_y); //旋轉到

  Serial.print(input_x, DEC);
  Serial.print(",");
  Serial.print(input_y, DEC);
  Serial.print(",");
  Serial.print(input_z, DEC);
  Serial.print(" ");
  Serial.print(pose_x, DEC);
  Serial.print(",");
  Serial.println(pose_y, DEC);
}