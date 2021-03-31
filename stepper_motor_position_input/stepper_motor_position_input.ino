#include <Stepper.h>
#define stepPin 7
#define dirPin 8 // blue wire on stepper driver

#define stepAngle 1.8

int stepIncrement = 6; //initial step increment, can be changed in accel loop  

float deg = 0;
long pos = 0;
int val = 0;
long desPos = pos; //8050; // 800 ticks per revolution at slow speed

long maxPos = 0;
long minPos = -130000;

int atTop = 0;
int atBottom = 0;

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
    // apply desired change to desPos and bound at limits 
    Serial.println(pos);
    if(changeInPos != 0)
      desPos += changeInPos;
      if(desPos > maxPos)
        desPos = maxPos;
      else if (desPos<minPos)
        desPos = minPos;
    Serial.println(desPos);
  }

  // move stepper toward desired position
  if (desPos > pos + stepIncrement - 1 && pos<maxPos) {
    // increase pos
    stepper.step(stepIncrement);
    pos = pos + stepIncrement;
  } else if (desPos < pos - stepIncrement - 1 && pos>minPos) {
    // decrease pos
    stepper.step(-stepIncrement);
    pos = pos - stepIncrement;
  } else{
  }

  // check limit switches
  int limit_top = analogRead(A0);
  int limit_bottom = analogRead(A5);
  if(limit_top > 1000 && !atTop && !atBottom){
    Serial.println("AT TOP");
    // switch has been hit, update current pos accordinly (will stop stepper)
    atTop = 1;
    pos = minPos;
    desPos = pos; // so stepper rests at current state until given new command
  } else if (atTop && limit_top < 800){
    // no longer at limit, update atTop
    atTop = 0;
    delay(50);
  }
  if(limit_bottom > 1000 && !atBottom && !atTop){
    Serial.println("AT BOTTOM");
    // switch has been hit, update current pos accordinly (will stop stepper)
    atBottom = 1;
    pos = maxPos;
    desPos = pos; // so stepper rests at current state until given new command
  } else if (atBottom && limit_bottom < 800){
    // no longer at limit, update atTop
    atBottom = 0;
    delay(50);
  }
  
  delayMicroseconds(1600);
}
