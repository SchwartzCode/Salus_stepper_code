const int interruptPin = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting...");
//  attachInterrupt(digitalPinToInterrupt(interruptPin), intFunc, RISING);
}

void loop() {
  int limit_top = analogRead(A0);
  if(limit_top > 1000){
    Serial.println("PRESSED");
  }

}

//void intFunc(){
//  int ugh = digitalRead(interruptPin);
//  if(ugh == 1){
////    Serial.println("HEY!");
//  }
//}
