#include <Arduino.h>
#include <Servo.h>

#define JOYSTICK_X 14 //x
#define JOYSTICK_Y 15 //y
#define JOYSTICK_Z 16 //key

Servo servo_x; // 建立SERVO物件
Servo servo_y;
int pose_x = 90, pose_y = 90;
int pose_x_base = 87, pose_y_base = 97;
int buff = 0;
int gui_flag = 0, control_flag = 0, joy_flag = 0, input_z_flag = 0;
int gui_x, gui_y;
int joy_delay = 0;

void setup()
{
  servo_x.attach(8); // 設定要將伺服馬達接到哪一個PIN腳
  servo_y.attach(9);

  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(JOYSTICK_Z, INPUT);

  Serial.begin(115200); // bps
}

void loop()
{
  int input_x, input_y, input_z;

  /********************************************
   * serial
   * ****************************************/
  if (Serial.available() > 0)
  {
    while (1)
    {
      buff = Serial.read();
      // Serial.write(buff);
      // Serial.println(buff, DEC);
      if (buff == 71 && gui_flag == 0) //G
      {
        Serial.write(83); //S
        Serial.write(pose_x);
        Serial.write(pose_y);
        buff = 0;
        break;
      }
      else if (buff == 67 || gui_flag != 0) //C
      {
        gui_flag++;
        if (gui_flag == 2)
        {
          if (buff == 82) //real_82 virtual_86
          {
            control_flag = 0;
          }
          if (buff == 86)
          {
            control_flag = 1;
          }
          else if (buff != 86)
          {
            buff = 0;
            gui_flag = 0;
            break;
          }
        }
        else if (gui_flag == 3)
        {
          gui_x = buff;
          // Serial.println(gui_y, DEC);
        }
        else if (gui_flag == 4)
        {
          gui_y = buff;
          // Serial.println(gui_y, DEC);

          pose_x = map(gui_x, 100, 0, pose_x_base - 10, pose_x_base + 10);
          pose_y = map(gui_y, 100, 0, pose_y_base - 10, pose_y_base + 10);
          buff = 0;
          gui_flag = 0;
        }
        break;
      }
    }
  }

  /********************************************
  * joystick
  * ****************************************/
  if (control_flag == 0)
  {
    input_x = analogRead(JOYSTICK_X);
    input_y = analogRead(JOYSTICK_Y);
    input_z = digitalRead(JOYSTICK_Z);

    if (input_z == 1 && input_z_flag == 0)
    {
      input_z_flag = 1;
      if (joy_flag == 0)
      {
        joy_flag = 1;
      }
      else if (joy_flag == 1)
      {
        joy_flag = 0;
        pose_x_base = pose_x;
        pose_y_base = pose_y;
      }
    }
    else if (input_z == 0 && input_z_flag == 1)
    {
      input_z_flag = 0;
    }

    if (joy_flag == 0)
    {
      pose_x = map(input_x, 1, 1023, pose_x_base - 10, pose_x_base + 10);
      pose_y = map(input_y, 1023, 1, pose_y_base - 10, pose_y_base + 10);
    }
    else
    {
      if (joy_delay == 0)
      {
        if (input_x < 268)
          pose_x--;
        else if (input_x > 768)
          pose_x++;

        if (input_y < 268)
          pose_y++;
        else if (input_y > 768)
          pose_y--;
      }
      joy_delay++;
      if (joy_delay > 1000)
        joy_delay = 0;
    }
  }
  // Serial.println(joy_flag);

  /********************************************
   * servo
   * ****************************************/
  if (pose_x > 100)
    pose_x = 100;
  else if (pose_x < 80)
    pose_x = 80;

  if (pose_y > 100)
    pose_y = 100;
  else if (pose_y < 80)
    pose_y = 80;

  servo_x.write(pose_x); //旋轉到
  servo_y.write(pose_y); //旋轉到

  /********************************************
   * print on monitor
   * ****************************************/
  // Serial.print(input_x, DEC);
  // Serial.print(",");
  // Serial.print(input_y, DEC);
  // Serial.print(",");
  // Serial.print(input_z, DEC);
  // Serial.print(" ");
  // Serial.print(pose_x, DEC);
  // Serial.print(",");
  // Serial.println(pose_y, DEC);
}