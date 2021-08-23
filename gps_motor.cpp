/*
  MLX90393 Magnetometer Example Code
  By: Nathan Seidle
  SparkFun Electronics
  Date: February 6th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
  Read the mag fields on three XYZ axis
  Hardware Connections (Breakoutboard to Arduino):
  3.3V = 3.3V
  GND = GND
  SDA = A4
  SCL = A5
  Serial.print it out at 9600 baud to serial monitor.
*/

#include <ros.h> //yiseul
#include <Wire.h>
#include <std_msgs/UInt16MultiArray.h> //yiseul
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <string.h>
#include <MLX90393.h> //From https://github.com/tedyapo/arduino-MLX90393 by Theodore Yapo
#include <Servo.h>
Servo servo_left;
Servo right;
Servo left;

MLX90393 mlx;
MLX90393::txyz data; //Create a structure, called data, of four floats (t, x, y, and z)
std_msgs::Float64 angle; //yiseul
std_msgs::UInt16MultiArray cmd_msg;
//ros::Publisher heading_angle("heading_angle", &angle); //yiseul
ros::NodeHandle  nh;
byte motor_left = 8;
byte motor_right = 10;

String str;
float del_lati;///
float del_longi;///

void messageLati(const std_msgs::UInt16MultiArray& cmd_msg)///
{
  Serial.println("msg.data"); ///
  del_lati = cmd_msg.data[0];///
   del_longi = cmd_msg.data[1];
}


ros::Subscriber <std_msgs::Float64> sub("gps_xy", messageLati);///

void setup()
{
  nh.initNode(); //yiseul
  Serial.begin(9600);
  Serial.println("MLX90393 Read Example");
  Wire.begin();
  //Connect to sensor with I2C address jumpers set: A1 = 1, A0 = 0
  //Use DRDY pin connected to A3
  //Returns byte containing status bytes
  byte status = mlx.begin();

  //Report status from configuration
  Serial.print("Start status: 0x");
  if(status < 0x10) Serial.print("0"); //Pretty output
  Serial.println(status, BIN);
  
  mlx.setGainSel(1);
  mlx.setResolution(0, 0, 0); //x, y, z
  mlx.setOverSampling(0);
  mlx.setDigitalFiltering(0);
  //See MLX90393.h and .cpp for additional functions including:
  //set/getOverSample, set/getTemperatureOverSample, set/getDigitalFiltering, set/getResolution
  //set/getTemperatureCompensation, setOffsets, setWThresholds
  left.attach(motor_left);
  right.attach(motor_right);

  left.writeMicroseconds(1500); // send "stop" signal to ESC.
  right.writeMicroseconds(1500); // send "stop" signal to ESC.

  nh.subscribe(sub);
  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop()
{
  String str;

  float way_x;
  float way_y;
  float difference = 1;
  float x;
  float y;
 // float h_angle; //yiseul
 // mlx.readData(data); //Read the values from the sensor
 // float x = float(data.x) + 30 ;
 // float y = float(data.y) + 35 ;
 // Serial.print("mag : \t ");
 // Serial.print(x); Serial.print("\t");
 // Serial.print(y);  Serial.print("\t");
 // float heading = atan2(y, x);
  //if(heading < 0)
 // heading += 2 * M_PI;
 // Serial.print("rotate_angle is: ");
  //delay(10);
 // str = "rotate_angle is" + String(rotate_angle, HEX);
 // Serial.println(str);

//  h_angle = heading; //yiseul
//  angle.data = h_angle; //yiseul
//  nh.advertise(heading_angle); //yiseul
  nh.spinOnce(); //yiseul
  
   //yujin
  int receive = 0; //yujin
//  int signal = heading;

 //  heading = heading * 180/M_PI;
  
 
    if (way_y - y && way_x - x) //first_Case
    {
      
      left.writeMicroseconds(1600); //
      right.writeMicroseconds(1520); //
     // Serial.println("Go_straight");
      
    }
    else if(way_y - y < 0 && way_x -x > 0) //second_case
    {
      left.writeMicroseconds(1520); //
      right.writeMicroseconds(1600); //
    //  Serial.println("Turn Right1");
      
    }
     else if(way_x - x < difference && way_y - y < difference) //second_case
    {
      left.writeMicroseconds(1600); //
      right.writeMicroseconds(1600); //
    //  Serial.println("Turn Right1");
     
    }
    
  delay(1000);
}