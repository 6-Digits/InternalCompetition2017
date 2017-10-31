int distanceOne, distanceTwo; // These are the values from the ultrasonic sensors.
boolean colorCorrect, onWhiteLine; // Determines whether the color sensor detects the correct color and the infared 
double memX = 0, derX, memY = 0, derY;
double speed;
void setup() {
    serial.begin(9600);  // put your setup code here, to run once:

}

void loop() {
    if(colorCorrect){
      time = 1; // whatever
      memX  = distanceOne - memX;
      derX = memX / time;
      memY  = distanceTwo - memX;
      derY = memY / time;
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

}
