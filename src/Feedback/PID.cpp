#include "main.h"
//PID constructor
float currAngle = 0;
float f = 0;
int backFlag = 1;
PID::PID(double kP_, double kD_, double kI_){
    kP = kP_;
    kI = kI_;
    kD = kD_;
}

//Destructor
PID::~PID(){}
void PID::setConstants(double kP_, double kD_, double kI_){
    kP = kP_;
    kI = kI_;
    kD = kD_;
}
//Computes the PID output based on the input, a value from a sensor
double PID::compute(double sensorValue){
    error = setpoint - sensorValue;
    derivitive=error-prevError;
    if(fabs(error)<setpoint){
        integral += error;
    }
    if((error>0&&prevError<0)||(error<0&&prevError>0)){
        integral=0;
    }
    prevError=error;
    pros::screen::print(TEXT_MEDIUM,3,"%f",error);
    return kP*error+kD*derivitive+integral*kI;
}

//Sets the PID target
void PID::setTarget(double setpoint_){
    setpoint=setpoint_;
}
void Turn(double angle){
    turnPID.setpoint = angle;
    driveState=Turning;
    headingPID.setTarget(angle);
}

void Drive(double dist){
    if(dist<0){
        backFlag=-1;
    }else{
        backFlag=1;
    }
    driveProfile.setTarget(fabs(dist));
    driveState=Driving;
}

void Drive(double dist, double maxVelocity_, double maxAccel_, double maxJerk_){
    if(dist<0){
        backFlag=-1;
    }else{
        backFlag=1;
    }
    driveProfile.setTarget(fabs(dist),maxVelocity_,maxAccel_,maxJerk_);
    driveProfile.t=0;
    driveState=Driving;
}
//This function will be called in the PID task
void driveTaskF(){
    headingPID.setTarget(0);
    //pros::delay(2000);
    while(true){
        //Checks if the robot is in turn mode, and turns according to the turn PID
        if(driveState==Turning){
            double power = turnPID.compute(imu.get_rotation());
            setTank(power,-power);
    //Checks if the robot is in drive mode, and drives according to the drive PID
        }else if(driveState==Driving){
            double power =driveProfile.follow();
            pros::screen::draw_pixel(100*f,227-2*power);
            pros::screen::print(TEXT_MEDIUM,2,"%f",(r1.get_position())/360*(3/7)*(4*3.14159265));
            double headingPower = headingPID.compute(imu.get_rotation());
            if(backFlag>0){
                setTank((power)+headingPower,(power)-headingPower);
            }else{
                setTank(-power+headingPower,-power-headingPower);
            }
        }else if(driveState=Stopping){
            setTank(0,0);
            driveProfile.t = 0;
        }
        f+=0.01;
        pros::delay(10);
    }
}
void turnWait(){
    int stopCounter=0;
    int t = 0;
    while(true){
        if(fabs(turnPID.derivitive)<0.1){
            stopCounter+=10;
            if(stopCounter>150&&t>500){
                driveState=Stopping;
                return;
            }
        }else{
            stopCounter=0;
        }
        t+=10;
        pros::delay(10);
    }
}
void driveWait(){
    int stopCounter=0;
    while(true){
        if(fabs(driveProfile.velocity)<1&&stopCounter>200){
            driveState=Stopping;
            return;
        }
        stopCounter+=10;
        pros::delay(10);
    }
}