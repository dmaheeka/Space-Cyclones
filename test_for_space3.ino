#include <Servo.h>
#include <SharpIR.h>

# define IRsensor A0
# define model 1080

int distInCM;

SharpIR mySensor = SharpIR(IRsensor, model);

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
}

void loop() {
  // put your main code here, to run repeatedly:

  distInCM = mySensor.distance();

  //if within range the servo will rotate counterclockwise else clockwise
  if(distInCM <= 40 && distInCM >= 10){
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

  // Print the measured distance to the serial monitor
  Serial.print("Mean distance: ");
  Serial.print(distInCM);
  Serial.println(" cm");
  
  delay(100);
 
}
