#include <Servo.h>

// Instanciations of Servo objects
Servo servo1;
Servo servo2;

// These are the values from the ultrasonic sensors.
//double distanceOne, distanceTwo; 

// Determines whether the color sensor detects the correct color and the infared
//boolean colorCorrect, onWL, haveBlock; 

// The derivative variables are for FULL Autonomous. The enemy color start and end range. The our color start and end range.
//double memX = 0, derX, memY = 0, derY, enemyColorS, enemyColorE, ourColorS, ourColorE; 
//Suicide Code
int speed = 100;
//double white;
// How long it will take to then switch / change direction of motor and the amount of time it takes to turn
//long delay, turn, endZone;

// Safe distance from the pit. 
//double safeDist, pitDist; 

//const int ultraSonicOne, ultraSonicTwo, infared, colorSensor, radio;
const int M1F= 5;
const int M1B = 6;
const int M2F = 7;
const int M2B = 8;

boolean auton = false;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(10);
  servo2.attach(11);
  Serial.begin(9600);  
 
  /*Serial.pinMode(ultraSonicOne, INPUT);
  Serial.pinMode(ultraSonicTwo, INPUT);
  Serial.pinMode(infared, INPUT); 
  Serial.pinMode(colorSensor, INPUT);*/
  pinMode(M1F, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2F, OUTPUT);
  pinMode(M2B, OUTPUT);
  //Serial.pinMode(radio, INPUT);
  
  eStop();
}

void loop() {
  checkInput();
  
  /*if (haveBlock && distanceOne < pitDist && distanceTwo < pitDist) {
    // speeds are different - determine after testing - Sam
    moveForward(speed); 
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
  }*/
}

/*void whiteLineFollower() {
  // White Line Follower + Turn at the end of the line (corner turns - Darren Kong)
  if (distance1 < safeDist && distance2 < safeDist) {
    turnRight(speed);
    delay(turn);
  }
  else if (distance1 < safeDist && distance2 < safeDistance) {
    turnRight(speed);
    delay(turn * 2);
  } 
  else {
    moveForward(speed);
    // check white line
    checkWL(); 
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
}*/

void checkInput() {
  char autoButton = Serial.read();
  /*if (Serial.available() > 0) {
    autoButton = Serial.read();
  }*/

  if (autoButton == 'm') {
    auton = !auton;
    if (auton) {
      Serial.println("Autonomous mode activated");
    }
    else {
      Serial.println("Autonomous mode deactivated");
    }
    Serial.println(autoButton);
  }
  
  if (!auton) {
    if (autoButton == 'w') {
      Serial.println(autoButton);
      moveForward(speed);
    }
    if (autoButton == 's') {
      Serial.println(autoButton);
      moveBackward(speed);
    }
    if (autoButton == 'd') {
      Serial.println(autoButton);
      turnRight(speed);
    }
    if (autoButton == 'a') {
      Serial.println(autoButton);
      turnLeft(speed);
    }
    if (autoButton == 'n') {
      Serial.println(autoButton);
      eStop();
    }
    if (autoButton == 'o') {
      Serial.println(autoButton);
      openServo();
    }
    if (autoButton == 'p') {
      Serial.println(autoButton);
      closeServo();
    }
  }
}

void moveForward(int speed){
   analogWrite(M1F, speed);
   analogWrite(M1B, 0);
   analogWrite(M2F, speed); 
   analogWrite(M2B, 0);
   Serial.println("Moving Forward");
}
void moveBackward(int speed){
   analogWrite(M1F, 0); 
   analogWrite(M1B, speed);
   analogWrite(M2F, 0);
   analogWrite(M2B, speed);
   Serial.println("Moving Backward");
}
void turnRight(int speed){
   analogWrite(M1F, speed);
   analogWrite(M1B, 0);
   analogWrite(M2F, 0);
   analogWrite(M2B, speed);
   Serial.println("Moving Right");
}

void turnLeft(int speed){
   analogWrite(M1F, 0);
   analogWrite(M1B, speed);
   analogWrite(M2F, speed);
   analogWrite(M2B, 0);
   Serial.println("Moving Left");
}

void turn180() {
  
}

void eStop(){
   analogWrite(M1F, 0);
   analogWrite(M1B, 0);
   analogWrite(M2F, 0);
   analogWrite(M2B, 0);
   Serial.println("Stopped");
}

void openServo() {
  /*for (int i = 0, j = 90; i < 90 && j > 90; i++, j--) {
    servo1.write(i);
    servo2.write(j);
    delay(2);
  }*/
  Serial.println("Opening Servo");
  servo1.write(90);
  servo2.write(15);
  Serial.println("Serial Opened"); 
}

void closeServo() {
  /*for (int i = 0, j = 90; i < 90 && j > 90; i++, j--) {
    servo1.write(j);
    servo2.write(i);
    delay(2);
  }*/
  Serial.println("Closing Servo");
  servo1.write(15);
  servo2.write(90);
  Serial.println("Serial Closed");
}

