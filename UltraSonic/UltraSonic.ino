const int trigPin = 52;
const int echoPin = 3;

long duration;
double distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); //Set trigger  to ouptut
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  Serial.print("Distance: ");
  Serial.println(distance);
}
