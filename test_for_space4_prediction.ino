#include <Servo.h>
#include <SharpIR.h>
#include <math.h>

#define IRsensor A0
#define model 1080

int distInCM;

SharpIR mySensor = SharpIR(IRsensor, model);

#define PWMsig 3

#define maxDist 40
#define minDist 10
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
    delay(100);
    Servo1.write(reset); // right
    servoAngle = reset;
    delay(100);
    Serial.begin(9600);
    Serial.println("Starting...");
}

#define servoStep 2
double convertDegreeToRadians(int angleDegrees){
    return angleDegrees * M_PI / 180;
}


void loop()
{
    Coordinate prevCoord;
    Coordinate newCoord;
    Velocity velo;
    Velocity avgVelo;
    avgVelo.x_velocity = 0;
    avgVelo.y_velocity = 0;
    int count = 1;
    long prevTime;
    long newTime;
    // put your main code here, to run repeatedly:

    // Scanner is facing right

    // Detect an object
    bool notFound = true;
    while (notFound)
    {
        distInCM = mySensor.distance();
        if (distInCM <= maxDist && distInCM >= minDist)
        {
            // set initial coordinate
            prevCoord.y_coord = 0;
            prevCoord.x_coord = distInCM;
            prevTime = millis();

            Serial.print("Angle: ");
            Serial.println(servoAngle);
            Serial.print("Time: ");
            Serial.println(prevTime);
            Serial.print("Coordinate(x,y): ");
            Serial.print(prevCoord.x_coord);
            Serial.print(", ");
            Serial.println(prevCoord.y_coord);

            notFound = false;
        }
    }
    while (servoAngle + servoStep <= 180)
    {
        // new servo angle
        servoAngle += servoStep;
        Servo1.write(servoAngle);
        delay(100);
        
        int magnitude;
        notFound = true;
        while (notFound)
        {
            distInCM = mySensor.distance();
            if (distInCM <= maxDist && distInCM >= minDist)
            {
                // set initial coordinate
                newTime = millis();
                newCoord.x_coord = distInCM * cos(convertDegreeToRadians(servoAngle));
                newCoord.y_coord = distInCM * sin(convertDegreeToRadians(servoAngle));
                velo.x_velocity = (newCoord.x_coord - prevCoord.x_coord) / (newTime - prevTime);
                velo.y_velocity = (newCoord.y_coord - prevCoord.y_coord) / (newTime - prevTime);
                // velocity everaging
                avgVelo.x_velocity = ((avgVelo.x_velocity * count) + velo.x_velocity) / (count + 1);
                avgVelo.y_velocity = ((avgVelo.y_velocity * count) + velo.y_velocity) / (count + 1);
                count++;


                // prediction

                // time
                // yposition + Tyvelo / xposition + Txvelo = tan(servoAngle + servoStep)
                // yposition + Tyvelo = (xposition + Txvelo)tan(servoAngle + servoStep)
                // Tyvelo - (Txvelo)tan(servoAngle + servoStep) = (xposition)tan(servoAngle + servoStep) - yposition
                // T(yvelo - (xvelo)tan(servoAngle + servoStep)) = (xposition)tan(servoAngle + servoStep) - yposition
                // T = ((xposition)tan(servoAngle + servoStep) - yposition) / (yvelo - (xvelo)tan(servoAngle + servoStep))
                double tangent = tan(convertDegreeToRadians(servoAngle + servoStep));
                int predict_time = ((newCoord.x_coord * tangent) - newCoord.y_coord) / (velo.y_velocity - (velo.x_velocity * tangent));
                // location
                Coordinate predict;
                //changed from velo to avgVelo
                // https://www.desmos.com/calculator/egrmzchife
                // Desmos visualization for the path prediction formulas
                predict.x_coord = newCoord.x_coord + (avgVelo.x_velocity * predict_time);
                predict.y_coord = newCoord.y_coord + (avgVelo.y_velocity * predict_time);
                magnitude = sqrt((predict.x_coord * predict.x_coord) + (predict.y_coord * predict.y_coord));
                
                Serial.print("Angle: ");
                Serial.println(servoAngle);
                Serial.print("Time: ");
                Serial.println(newTime);
                Serial.print("Coordinate(x,y): ");
                Serial.print(newCoord.x_coord);
                Serial.print(", ");
                Serial.println(newCoord.y_coord);                
                Serial.println("Prediction(t,x,y,d): ");
                Serial.print(newTime + predict_time);
                Serial.print(", ");
                Serial.print(predict.x_coord);
                Serial.print(", ");
                Serial.print(predict.y_coord);
                Serial.print(", ");                
                Serial.println(magnitude);

                prevCoord = newCoord;
                notFound = false;
            }
        }

        // end scan and reset if prediction puts next scan out of range
        if(magnitude > maxDist){
            Serial.print("Program Stopped: Object out of range");
            while(true){}
        }
        /* code */
    }
    Serial.print("Program Stopped: Ran out of servo angles");
    while(true){}
}
