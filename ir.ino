#include <SharpIR.h>

# define IRsensor A0
# define model 1080

int distInCM;

SharpIR mySensor = SharpIR(IRsensor, model);

SharpIR init() {
  // put your setup code here, to run once: 
  Serial.begin(9600);
}

int getDistanceCMsingle(){
    return mySenstor.distance();
}

int getDistinceCM(){
    scan1 = getDistinceCMsingle();
    scan2 = getDistanceCMsingle();
    scan3 = getDistanceCMsingle();
    // return the median of the 3 scans
    if (scan1 > scan2 && scan1 < scan3)
    {
        return scan1;
    } else if (scan2 > scan1 && scan2 < scan3)
    {
        return scan2;    
    } else{
        return scan3;
    }    
}
