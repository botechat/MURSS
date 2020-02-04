#include <Servo.h>
#define servoLeftPin 9
#define servoRightPin 3

Servo servoLeft;
Servo servoRight;


void setup() {
  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);
}

void loop() {
  servoLeft.writeMicroseconds(2500);
}
