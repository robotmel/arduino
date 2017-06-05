#include <Servo.h>

const int laser = 7;

Servo vert; 
Servo hor;

void setup() { 
  vert.attach(8);
  hor.attach(9);
  digitalWrite(laser, HIGH);
}

void migrate(Servo &myServo, int newPos) {
  int wait=random(30,60); //randomize the wait to make it more interesting
  int pos = myServo.read(); //Read the current servo position
  if (pos < newPos) { 
    for (int i=pos; i < newPos; i++) {
      myServo.write(i);
      delay(wait); 
    }
  } else { 
    for (int i=pos; i > newPos; i--) { 
      myServo.write(i);
      delay(wait);
    }
  }
}
  
void randomPosition() {
  int rand=random(40,120); //The range is limited to 60 deg for better cat action
  migrate(hor, rand);
  
  rand=random(90,135); //The vertical range is limited to 45 deg also for better cat action. 
  migrate(vert, rand);
}
   
void loop() { 
  randomPosition();
  delay(2000);
}
