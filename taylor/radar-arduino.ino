#include <Servo.h>
#include <NewPing.h>
/* LIBRARIES
NewPing: http://playground.arduino.cc/Code/NewPing
*/

#define TRIGGER_PIN  10
#define ECHO_PIN     11
#define MAX_DISTANCE 41

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo radarServo;

int distance;
int servoDelay = 30;

void setup() {
  Serial.begin(115200);
  radarServo.attach(12);
  radarServo.write(15);
}

void loop() {

  for(int i=15; i<=165; i++){  
  radarServo.write(i);
  delay(servoDelay);

  getDistance();

  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }

  for(int i=165; i>15; i--){  
  radarServo.write(i);
  delay(servoDelay);

  getDistance();

  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}

int getDistance() {
 sonar.timer_stop();
 distance = sonar.ping_cm();
 if (distance == 0 || distance > 40) distance = MAX_DISTANCE;
 return distance;
}
