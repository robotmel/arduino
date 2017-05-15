#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <digitalWriteFast.h>
/* LIBRARIES
I2CDev: https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/I2Cdev
MPU6050: https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
digitalWriteFast: https://github.com/NicksonYap/digitalWriteFast or https://github.com/watterott/Arduino-Libs/tree/master/digitalWriteFast
*/

MPU6050 accelgyro;

#define runEvery(t) for (static long _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))


int16_t ax, ay, az;
float accBiasX, accBiasY, accBiasZ;
float accAngleX, accAngleY;
double accPitch, accRoll;

int16_t gx, gy, gz;
float gyroBiasX, gyroBiasY, gyroBiasZ;
float gyroRateX, gyroRateY, gyroRateZ;
float gyroBias_oldX, gyroBias_oldY, gyroBias_oldZ;
float gyroPitch = 180;
float gyroRoll = -180;
float gyroYaw = 0;

uint32_t timer;

// input
double InputPitch, InputRoll;

// initial values
double InitialRoll;

// Motors
const int enablea = 10;
const int enableb = 11;
const int a1 = 12;
const int b1 = 13;

		///////////////////
		////SETUP BEGIN////
		///////////////////

void setup() {

  Wire.begin();
//  Wire.setClock(400000UL); // Set I2C frequency to 400kHz


  Serial.begin(9600);

  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  delay(1500);

  // Motor
  pinModeFast(enablea, OUTPUT);
  pinModeFast(enableb, OUTPUT);
  pinModeFast(a1, OUTPUT);
  pinModeFast(b1, OUTPUT);

  digitalWriteFast(a1, HIGH);
  digitalWriteFast(b1, HIGH);
  
 //TODO: Better calibration 
  accelgyro.setXAccelOffset(-1692);
  accelgyro.setYAccelOffset(-926);
  accelgyro.setZAccelOffset(2355);
  accelgyro.setXGyroOffset(45);
  accelgyro.setYGyroOffset(-6);
  accelgyro.setZGyroOffset(22);

  gyroBiasX = 0;
  gyroBiasY = 0;
  gyroBiasZ = 0;

  accBiasX = 0;
  accBiasY = 0;
  accBiasZ = 16384;

  //Get Starting Pitch and Roll
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  accPitch = (atan2(-ax, -az) + PI) * RAD_TO_DEG;
  accRoll = (atan2(ay, -az) + PI) * RAD_TO_DEG;

  if (accPitch <= 360 & accPitch >= 180) {
    accPitch = accPitch - 360;
  }

  if (accRoll <= 360 & accRoll >= 180) {
    accRoll = accRoll - 360;
  }

  gyroPitch = accPitch;
  gyroRoll = accRoll;

  timer = micros();
  delay(1000);
  initializeValues();

}
		///////////////////
		/////SETUP END/////
		///////////////////

double Setpoint;

		/////////////////////
		////MOTOR CONTROL////
		/////////////////////

void MotorControl(double out) {
  if (out > 0) {
    digitalWriteFast(a1, LOW);
    digitalWriteFast(b1, LOW);
  } else {
    digitalWriteFast(a1, HIGH);
    digitalWriteFast(b1, HIGH);
  }

  byte vel = abs(out);
  if (vel < 0)
    vel = 0;
  if (vel > 255)
    vel = 255;

  analogWrite(enablea, vel);
  analogWrite(enableb, vel);
}

		//////////////////////
		////INITIAL VALUES////
		//////////////////////

void initializeValues() {

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  //////////////////////
  //  Accelerometer   //
  //////////////////////

  accPitch = (atan2(-ax/182.0, -az/182.0) + PI) * RAD_TO_DEG;
  accRoll = (atan2(ay/182.0, -az/182.0) + PI) * RAD_TO_DEG;

  if (accRoll <= 360 & accRoll >= 180) {
    accRoll = accRoll - 360;
  }

  //////////////////////
  //      GYRO        //
  //////////////////////

  gyroRateX = ((int)gx - gyroBiasX) * 131; 

  gyroPitch += gyroRateY * ((double)(micros() - timer) / 1000000);

  
  timer = micros();
  InitialRoll = accRoll;

  Setpoint = InitialRoll;
}

double filtered = 0;

		//////////////////
		////LOOP BEGIN////
		//////////////////

void loop() {

  runEvery(10) {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    //////////////////////
    //  Accelerometer   //
    //////////////////////

    accRoll = (atan2(ay/182.0, -az/182.0) + PI) * RAD_TO_DEG;

    if (accRoll <= 360 & accRoll >= 180) {
     accRoll = accRoll - 360;
    }

    //////////////////////
    //      GYRO        //
    //////////////////////

    gyroRateX = -((int)gx - gyroBiasX) / 131;

    double gyroVal = gyroRateX * ((double)(micros() - timer) / 1000000);

    timer = micros();

    //Complementary filter
    filtered = 0.98 * (filtered + gyroVal) + 0.02 * (accRoll);

    MotorControl(ComputePID(filtered - InitialRoll));

  }
}
		////////////////
		////LOOP END////
		////////////////

/*Compute PID Function*/

int outMax = 255;
int outMin = -255;
float lastInput = 0;
double ITerm = 0;
double kp = 85;
double ki = 3;
double kd = 0.5;

double ComputePID(double input)
{
  double error = Setpoint - input;

  ITerm += (ki * error);

  if (ITerm > outMax) ITerm = outMax;
  else if (ITerm < outMin) ITerm = outMin;
  double dInput = (input - lastInput);

  /*Compute PID Output*/
  double output = kp * error + ITerm + kd * dInput;

  if (output > outMax) output = outMax;
  else if (output < outMin) output = outMin;

  /*Remember some variables for next time*/
  lastInput = input;
  return output;
}
