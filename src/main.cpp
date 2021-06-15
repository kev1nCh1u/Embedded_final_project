#include <Arduino.h>
#include <Servo.h> //載入函式庫，這是內建的，不用安裝

#define JOYSTICK_X 14 //x
#define JOYSTICK_Y 15 //y
#define JOYSTICK_Z 16 //key

Servo servo_x; // 建立SERVO物件
Servo servo_y;
int pose_x = 90, pose_y = 90;
int buff = 0, flag = 0;
int gui_x, gui_y;

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
  /********************************************
   * joystick
   * ****************************************/
  int input_x, input_y, input_z;
  input_x = analogRead(JOYSTICK_X);
  input_y = analogRead(JOYSTICK_Y);
  input_z = digitalRead(JOYSTICK_Z);
  // pose_y = map(input_x, 1, 1023, 80, 100);
  // pose_x = map(1024-input_y, 1, 1023, 80, 100);
  
  
  /********************************************
   * serial
   * ****************************************/
  while (1)
  {
    if (Serial.available() > 0) {
      if(buff == 0)
        buff = Serial.read();
      // Serial.write(buff);
      // Serial.println(buff, DEC);
      if(buff == 71){   //G
        Serial.write(83);   //S
        Serial.write(pose_x);
        Serial.write(pose_y);
        buff = 0;
        break;
      }
      else if(buff == 67 || flag != 0){    //C
        flag++;
        if(flag == 2)
          gui_x = Serial.read();
        else if(flag == 3){
          gui_y = Serial.read();

          // Serial.println(gui_y, DEC);
          
          pose_y = map(gui_x, 100, 0, 80, 100);
          pose_x = map(gui_y, 100, 0, 80, 100);
          buff = 0;
          flag = 0;
        }
        break;
      }
    }
  }

  /********************************************
   * servo
   * ****************************************/
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