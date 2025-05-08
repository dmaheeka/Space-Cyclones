#include <Servo.h>
#include <SharpIR.h>
#include <math.h>

#define IRsensor A0
#define model 1080
#define PWMsig 3

{ // Structs
    struct Target{
        int val;
    };
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
}

{ // Static Variables
    #define maxDist 40
    #define minDist 10
    #define servoStep 2
}

{ // Global Variables
    SharpIR mySensor = SharpIR(IRsensor, model);
    int distInCM;
    Servo Servo1;
    int reset = 0;
    int launch = 179;
    int servoAngle;
}

{ // Math Functions
    double convertDegreeToRadians(int angleDegrees)
    {
        return angleDegrees * M_PI / 180;
    }
}

{ // Print Output Functions
    void printServoPredictionData(int servoAngle, float newTime, float predict_time, Coord newCoord, Coord predict, float magnitude)
    {
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
    }

}

{ // Mission Functions
    scanForTarget(){
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
            // changed from velo to avgVelo
            predict.x_coord = newCoord.x_coord + (avgVelo.x_velocity * predict_time);
            predict.y_coord = newCoord.y_coord + (avgVelo.y_velocity * predict_time);
            magnitude = sqrt((predict.x_coord * predict.x_coord) + (predict.y_coord * predict.y_coord));

            printServoPredictionData(servoAngle, newTime, predict_time, newCoord, predict, magnitude);

            prevCoord = newCoord;
            notFound = false;
        }

    }
}

{ // Not Implimented
    Target getAssignment(){
        /* wait for assignment */
        while (false){
            // Get Assignment
            Target target = nullptr;
            // Determine if Assignment is viable
            if( targetIsViable(target) ){
                /* return assignment */
                return target;
            }      
        }         
    }

    bool targetIsViable(Target target){
        if (condition)
        {
            /* code */
        }
        


        
        Serial.print("Assignment is accepted as a feasible target");
        return true;
    }
}

void restart(){ loop() }

void exit(){ while (true){} }

void setup() // put your setup code here, to run once:
{
    Serial.begin(9600);
    Serial.println("Initializing...");
    Servo1.attach(PWMsig);
    delay(100);
    servoAngle = reset;
    Servo1.write(servoAngle);
    delay(100);
    Serial.println("Starting...");
}

void loop()
{
    /* Get Target Assignment */
    
        // Listen for Assignment
            // *prototype: start trigger 
        // Determine if Viable / Worthwhile
            // use object Size, Distance, Mass
        // Accept / Deny Mission Assignment
    assignment = getAssignment();
    /* Get Predicted Approach */
        // Using Assignment Data:
        // Determine where and when object will approach
    prediction = getPredictedApproach(assignment);
    /* Start Mission Upon Approach */
        // Sleep until predicted approach
    sleep(prediction.delay);    
    /* Scan for Target */
        // Using Prediction, choose angle to scan and direction to track object into
    /* Track Target and Predict */
        // Determine potential launch position
        // Track the target in the direction
        // Based on prediction accuracy, determine a final launch angle
            // *prototype: based on intersection with static launch angle
    /* Fire Projectile */
        // Fire based on prediction
    /* Navigate Projectile to Target */
    /* Deploy Net */
    /* Determine if Mission Sucessful or not */
    /* Display Mission Status */




    // Coordinate prevCoord;
    // Coordinate newCoord;
    // Velocity velo;
    // Velocity avgVelo;
    // avgVelo.x_velocity = 0;
    // avgVelo.y_velocity = 0;
    // int count = 1;
    // long prevTime;
    // long newTime;
    // // put your main code here, to run repeatedly:

    // // Scanner is facing right

    // // Detect an object
    // bool notFound = true;
    // while (notFound)
    // {
    //     distInCM = mySensor.distance();
    //     if (distInCM <= maxDist && distInCM >= minDist)
    //     {
    //         // set initial coordinate
    //         prevCoord.y_coord = 0;
    //         prevCoord.x_coord = distInCM;
    //         prevTime = millis();

    //         Serial.print("Angle: ");
    //         Serial.println(servoAngle);
    //         Serial.print("Time: ");
    //         Serial.println(prevTime);
    //         Serial.print("Coordinate(x,y): ");
    //         Serial.print(prevCoord.x_coord);
    //         Serial.print(", ");
    //         Serial.println(prevCoord.y_coord);

    //         notFound = false;
    //     }
    // }
    // while (servoAngle + servoStep <= 180)
    // {
    //     // new servo angle
    //     servoAngle += servoStep;
    //     Servo1.write(servoAngle);
    //     delay(100);

    //     int magnitude;
    //     notFound = true;
    //     while (notFound)
    //     {
    //         scanForTarget();
    //     }

    //     // end scan and reset if prediction puts next scan out of range
    //     if (magnitude > maxDist)
    //     {
    //         Serial.print("Program Stopped: Object out of range");
    //         while (true)
    //         {
    //         }
    //     }
    //     /* code */
    // }
    // Serial.print("Program Stopped: Ran out of servo angles");
    // while (true)
    // {
    // }
}
