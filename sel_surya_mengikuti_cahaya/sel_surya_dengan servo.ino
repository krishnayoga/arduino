#include <Servo.h> 

Servo myservo;

const int ldr1 = 12;
const int ldr2 = 11;
const int ldr3 = 10;
const int ldr4 = 9;
const int ldr5 = 8;

void setup() { 
  myservo.attach(7);
  Serial.begin(9600);

  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);
  pinMode(ldr3, INPUT);
  pinMode(ldr4, INPUT);
  pinMode(ldr5, INPUT);
} 

void loop() {
  int pinDig12 = digitalRead(ldr1);
  int pinDig11 = digitalRead(ldr2);
  int pinDig10 = digitalRead(ldr3);
  int pinDig9 = digitalRead(ldr4);
  int pinDig8 = digitalRead(ldr5);

  if(pinDig12 == LOW){
    myservo.write(60);
  }
  else if(pinDig11 == LOW){
    myservo.write(75);
  }
  else if(pinDig11 == LOW && pinDig12 == LOW){
    myservo.write(68);
  }
  else if(pinDig10 == LOW){
    myservo.write(90);
  }
  else if(pinDig10 == LOW && pinDig11 == LOW){
    myservo.write(83);
  }
  else if(pinDig9 == LOW){
    myservo.write(105);
  }
  else if(pinDig10 == LOW && pinDig9 == LOW){
    myservo.write(98);
  }
  else if(pinDig8 == LOW){
    myservo.write(120);
  }
  else if(pinDig8 == LOW && pinDig9 == LOW){
    myservo.write(113);
  }
  } 
