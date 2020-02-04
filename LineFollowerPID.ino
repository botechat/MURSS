#include <Servo.h>
#define sensorLeftPin A0
#define sensorRightPin A2
int sensorLeftCurrent, sensorLeftPrevious;
int sensorRightCurrent, sensorRightPrevious;
int soma1,soma2;
int sensorLeft, sensorRight;
int error,correction,lastError;
int errorSum = 0;
int kp = 10;
int ki = 0;
int kd = 15;
int P,D,I;
int motorLeft,motorRight;
int motorLeftInitial,motorRightInitial;
#define servoLeftPin 9
#define servoRightPin 3

Servo servoLeft;
Servo servoRight;

void setup(){
	servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);
	Serial.begin(9600);
  motorLeftInitial = 1580;
  motorRightInitial = 1420;
}

void loop(){
  follow();
	average();
  disp();
}

//####################################################################//

int filter(int sensorCurrent, int sensorPrevious) {
  if (abs(sensorCurrent - sensorPrevious) > 200) {
    sensorCurrent = sensorPrevious;
  }
  return sensorCurrent;
}


void average() {
  soma1 = 0;
  soma2 = 0;
  for (int x = 0; x < 3; x++) {
    sensorLeftCurrent = analogRead(sensorLeftPin);
    sensorLeftCurrent = filter(sensorLeftCurrent, sensorLeftPrevious);
    sensorLeftPrevious = sensorLeftCurrent;
    sensorRightCurrent = analogRead(sensorRightPin);
    sensorRightCurrent = filter(sensorRightCurrent, sensorRightPrevious);
    sensorRightPrevious = sensorRightCurrent;
    soma1 += sensorLeftCurrent;
    soma2 += sensorRightCurrent;
  }
  sensorLeft = soma1 / 3;
  sensorRight = soma2 / 3;
  sensorLeft = constrain(sensorLeft,0,500);
  sensorRight = constrain(sensorRight,0,500);
}

void PID(){
  
  error = sensorRight - sensorLeft;
  error = error/15;
  P = error * kp;
  I = errorSum*ki;
  D = (error - lastError)* kd;
  correction = P + D + I;
  lastError = error;
  errorSum += error;
}

void follow(){
  PID();
  motorLeft = motorLeftInitial + correction;
  motorRight = motorRightInitial + correction;
  motorLeft = constrain(motorLeft, 500, 2500); 
  motorRight = constrain(motorRight, 500, 2500);
  servoLeft.writeMicroseconds(motorLeft);
  servoRight.writeMicroseconds(motorRight);
}

void disp(){
  Serial.print(sensorLeft); Serial.print(",");
  Serial.print(sensorRight); Serial.print(",");
  Serial.println();
}
