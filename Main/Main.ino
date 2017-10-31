#include ServoMotor.h
#include Motor.h
#include UltraSonic.h
#include Auton.h

boolean auton = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (AUTO_BUTTON) {
    !auton;
  }
  
  if (auton) {
    Auton.setup();
  }
  else {
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
