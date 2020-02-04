#define sensorLeftPin A0
#define sensorRightPin A2
int sensorLeftCurrent, sensorLeftPrevious;
int sensorRightCurrent, sensorRightPrevious;
int soma1,soma2;
int sensorLeft, sensorRight;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(analogRead(sensorLeftPin)); Serial.print(",");
  //Serial.print(sensorRight); Serial.print(",");
  Serial.println();
  delay(100);
}

//########################################################//

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
}
