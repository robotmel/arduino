const int relayPin_1 = 3;	// choose the pin for the RELAY_1
const int relayPin_2 = 5;	// choose the pin for the RELAY_2
const int sensorPin = 6;	// choose the Jog sensor button pin
int val = 0;			// variable for reading the Jog sensor button pin status
bool stat = true;		// variable for reading actual RELAY status

void setup() {
  pinMode(relayPin_1, OUTPUT);	// declare RELAY_1 as output
  pinMode(relayPin_2, OUTPUT);	// declare RELAY_2 as output
  pinMode(sensorPin, INPUT);	// declare Jog sensor button as input
  digitalWrite(relayPin_1, HIGH);
  digitalWrite(relayPin_2, HIGH);
}

void loop(){
  val = digitalRead(sensorPin);	// read input value
  if (val == HIGH & stat == true) {	// check if the sensor input is HIGH and RELAY is turned OFF
    digitalWrite(relayPin_1, LOW);	// turn RELAY_1 ON
    digitalWrite(relayPin_2, LOW);	// turn RELAY_2 ON
    stat = false;			// change RELAYS status to turned ON
  }
  else if (val == HIGH & stat == false) {	// check if the sensor input is HIGH and RELAY is turned ON
    digitalWrite(relayPin_1, HIGH);	// turn RELAY_1 OFF
    digitalWrite(relayPin_2, HIGH);	// turn RELAY_2 OFF
    stat = true;			// change RELAY status to turned OFF
  }
delay(3000);				// 3 seconds delay
}
