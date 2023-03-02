
#pragma once
#include "main.h"
enum DriveState{Driving,Turning,Stopping};
inline DriveState driveState;
extern pros::Task driveTask;
class PID{
    public:
        PID(double kP_=0, double kD_=0, double kI_=0);
        ~PID();
        double compute(double sensorVal);
        void setTarget(double setpoint_);
        void setConstants(double kP_=0, double kD_=0, double kI_=0);
        double derivitive;
        double error;
        double setpoint;
    private:
        double integral;
        double prevError;
        double kP;
        double kD;
        double kI;
};

void Turn(double angle);
void Drive(double dist);
void Drive(double dist, double maxVelocity_, double maxAccel_, double maxJerk_);
void turnWait();
void driveWait();
void driveTaskF();

//PDI not PID
//inline PID turnPID(2.84,0.13,8.65);
inline PID turnPID(2.78,14,0.0035);
inline PID leftDrivePID(0,0,0);
inline PID rightDrivePID(0,0,0);
inline PID headingPID(7,1,0.1);
