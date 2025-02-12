#include <Servo.h>

# define buttonClk 7
# define buttonCounterClk 4
# define PWMsig 3

Servo Servo1;
int servoPosition = 0;

void setup() {
  // put your setup code here, to run once:
  Servo1.attach(PWMsig);
  delay(5);
  Servo1.write(servoPosition);
  
  Serial.begin(9600);
  
  pinMode(buttonClk, INPUT);
  pinMode(buttonCounterClk, INPUT);
  //pinMode(PWMsig, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonClkState = digitalRead(buttonClk);
  int buttonCounterClkState = digitalRead(buttonCounterClk);

  if(buttonCounterClkState == 1 && servoPosition < 180){
    servoPosition++;
    Servo1.write(servoPosition);
    delay(5);
    Serial.println(servoPosition);
  }
  else if(buttonClkState == 1 && servoPosition >= 0){
    servoPosition--;
    Servo1.write(servoPosition);
    delay(5);
    Serial.println(servoPosition);
  }
}
