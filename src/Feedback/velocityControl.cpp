#include "main.h"
#include <vector>
using namespace std;

//Velocity Controller

//Default constructor
VelocityController::VelocityController(){}

//Velcity controller constructor takes a pointner to the abstract base class Filter allowing
//any derived class to be passed in. The constructor also requires a PID object and the 
//constants kV and kD
VelocityController::VelocityController(PID pid_, double velocityLookup_[], double kA_, Filter * filter_,double PIDconst_,double bangBang_){
    pid=pid_;
    for(int i = 0; i < 12;i++){
        velocityLookup[i]=velocityLookup_[i];
    }
    PIDconst=PIDconst_;
    bangBang=bangBang_;
    //kV=kV_;
    kA=kA_;
    filter=filter_;
}

//Deconstructor
VelocityController::~VelocityController(){}

//Seets the PID of the velocity controllerr
void VelocityController::setPID(double kp_, double ki_,double kd_){
    pid.setConstants(kp_,ki_,kd_);
}

//Computes the output of the velocity controller
double VelocityController::compute(double sensorVal){
    double filteredVal = filter->compute(sensorVal);
    if(setpoint!=0){
        //Checks if velocity is in a certain range and chooses between bang-bang, feedforward, PID
        if(setpoint-filteredVal>bangBang){
            pros::screen::print(TEXT_LARGE,5,"1");
            return 127;
        }else if(filteredVal-setpoint>1000){
            pros::screen::print(TEXT_LARGE,5,"3");
            return setpoint*velocityLookup[int(round((setpoint*PIDconst)/50))-1]*PIDconst;
        }else{
            outputA+=pid.compute(filteredVal);
            pros::screen::print(TEXT_LARGE,5,"2");
            return setpoint*velocityLookup[int(round((setpoint*PIDconst)/50))-1]*PIDconst+outputA;
        }
    }
    return 0;
}

//Sets the gains for the velocity controller
void VelocityController::setConstants(PID pid_, double velocityLookup_[12], double kA_){
    pid=pid_;
    for(int i = 0; i < 12;i++){
        velocityLookup[i]=velocityLookup_[i];
    }
    kA=kA_;
}
//Sets the target for the velocity controller
void VelocityController::setTarget(double setpoint_,double PIDconst_){
    setpoint=setpoint_;
    //accelSetpoint=accelSetpoint_;
    pid.setTarget(setpoint*PIDconst);
}

//Motion Profiling

//Constructor
LinearMotionProfile::LinearMotionProfile(double setpoint_, double maxVelocity_, double maxAccel_, double maxJerk_,VelocityController velController_){
    setpoint=setpoint_;
    maxVelocity=maxVelocity_;
    maxAccel=maxAccel_;
    maxJerk=maxJerk_;
    velController=velController_;
}

//Deconstructor
LinearMotionProfile::~LinearMotionProfile(){}

//Sets the target of the profile and resets the time
void LinearMotionProfile::setTarget(double dist){
    t=0;
    setpoint = dist;
    
}

//Overload that sets the target aswell as the maximum values
void LinearMotionProfile::setTarget(double dist, double maxVelocity_, double maxAccel_, double maxJerk_){
    t=0;
    setpoint = dist;
    maxVelocity=maxVelocity_;
    maxAccel=maxAccel_;
    maxJerk=maxJerk_;
}

//Follows the profile
double LinearMotionProfile::follow(){
    double a = maxAccel;
    double j = maxJerk;
    double v = maxVelocity;
    double p = setpoint;

    //Definition of a piecewise function for velocity, based on time. This will bring the robot
    //exactly to the setpoint without violating any constraints

    //Initial Jerk
    if(t>=0&&t<a/j){
        velController.setTarget((j*pow(t,2))/2,11.1408);
    }
    //Max Acceleration
    else if(t>=a/j&&t<v/a){
        velController.setTarget((a*t)-pow(a,2)/(2*j),11.1408);
    }

    //Negative Jerk    
    else if(t>=v/a&t<(pow(a,2)+j*v)/(a*j)){
        velController.setTarget(v+(-pow(-pow(a,2)-(j*v)+(j*a*t),2)/(2*pow(a,2)*j)));
    }

    //Stable Veloicty
    else if(t>=(pow(a,2)+j*v)/(a*j)&&t<p/v){
        velController.setTarget(v,11.1408);
    }
    
    //Negative Jerk
    else if(t>=(p/v)&&t<(a/j)+(p/v)){
        velController.setTarget(v-(j*pow(t*v-p,2))/(2*pow(v,2)),11.1408);
    }
    
    //Max Negative Accelration
    else if(t>=(a/j)+(p/v)&&t<(pow(v,2)+p*a)/(v*a)){
        velController.setTarget((-a*t)+((a*p)/v)+(pow(a,2)/(2*j)+v),11.1408);
    }
    
    //Positive Jerk
    else if(t>=(pow(v,2)+p*a)/(v*a)&&t<((j*pow(v,2))+(j*p*a)+(v*pow(a,2)))/(j*v*a)){
        velController.setTarget((j/2)*pow(t-(((j*pow(v,2))+(j*p*a)+(v*pow(a,2)))/(j*v*a)),2),11.1408);
    }
    t+=0.01;
    velocity=velController.compute(fabs(l1.get_actual_velocity()));   
    return velocity;
}

