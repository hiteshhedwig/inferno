
#include <ros.h>
#include <auto_navi/try2.h>
#include "Arduino.h"

#define rpm_1 2
#define rpm_2 9
#define rpm_3 7
#define rpm_4 5
#define rpm_5 3
#define rpm_6 10

#define dir_1 43
#define dir_2 45
#define dir_3 48
#define dir_4 53
#define dir_5 49
#define dir_6 52

ros::NodeHandle nh;


void roverdrivesys( const auto_navi::try2& data){
  
int fr;
int bk;
fr=data.forward_speed;
bk=data.backward_speed;
lf= data.turning_left;
rg= data.turning_right;
  
  roverControl(fr,bk,lf,rg) ;
  
}

void roverControl(int fr, int bk, int lf, int rg) {
 
  if(fr>0&&bk==0&&lf==0&&rg==0)
  {
    digitalWrite(dir_1, LOW);
    digitalWrite(dir_2, HIGH);
    digitalWrite(dir_3, LOW);
    digitalWrite(dir_4, HIGH);
    digitalWrite(dir_5, LOW);
    digitalWrite(dir_6, HIGH);
    
    analogWrite(rpm_1, fr);
    analogWrite(rpm_2, fr);
    analogWrite(rpm_3, fr);
    analogWrite(rpm_4, fr);
    analogWrite(rpm_5, fr);
    analogWrite(rpm_6,fr);
  }
  if(fr==0&&bk>0&&lf==0&&rg==0)
  { 
    digitalWrite(dir_1, HIGH);
    digitalWrite(dir_2, LOW);
    digitalWrite(dir_3, HIGH);
    digitalWrite(dir_4, LOW);
    digitalWrite(dir_5, HIGH);
    digitalWrite(dir_6, LOW);
    
    analogWrite(rpm_1, bk);
    analogWrite(rpm_2, bk);
    analogWrite(rpm_3, bk);
    analogWrite(rpm_4, bk);
    analogWrite(rpm_5, bk);
    analogWrite(rpm_6, bk);
  }
  if(fr==0&&bk==0&&lf==0&&rg==0)
  { 
    digitalWrite(dir_1, HIGH);
    digitalWrite(dir_2, LOW);
    digitalWrite(dir_3, HIGH);
    digitalWrite(dir_4, LOW);
    digitalWrite(dir_5, HIGH);
    digitalWrite(dir_6, LOW);
    
    analogWrite(rpm_1, 0);
    analogWrite(rpm_2, 0);
    analogWrite(rpm_3, 0);
    analogWrite(rpm_4, 0);
    analogWrite(rpm_5, 0);
    analogWrite(rpm_6, 0);
  }

 if(fr==0&&bk==0&&lf>0&&rg==0)
 {
  //function calling code for turning left
 }

 if(fr==0&&bk==0&&lf==0&&rg>0)
 {
  //function calling code for turning right
 }
}

ros::Subscriber<auto_navi::try2> sub("rover_drive", &roverdrivesys );


void setup(){
    pinMode(rpm_1, OUTPUT);
    pinMode(rpm_2, OUTPUT);
    pinMode(rpm_3, OUTPUT);
    pinMode(rpm_4, OUTPUT);
    pinMode(rpm_5, OUTPUT);
    pinMode(rpm_6, OUTPUT);
    pinMode(dir_1, OUTPUT);
    pinMode(dir_2, OUTPUT);
    pinMode(dir_3, OUTPUT);
    pinMode(dir_4, OUTPUT);
    pinMode(dir_5, OUTPUT);
    pinMode(dir_6, OUTPUT);
    Serial.begin(9600);
    nh.initNode();
    nh.subscribe(sub);
    nh.loginfo("Program info");
  
}

void loop(){
      
      Serial.println("Starting Processes...");
      nh.spinOnce();
      
}
