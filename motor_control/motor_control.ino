#include <PS2X_lib.h> //controller ps2
#include <AFMotor.h> //l293shield

//AFMotor
AF_DCMotor motorh1(1, MOTOR12_64KHZ);  //kanan
AF_DCMotor motorh2(2, MOTOR12_64KHZ);  //kiri
AF_DCMotor motorv1(3, MOTOR12_64KHZ);  //atas
AF_DCMotor motorv2(4, MOTOR12_64KHZ);  //atas

//PS2X - Start
PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;
//PS2X - End

void setup() {
  //PS2X - Start
  Serial.begin(57600);
  error = ps2x.config_gamepad(13, 11, 10, 12, true, true); //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

  if (error == 0){
    Serial.println("Found Controller, configured successful");
  } 
  else if (error == 1){
    Serial.println("No controller found, check wiring");
  } 
  else if (error == 2){
    Serial.println("Controller found but not accepting commands");
  } 
  else if (error == 3){
    Serial.println("Controller refusing to enter Pressures mode");
  }

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
  }
  //PS2X - End
}

void loop() {
  //PS2X - Start
  if (error == 1) //skip loop if no controller found
    return;
  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    if ((ps2x.Analog(PSS_RY) < 64) && ((ps2x.Analog(PSS_RX) >= 64) && (ps2x.Analog(PSS_RX) <= 192))) {
      //maju
      Serial.println("Maju");
      motorh1.run(FORWARD);
      motorh1.setSpeed(255);
      motorh2.run(FORWARD);
      motorh2.setSpeed(255);
    }

    else if ((ps2x.Analog(PSS_RY) > 192) && ((ps2x.Analog(PSS_RX) >= 64) && (ps2x.Analog(PSS_RX) <= 192))) {
      //mundur
      Serial.println("Mundur");
      motorh1.run(BACKWARD);
      motorh1.setSpeed(255);
      motorh2.run(BACKWARD);
      motorh2.setSpeed(255);
    }

    else if ((ps2x.Analog(PSS_RX) < 64) && ((ps2x.Analog(PSS_RY) >= 64) && (ps2x.Analog(PSS_RY) <= 192))) {
      //kiri
      Serial.println("Kiri");
      motorh1.run(FORWARD);
      motorh1.setSpeed(255);
      motorh2.run(BACKWARD);
      motorh2.setSpeed(255);
    }

    else if ((ps2x.Analog(PSS_RX) > 192) && ((ps2x.Analog(PSS_RY) >= 64) && (ps2x.Analog(PSS_RY) <= 192))) {
      //kanan
      Serial.println("RIGHT");
      motorh1.run(BACKWARD);
      motorh1.setSpeed(255);
      motorh2.run(FORWARD);
      motorh2.setSpeed(255);
    }
    //naik turun
     else if ((ps2x.Analog(PSS_LY) > 64) && ((ps2x.Analog(PSS_LX) >= 64) && (ps2x.Analog(PSS_LX) <= 192))) {
      //naik
      Serial.println("Naik");
      motorh1.run(BACKWARD);
      motorh1.setSpeed(255);
      motorh2.run(BACKWARD);
      motorh2.setSpeed(255);
    }
    
    else if ((ps2x.Analog(PSS_LY) > 192) && ((ps2x.Analog(PSS_LX) >= 64) && (ps2x.Analog(PSS_LX) <= 192))) {
      //turun
      Serial.println("Turun");
      motorh1.run(FORWARD);
      motorh1.setSpeed(255);
      motorh2.run(FORWARD);
      motorh2.setSpeed(255);
    }

    else{
      //stopped
      Serial.println("MELAYANG");
      motorv1.run(BACKWARD);
      motorv1.setSpeed(100);
      motorv2.run(BACKWARD);
      motorv2.setSpeed(100);
    }
  }
}

