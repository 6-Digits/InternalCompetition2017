# InternalCompetition2017
The program used to control a remote control robot for the Stony Brook University Robotics Team Internal Competition. This program is written in Arduino to be used by an Arduino Servo Controller. The code was written for specific input wiring and inputs from an Xbox 360 Controller. 

To run the code, it must be uploaded to an Arduino Servo Controller using the Arduino IDE and connection wire. The program for running the Xbox 360 controller to move the robot is seperate from the Arduino File and must be obtained seperately. 

To change the code for the wiring, modify the following code segment in the Arduino File:
```Arduino
const int M1F= 5;
const int M1B = 6;
const int M2F = 7;
const int M2B = 8;
const int led = 7;
```
Change the values for the pins on the breadboard attached to the Arduino Servo Controller. 
