// #Includes    //////////////////////////////////////////////////////////////////////


// Data Types   //////////////////////////////////////////////////////////////////////
struct Coordinate{
    double x_coord;
    double y_coord;
};
struct Velocity{
    double x_velocity;
    double y_velocity;
};
struct SpaceObject{
    Coordinate coord;
    Velocity velo;   
};
struct Prediction{
    Coordinate coord;
    double time;
};

// #Defines     //////////////////////////////////////////////////////////////////////
#define ScanStartAngle 15

// Globals      //////////////////////////////////////////////////////////////////////

/* Properties of the Object to be Captured*/
SpaceObject Target;
/* Additional Property for Target Object */
Coordinate prev;
/* Additional Property for Target Object*/
double target_width;

/* Properties of the Host Object*/
SpaceObject Host;
/* Properties of the Capturing Object*/
SpaceObject Projectile;
/* Side of approach */
bool DirectionLR;

// Functions    ///////////////////////////////////////////////////////////////////////

/*
Start Clock, Initialize Servo and Scanner
*/
void init();

/* 
Notify What Target to Look for and Where
*/
void assignTarget(bool isLeft, Velocity route, double width){
    DirectionLR = isLeft;
    target_width = width;
    if(isLeft){
        // Start Scanning on the left
        setScanAngle(ScanStartAngle);

    }
    else{
        // Start Scanning on the right
        setScanAngle(-ScanStartAngle);
    }
    // define next scan as being the first scan for the object
    prev.x_coord = 0;
    prev.y_coord = 0;
}

/*

*/
void DetectObject(SpaceObject target){

}

/*
Sets the angle of the next scan
*/
void setScanAngle(double angle);

/*
Scan's and returns the distance to the scan,
returns -1 if object is not detected or out of operable range 
*/
void scan();


double getInterceptTime(){
    // Think of the objects trajectory as a beam
    // When does the target object intercept this beam
    // When the the vector between the two objects the same as the direction given by 

    // (y_Host - y_Target + (T)vy_Target) / (x_Host - x_Target + (T)xy_Target) = vy_Host / vx_Host
    // vx_Host(y_Host - y_Target + (T)vy_Target) = vy_Host(x_Host - x_Target + (T)xy_Target)
    // vx_Host(y_Host - y_Target) + vx_Host(T)vy_Target = vy_Host(x_Host - x_Target) + vy_Host(T)xy_Target
    // vx_Host(y_Host - y_Target) - vy_Host(x_Host - x_Target) = vy_Host(T)xy_Target - vx_Host(T)vy_Target
    // vx_Host(y_Host - y_Target) - vy_Host(x_Host - x_Target) = T(vy_Host(xy_Target) - vx_Host(vy_Target))
    // vx_Host(y_Host - y_Target) - vy_Host(x_Host - x_Target) / (vy_Host(xy_Target) - vx_Host(vy_Target)) = T
    
    double tmp1 = Host.velo.x_velocity * (Host.coord.y_coord - Target.coord.y_coord);
    double tmp2 = Host.velo.y_velocity * (Host.coord.x_coord - Target.coord.x_coord);
    double tmp3 = (Host.velo.y_velocity * Target.velo.y_velocity) - (Host.velo.x_velocity * Target.velo.y_velocity);
    return (tmp1 - tmp2) / tmp3;
};

Coordinate getInterceptLocation(){
    // Think of the objects trajectory as a beam
    // When does the target object intercept this beam
    


    // x_coord + T x_velo / 
    // 
    // 
};

/* Returns a launch time based on the intercept location*/
double getLaunchTime(){
    return 0.0;
};

void updateTargetInfo(Coordinate new_location){

};

// Program      //////////////////////////////////////////////////////////////////////
void main(){
    init();
    assignTarget();
    while(!DetectObject()){

    }
    double angle = 0;
    while (angle < 90 && angle > -90)
    {
        scanForObject(angle);
        getPrediction();
        getIntercept();
    }
    
    
    
    
    
}