// Norm's Line Following Bot //
// Purpose deliver water to dorm rooms on predetermined route //

//Library
#include <AFMotor.h>

//Sensor pins
// A = Analog, D = Digital
#define rightA A0
#define rightD A1
#define leftA A3
#define leftD A4

//Motors
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

// Motor speed
int TurnSpeed = 150;
int MoveSpeed = 150;

void setup() {
  //Pin types
  pinMode(rightA,INPUT);
  pinMode(rightD,INPUT);
  pinMode(leftA,INPUT);
  pinMode(leftD,INPUT);
  //Begin communication with pins
  Serial.begin(9600);
}

void loop(){
  //Console logging
  Serial.print("Analog reading right = ");
  Serial.print(analogRead(rightA));
  Serial.print("\t Digital reading right = ");
  Serial.print(digitalRead(rightD));
  Serial.print("\t Analog reading left = ");
  Serial.print(analogRead(leftA));
  Serial.print("\t Digital reading left = ");
  Serial.print(digitalRead(leftD));
  Serial.print("\n");

  if(digitalRead(rightD)==0 && digitalRead(leftD)==0 && (analogRead(rightA) < 500 && analogRead(leftA) < 500)){
    // No line detected
    Go();
  }
  else if(!digitalRead(rightD)==0 && digitalRead(leftD)==0){
    // Line detected by right sensor
    TurnLeft();
  }
  else if(digitalRead(rightD)==0 && !digitalRead(leftD)==0){
    // Line detected by left sensor
    TurnRight();
  }
  else if(!digitalRead(rightD)==0 && !digitalRead(leftD)==0){
    // Line detected on both sensor
    Stop();
  }
}

void Go() {
  motor1.run(FORWARD);
  motor1.setSpeed(MoveSpeed);
  motor2.run(FORWARD);
  motor2.setSpeed(MoveSpeed);
  motor3.run(FORWARD);
  motor3.setSpeed(MoveSpeed);
  motor4.run(FORWARD);
  motor4.setSpeed(MoveSpeed);
}

void Stop() {
  motor1.run(RELEASE);
  motor1.setSpeed(0);
  motor2.run(RELEASE);
  motor2.setSpeed(0);
  motor3.run(RELEASE);
  motor3.setSpeed(0);
  motor4.run(RELEASE);
  motor4.setSpeed(0);
}

void TurnRight() {
  motor1.run(FORWARD);
  motor1.setSpeed(TurnSpeed);
  motor2.run(FORWARD);
  motor2.setSpeed(TurnSpeed);
  motor3.run(BACKWARD);
  motor3.setSpeed(TurnSpeed);
  motor4.run(BACKWARD);
  motor4.setSpeed(TurnSpeed);  
}

void TurnLeft() {
  motor1.run(BACKWARD);
  motor1.setSpeed(TurnSpeed);
  motor2.run(BACKWARD);
  motor2.setSpeed(TurnSpeed);
  motor3.run(FORWARD);
  motor3.setSpeed(TurnSpeed);
  motor4.run(FORWARD);
  motor4.setSpeed(TurnSpeed);
}
