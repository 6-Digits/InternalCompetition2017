#include <Servo.h>
Servo whatever; //"call it whatever' -Jason

double distanceOne, distanceTwo; // These are the values from the ultrasonic sensors.
boolean colorCorrect, onWL, haveBlock; // Determines whether the color sensor detects the correct color and the infared
double memX = 0, derX, memY = 0, derY, enemyColorS, enemyColorE, ourColorS, ourColorE; //The derivative variables are for FULL Autonomous. The enemy color start and end range. The our color start and end range.
double speed;
double white;
long delay, turn, endZone; // How long it will take to then switch / change direction of motor and the amount of time it takes to turn
double safeDist, pitDist; //Safe distance from the pit.
const int ultraSonicOne, ultraSonicTwo, infared, servoOne, servoTwo, colorSensor, motorOne, motorTwo, radio;
boolean auton = false;

void setup() {
  Serial.begin(9600);  // put your setup code here, to run once:
  
  Serial.pinMode(ultraSonicOne, INPUT);
  Serial.pinMode(ultraSonicTwo, INPUT);
  Serial.pinMode(infared, INPUT);
  Serial.pinMode(servoOne, OUTPUT);
  Serial.pinMode(servoTwo, OUTPUT);
  Serial.pinMode(colorSensor, INPUT);
  Serial.pinMode(motorOne, OUTPUT);
  Serial.pinMode(motorTwo, OUTPUT);
  Serial.pinMode(radio, INPUT);
  
  eStop();
}

void loop() {
  checkInput();
  
  if (haveBlock && distanceOne < pitDist && distanceTwo < pitDist) {
    moveForward(speed); // speeds are different - determine after testing - Sam
    delay(endZone);
    moveBackward(speed);
    delay(endZone);
    haveBlock = false;
  } 
  else if (colorCorrect) {
    haveBlock = true;
    whiteLineFollower();
  } 
  else {
    blockBlock();
  }
}

void whiteLineFollower() {
  if (distance1 < safeDist && distance2 < safeDist) {               // White Line Follower + Turn at the end of the line (corner turns - Darren Kong)
    turnRight(speed);
    delay(turn);
  }
  else if (distance1 < safeDist && distance2 < safeDistance) {
    turnRight(speed);
    delay(turn * 2);
  } 
  else {
    moveForward(speed);
    checkWL(); // check white line
    delay(delay);
    if (onWL) {
      continue;
    } 
    else {
      moveBackwards(speed);
      delay(delay);
      turnRight(speed);
      delay(turn);
      moveForward(speed);
      delay(delay);
      checkWL();
      if (onWL) {
        continue;
      } 
      else {
        moveBackwards(speed);
        delay(delay);
        turnLeft(speed);
        delay(2 * turn);
        moveForward(speed);
        delay(delay);
        checkWL();
      }
    }
  }
}

void blockBlock(double speed) {
  moveForward(speed);
  delay(delay);
  closeServoMotor();
  turnRight(speed);
  delay(turn);
  moveForward(speed);
  delay(delay * 2);
  openServoOpen();
  moveBackward(speed);
  delay(delay * 2);
  turnLeft(speed);
  delay(turn);
  moveBackward(speed);
  delay(delay);
}

boolean checkWL() {
  if (analogRead(Infared_Sensor) < white) {
    onWhiteLine = false;
  }
  else {
    onWhiteLine = true;
  }
}

void checkInput() {
  int autoButton = Serial.read();

  if (autoButton = KEY_LEFT_CTRL) {
    !auton;
  }
  
  if (!auton) {
    if (UP_BUTTON) {
      Motor.moveForward(NUM);
    }
    if (DOWN_BUTTON) {
      Motor.moveBackward(NUM);
    }
    if (RIGHT_BUTTON) {
      Motor.turnRight(NUM);
    }
    if (LEFT_BUTTON) {
      Motor.turnLeft(NUM);
    }
    if (STOP_BUTTON) {
      Motor.eStop();
    }
  }
}

void moveForward(int speed){
   analogWrite(motorOne, speed);
   analogWrite(motorTwo, -1 * speed);
}
void moveBackward(int speed){
   analogWrite(motorOne, -1*speed);
   analogWrite(motorTwo, speed);
}
void turnRight(int speed){
   analogWrite(motorOne, speed);
   analogWrite(motorTwo, speed);
}

void turnLeft(int speed){
   analogWrite(motorOne, -1*speed);
   analogWrite(motorTwo, 1*speed);
}

void turn180() {
  
}

void eStop(){
   analogWrite(motorOne, 0);
   analogWrite(motorTwo, 0);
}
