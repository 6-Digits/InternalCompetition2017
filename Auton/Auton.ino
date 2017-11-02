double distanceOne, distanceTwo; // These are the values from the ultrasonic sensors.
boolean colorCorrect, onWL, haveBlock; // Determines whether the color sensor detects the correct color and the infared
double memX = 0, derX, memY = 0, derY, enemyColorS, enemyColorE, ourColorS, ourColorE; //The derivative variables are for FULL Autonomous. The enemy color start and end range. The our color start and end range.
double speed;
double white;
long delay, turn, endZone; // How long it will take to then switch / change direction of motor and the amount of time it takes to turn
double safeDist, pitDist; //Safe distance from the pit.
const int ultraSonicOne, ultraSonicTwo, infared, servoOne, servoTwo, colorSensor, motorOne, motorTwo, radio;
void setup() {
  serial.begin(9600);  // put your setup code here, to run once:
  serial.pinMode(ultraSonicOne, INPUT);
  serial.pinMode(ultraSonicTwo, INPUT);
  serial.pinMode(infared, INPUT);
  serial.pinMode(servoOne, OUTPUT);
  serial.pinMode(servoTwo, OUTPUT);
  serial.pinMode(colorSensor, INPUT);
  serial.pinMode(motorOne, OUTPUT);
  serial.pinMode(motorTwo, OUTPUT);
  serial.pinMode(radio, INPUT);
  servoFortyFive();
  eStop();
}

void loop() {
  if (haveBlock && distanceOne < pitDist && distanceTwo < pitDist) {
    moveForward(speed);
    delay(endZone);
    moveBackward(speed);
    delay(endZone);
    haveBlock = false;
  } else {
    if (colorCorrect) {
      haveBlock = true;
      whiteLineFollower();
    } else {
      blockBlock();
    }
    /*
      if(colorCorrect){
      time = 1; // whatever
      memX  = distanceOne - memX;
      derX = memX / time;
      memY  = distanceTwo - memX;
      derY = memY / time;
      if(der
      if(derX < 0 && derY < 0){
      turnLeft(speed);
      moveForward(speed);
      }
      if(derX < 0 && derY > 0){
      turnRight(speed);
      moveForward(speed);
      }
      if(derX > 0 && derY < 0){
      turnRight(speed);
      moveForward(speed);
      }
      if(derX > 0 && derY > 0){

      }
      } else {

      }
      }
    */
  }

}
void whiteLineFollower() {
  if (distance1 < safeDist && distance2 < safeDist) {               // White Line Follower + Turn at the end of the line (corner turns - Darren Kong)
    moveRight(speed);
    delay(turn);
  } else if (distance1 < safeDist && distance2 < safeDistance) {
    moveRight(speed);
    delay(turn * 2);
  } else {
    moveForward(speed);
    checkWL(); // check white line
    delay(delay);
    if (onWL) {
      continue;
    } else {
      moveBackwards(speed);
      delay(delay);
      moveRight(speed);
      delay(turn);
      moveForward(speed);
      delay(delay);
      checkWL();
      if (onWL) {
        continue;
      } else {
        moveBackwards(speed);
        delay(delay);
        moveLeft(speed);
        delay(2 * turn);
        moveForward(speed);
        delay(delay);
        checkWL();
      }
    }
  }
  void blockBlock(double speed) {      //Bruh
    moveForward(speed);
    delay(delay);
    closeServoMotor();
    moveRight(speed);
    delay(turn);
    moveForward(speed);
    delay(delay * 2);
    openServoOpen();
    moveBackward(speed);
    delay(delay * 2);
    moveLeft(speed);
    delay(turn);
    moveBackward(speed);
    delay(delay);
  }

  boolean checkWL() {
    if (analogRead(Infared_Sensor) < white) {
      onWhiteLine = false;
    } else {
      onWhiteLine = true;
    }
  }

