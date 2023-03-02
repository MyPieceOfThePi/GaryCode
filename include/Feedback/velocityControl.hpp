
#pragma once
#include "main.h"
#include <vector>
using namespace std;

//Class that controls velocity for flywheel and drive
class VelocityController{
    public:
    VelocityController();
    VelocityController(PID pid_, double velocityLookup_[], double kA_, Filter * filter_,double PIDconst_,double bangBang_);
    ~VelocityController();
    double bangBang=100;
    double compute(double sensorVal);
    void setPID(double kp_, double ki_,double kd_);
    void setConstants(PID pid_, double velocityLookup_[], double kA_=0);
    void setTarget(double setpoint_,double PIDconst_=1);
    double setpoint=400;
    private:
    double velocityLookup[12];
    double accelSetpoint;
    Filter * filter;
    PID pid;
    double kV;
    double kA;
    double outputA;
    double PIDconst;
};

//Class that creates and follows a velocity and acceleration profile
class LinearMotionProfile{
    public:
        LinearMotionProfile(double setpoint_, double maxVelocity_, double maxAccel_, double maxJerk_,VelocityController velController_);
        ~LinearMotionProfile(); 
        double follow();
        void setTarget(double dist, double maxVelocity_, double maxAccel_, double maxJerk_);
        void setTarget(double dist);
        double velocity = 0;
        double t = 0;
    private:
        double maxJerk;
        double maxAccel;
        double maxVelocity;
        double setpoint;
        VelocityController velController;
};