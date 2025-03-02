#include <Servo.h>
#include <SharpIR.h>
#include <math.h>

#define IRsensor A0
#define model 1080

int distInCM;

SharpIR mySensor = SharpIR(IRsensor, model);

#define PWMsig 3

struct Coordinate
{
    double x_coord;
    double y_coord;
};
struct Velocity
{
    double x_velocity;
    double y_velocity;
};

Servo Servo1;
int reset = 0;
int launch = 179;
int servoAngle;

void setup()
{
    // put your setup code here, to run once:
    Servo1.attach(PWMsig);
    delay(5);
    Servo1.write(reset); // right
    servoAngle = reset;
    Serial.begin(9600);
}

#define servoStep 10
double convertDegreeToRadians(int angleDegrees){
    return angle * M_PI / 180;
}


void loop()
{
    Coordinate prevCoord;
    Coordinate newCoord;
    Velocity velo;
    long prevTime;
    long newTime;
    // put your main code here, to run repeatedly:

    // Scanner is facing right

    // Detect an object
    

    bool notFound = true;
    while (notFound)
    {
        distInCM = mySensor.distance();
        if (distInCM <= 40 && distInCM >= 10)
        {
            // set initial coordinate
            prevCoordinate.y_coord = 0;
            prevCoordinate.x_coord = distInCM;
            prevTime = millis();
            notFound = false;
        }
    }
    while (servoAngle + servoStep < 180)
    {
        // new servo angle
        servoAngle += servoStep;
        Servo1.write(servoAngle);
        
        notFound = true;
        while (notFound)
        {
            distInCM = mySensor.distance();
            if (distInCM <= 40 && distInCM >= 10)
            {
                // set initial coordinate
                newTime = millis();
                newCoord.x_coord = distInCM * cos(convertDegreeToRadians(servoAngle));
                newCoord.y_coord = distInCM * sin(convertDegreeToRadians(servoAngle));
                
                Serial.print("Angle: ");
                Serial.println(servoAngle);
                Serial.print("Time: ");
                Serial.println(newTime);
                Serial.print("Coordinate(x,y): ");
                Serial.print(newCoord.x_coord);
                Serial.print(", ");
                Serial.println(newCoord.y_coord);
                Serial.println();

                prevCoord = newCoord;
                notFound = false;
            }
        }

        // end scan and reset if prediction puts next scan out of range
        if(false){

        }
        /* code */
    }
}
