#include <Stepper.h>
#define stepPin 7
#define dirPin 8

#define stepAngle 1.8

int stepIncrement = 6; //initial step increment, can be changed in accel loop  

float deg = 0;
long pos = 0;
int val = 0;
long desPos = pos; //8050; // 800 ticks per revolution at slow speed

long maxPos = 0;
long minPos = -130000;

const int stepsPerRev = 800;

Stepper stepper(stepsPerRev, stepPin, dirPin);

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(500); //speed in RPM

  Serial.println("Enter desired change in position in mm:");
}

void loop() {
  if(Serial.available()){
    String user_input = Serial.readString();
    // convert desired change in pos from mm to stepper ticks
    long changeInPos = -stepsPerRev*user_input.toFloat()/5; 
    if(changeInPos != 0)
//      Serial.println(changeInPos);
//      Serial.println(desPos);
      desPos += changeInPos;
      if(desPos > maxPos)
        desPos = maxPos;
      else if (desPos<minPos)
        desPos = minPos;
//      Serial.println(desPos);
//      Serial.println("\n\n");
  }
  
  if (desPos > pos + stepIncrement - 1) {
    // increase pos
    stepper.step(stepIncrement);
    pos = pos + stepIncrement;
  } else if (desPos < pos - stepIncrement - 1) {
    // decrease pos
    stepper.step(-stepIncrement);
    pos = pos - stepIncrement;
  } else{
  }

  delayMicroseconds(1600);
}
