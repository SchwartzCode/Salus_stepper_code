#include <Stepper.h>
#define stepPin 7
#define dirPin 8

#define stepAngle 1.8

int stepIncrement = 6; //initial step increment, can be changed in accel loop  

float deg = 0;
long pos = 0;
int val = 0;
long desPos = 2000; //8050; // 800 ticks per revolution at slow speed

const int stepsPerRev = 800;

Stepper stepper(stepsPerRev, stepPin, dirPin);

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(500); //speed in RPM

  Serial.println(desPos);
}

void loop() {
  //accelerate
//  if(pos/400 > stepIncrement-1 && stepIncrement < 6){
//    stepIncrement++;
//    Serial.println(pos);
//    Serial.println(stepIncrement);
//  }
  
  if (desPos > pos + stepIncrement - 1) {
    stepper.step(stepIncrement);
    pos = pos + stepIncrement;
  } else if (desPos < pos - stepIncrement - 1) {
    stepper.step(-stepIncrement);
    pos = pos - stepIncrement;
  } else{
    Serial.println(pos);
    Serial.println(desPos);
  }
  //  deg = posToDegree(pos);
  //  Serial.print("stepper ");
  //  Serial.println(deg);
  delayMicroseconds(1600);
}
