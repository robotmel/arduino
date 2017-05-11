#include <AFMotor.h>

const int trigPin A0;
const int echoPin A1;
AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_8KHZ);
 
void setup() {
  Serial.begin(9600);
  Serial.println("Motor test!");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  motor1.setSpeed(130);
  motor2.setSpeed (130);  
}
 
void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)/29.4;
  if (distance < 25)
	Serial.println ("Close Obstacle detected!" );
	Serial.println ("Obstacle Details:");
	Serial.print ("Distance From Robot is " );
	Serial.print (distance);
	Serial.print ( " CM!");
	Serial.println (" The obstacle is declared a threat due to close distance. ");
	Serial.println (" Turning !");
	motor1.run(FORWARD);
	motor2.run (BACKWARD);
	}
  else {
	Serial.println ("No obstacle detected. Moving forward");
	delay (15);
	motor1.run(FORWARD);
	motor2.run(FORWARD);  
	}
}
