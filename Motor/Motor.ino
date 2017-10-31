
const int motor_1;
const int motor_2; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor_1, OUTPUT);
  pinMode(motor_2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
//NEED TO TEST THE MOTOR DIRECTION!!!!!
void moveForward(int speed){
   analogWrite(motor_1, speed);
   analogWrite(motor_2, -1 * speed);
}
void moveBackward(int speed){
   analogWrite(motor_1, -1*speed);
   analogWrite(motor_2, speed);
}
void moveRight(int speed){
   analogWrite(motor_1, speed);
   analogWrite(motor_2, speed);
}

void moveLeft(int speed){
   analogWrite(motor_1, -1*speed);
   analogWrite(motor_2, 1*speed);
}
void eStop(){
   analogWrite(motor_1, 0);
   analogWrite(motor_2, 0);
}
