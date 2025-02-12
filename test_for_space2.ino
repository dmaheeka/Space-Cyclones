#include <Servo.h>

# define trigPin 5
# define echoPin 4
# define PWMsig 3

Servo Servo1;
int reset = 0;
int launch = 179;

void setup() {
  // put your setup code here, to run once:
  Servo1.attach(PWMsig);
  delay(5);
  Servo1.write(reset);
  
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //pinMode(PWMsig, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = convertToCM(duration);

  //if within range the servo will rotate counterclockwise else clockwise
  if(distance <= 100){
    //servoPosition++;
    delay(15);
    Servo1.write(launch);
    delay(5);
    Serial.println(launch);
  }
  else{
    //servoPosition--;
    delay(15);
    Servo1.write(reset);
    delay(15);
    Serial.println(reset);
  }
  delay(100);
 
}

long convertToCM(long pulsebacktime){
  return pulsebacktime / 29 / 2;
}
