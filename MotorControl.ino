
#include <ros.h>
#include <geometry_msgs/Point.h>

#include "Invkin.h"
#include "MotorPID.h"

float X ;
float Y ;
float Z ;
float x ;
float y ;
float z ;

ros::NodeHandle node;
geometry_msgs::Point msg;

Invkin IK(2,4,6);



MotorPID M1(3,22,A0);   // pwm , dir , potenio 
MotorPID M2(4,23,A1);
MotorPID M3(5,24,A2);



void roverCallBack(const geometry_msgs::Point& co_ordinates)
{  
    X =   co_ordinates.x ;
    Y =   co_ordinates.y ;  
    Z =   co_ordinates.z ;
    Serial.println(X);
    Motor_cont(X,Y,Z);
}

void Motor_cont(X,Y,Z)
{
  IK.transform();
  
  M1.x = IK.theta1;  // angle for motor 1 
  M2.x = IK.theta2;  // angle for motor 2
  M3.x = IK.theta3;  // angle for motor 3
  
  M1.errorcheck();
  M2.errorcheck();
  M3.errorcheck();


}
    
   



ros::Subscriber <geometry_msgs::Point> sub("co_ordinates", &roverCallBack);

void setup()
{
  Serial.begin(9600);  
  
  node.getHardware()->setBaud(115200);
  node.initNode();
  node.subscribe(sub);

  
  pinMode(A0,INPUT);
  pinMode(3,OUTPUT);
  pinMode(22,OUTPUT);
  
  pinMode(A1,INPUT);
  pinMode(4,OUTPUT);
  pinMode(23,OUTPUT);
  
  pinMode(A2,INPUT);
  pinMode(5,OUTPUT);
  pinMode(24,OUTPUT);
  
  M1.setPID(0.9,0.02,0.02);  //elbow
  M2.setPID(0.85,0.02,0.02); //shoulder
  M3.setPID(1.5,0.02,0.02);  //base

  
} 

void loop()
{

  node.spinOnce(); 
  delay(1);
}

