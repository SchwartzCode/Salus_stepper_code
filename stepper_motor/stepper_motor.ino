#include <Stepper.h>
#define stepPin 7
#define dirPin 8

#define stepAngle 1.8
#define stepIncrement 5   // may need to change this

float deg = 0;
int pos = 0;
int val = 0;
int desPos = 8000; // 800 ticks per revolution

const int stepsPerRev = 800;

Stepper stepper(stepsPerRev, stepPin, dirPin);

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(1000); //speed in RPM
}

void loop() {
  if (desPos > pos + stepIncrement - 1) {
    stepper.step(stepIncrement);
    pos = pos + stepIncrement;
  } else if (desPos < pos - stepIncrement - 1) {
    stepper.step(-stepIncrement);
    pos = pos - stepIncrement;
  }

//  deg = posToDegree(pos);
//  Serial.print("stepper ");
//  Serial.println(deg);
  Serial.println(pos);
//  delay(50);
}
