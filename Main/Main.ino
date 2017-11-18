#include <Servo.h>

// Instanciations of Servo objects
Servo servo1;
Servo servo2;

// These are the values from the ultrasonic sensors.
double distanceOne, distanceTwo; 

// Determines whether the color sensor detects the correct color and the infared
boolean colorCorrect, onBL, haveBlock; 

// The derivative variables are for FULL Autonomous. The enemy color start and end range. The our color start and end range.
//double memX = 0, derX, memY = 0, derY, enemyColorS, enemyColorE, ourColorS, ourColorE; 
//Suicide Code
int speed = 100;
double black;
// How long it will take to then switch / change direction of motor and the amount of time it takes to turn
long turn, endZone, delays;

// Safe distance from the pit. 
double safeDist, pitDist; 

const int infared = 3; 
//colorSensor, radio;
const int M1F= 5;
const int M1B = 6;
const int M2F = 7;
const int M2B = 8;
const int led = 7;

boolean auton = false;

//index 1 is left joystick Y, index 2 is left trigger, 
//and index 4 is right joystick Y, index 5 is right trigger 
//index 6 is 255 if there is new data
//Index 0 is 'L' index 3 is 'R'
byte raw_data[7];

void checkData() {
   
//Wait until at least 6 bytes are available. We expect 6 bytes at a time from msg
if (Serial.available() >= 6) {

  for(int i = 0; i < 6; i++) {
    raw_data[i] = Serial.read();
//      Serial.print(" Data: ");
//      Serial.print(raw_data[i]);
  }

//   If we get out of sync realign data. Could also try Serial.flush() instead if not aligned
  for(int i = 0; i < 6; i++) {
    if(raw_data[0] == 76 && raw_data[3] == 82) {
      break;
    }
    byte temp = raw_data[0];
    raw_data[0] = raw_data[1];
    raw_data[1] = raw_data[2];
    raw_data[2] = raw_data[3];
    raw_data[3] = raw_data[4];
    raw_data[4] = raw_data[5];
    raw_data[5] = temp;
  }
  raw_data[6] = 255;
}
}

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
  checkData(); // Checks data and updates raw_data global variable

  //Raw data[6] is a flag that checkdata sets. Make sure to set this to other than 255 if we have tended to it        
   if(raw_data[6] == 255) {
      raw_data[6] = 0;
      for(int i = 0; i < 6; i++) {
        Serial.print(" ");
        Serial.print(raw_data[i]);
      }
        Serial.println("");
   }

  analogWrite(led, raw_data[1]);
  
  checkInput();
  
  if (haveBlock && distanceOne < pitDist && distanceTwo < pitDist) {
    // speeds are different - determine after testing - Sam
    moveForward(speed); 
    delay(endZone);
    moveBackward(speed);
    delay(endZone);
    haveBlock = false;
  } 
  else if (colorCorrect) {
    haveBlock = true;
    blackLineFollower();
  } 
  else {
    blockBlock(speed);
  }
}

void blackLineFollower() {
  // black Line Follower + Turn at the end of the line (corner turns - Darren Kong)
  if (distanceOne < safeDist && distanceTwo < safeDist) {
    turnRight(speed);
    delay(turn);
  }
  else if (distanceOne < safeDist && distanceTwo < safeDist) {
    turnRight(speed);
    delay(turn * 2);
  } 
  else {
    moveForward(speed);
    // check black line
    checkBL(); 
    delay(delays); 
    // if its not on the black line, checks right side
    if (!onBL) {
      moveBackward(speed);
      delay(delays);
      turnRight(speed);
      delay(turn);
      moveForward(speed);
      delay(delays);
      checkBL(); 
      // if its still not on the black line, checks left side
      if (!onBL) {
        moveBackward(speed);
        delay(delays);
        turnLeft(speed);
        delay(2 * turn);
        moveForward(speed);
        delay(delays);
        checkBL();
      }
    }
  }
}

void blockBlock(double speed) {
  moveForward(speed);
  delay(delays);
  closeServo();
  turnRight(speed);
  delay(turn);
  moveForward(speed);
  delay(delays * 2);
  openServo();
  moveBackward(speed);
  delay(delays * 2);
  turnLeft(speed);
  delay(turn);
  moveBackward(speed);
  delay(delays);
}

boolean checkBL() {
  if (analogRead(infared) < black) {
    onBL = false;
  }
  else {
    onBL = true;
  }
}

void checkInput() {
  char autoButton = Serial.read();
  /*if (Serial.available() > 0) {
    autoButton = Serial.read();
  }*/

  if (autoButton == 'm') {
    auton = !auton;
    if (auton) {
      blackLineFollower();
      Serial.println("Autonomous mode activated");
    }
    else {
      Serial.println("Autonomous mode deactivated");
    }
    Serial.println(autoButton);
  }
  
  if (!auton) {
    if (raw_data[1] > 0 && raw_data[1] < 128){
      //Motor 1 Forward
      analogWrite(M1F, (127 - (int)raw_data[1]) * 2);
    }
    if (raw_data[1] > 127 && raw_data[1] < 256){
      //Motor 1 Backwards
      analogWrite(M1B, (127 - (int)raw_data[1]) * 2);
    }
    if (raw_data[4] > 0 && raw_data[4] < 128){
      //Motor 2 Forward
      analogWrite(M2F, (127 - (int)raw_data[4]) * 2);
    }
    if (raw_data[4] > 127 && raw_data[4] < 256){
      //Motor 2 Backwards
      analogWrite(M2B, (127 - (int)raw_data[4]) * 2);
    }
    if (autoButton == 'n') {
      Serial.println(autoButton);
      eStop();
    }
    if (raw_data[2] > 0) {
      //Opens Servo
      openServo();
    }
    if (raw_data[5] > 0) {
      //Close Servo
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
  Serial.println("Servo Opened"); 
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
  Serial.println("Servo Closed");
}

