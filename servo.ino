#include <Servo.h>

# define fullRight 0
# define fullLeft 180
# define PWMsig 3

Servo myServo;

Servo init(){
    myServo.attach(PWMsig);
    delay(5);
    myServo.write(90)
    return myServo;
}

bool rotate(Servo myServo, int angle){
    if(angle <= fullLeft && angle >= fullRight){
        myServo.write(angle)
        return true;
    }
    return false;
}