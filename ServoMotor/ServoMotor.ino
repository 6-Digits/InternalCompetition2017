
#include <Servo.h>
Servo test1;
int pos = 0;

int ledPin = 2;    // select the input pin for the potentiometer
   // select the pin for the LED

void setup() {
  test1.attach(9);
  Serial.begin(9600);
  
    // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  for(pos = 0; pos < 180; pos++){
      test1.write(pos);
      delay(10);
  }
  for(pos = 180; pos > 0; pos--){
      test1.write(pos);
      delay(10);
  }
}
void openServo(pos){
    for(pos = 0; pos < 180; pos++){
      test1.write(pos);
      delay(10);
  }
  for(pos = 180; pos > 0; pos--){
      test1.write(pos);
      delay(10);
  }
}

