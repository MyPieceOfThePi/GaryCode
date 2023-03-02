using namespace pros;
#pragma once
#include "main.h"
//Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
//Motors
inline pros::Motor l1(10,pros::E_MOTOR_GEARSET_06,true);
inline pros::Motor l2(9,pros::E_MOTOR_GEARSET_06,false);
inline pros::Motor l3(13,pros::E_MOTOR_GEARSET_06,true);
inline pros::Motor r1(2,pros::E_MOTOR_GEARSET_06,false,pros::E_MOTOR_ENCODER_DEGREES);
inline pros::Motor r2(1,pros::E_MOTOR_GEARSET_06,true);
inline pros::Motor r3(7,pros::E_MOTOR_GEARSET_06,false) ;
inline pros::Motor intake(8,pros::E_MOTOR_GEARSET_06,true);
inline pros::Motor flywheel(11,pros::E_MOTOR_GEARSET_06,false);

//pistons
inline pros::ADIDigitalOut indexer('A');
inline pros::ADIDigitalOut expansion('B');

//sensors
inline pros::Imu imu(6);

//driver control functions
void setTank(int leftPower, int rightPower);
void flywheelTaskF();
void tankDriveControl();
void subsystemControl();


//filters
inline EMA flywheelEMA(0.2);
inline EMA driveEMA(0.01);

//Controllers
inline PID flywheelPID(0.001,0,0);
inline PID flywheelPIDA(0.001,0,0);
inline PID driveVelocityPID(0.0001,0,0);
inline double flywheelLookup[12]={0.211,0.211,0.211,0.211,0.211,0.23,0.228,0.22,0.22,0.187,0.197,0.211};
inline double driveLookup[12]={0.211,0.211,0.211,0.211,0.211,0.211,0.211,0.211,0.211,0.211,0.211,0.211};
inline VelocityController flywheelController(flywheelPID,flywheelLookup,0,&flywheelEMA,1,20);
inline VelocityController flywheelControllerA(flywheelPIDA,flywheelLookup,0,&flywheelEMA,1,20);
inline VelocityController driveVelocityController(driveVelocityPID,driveLookup,0,&driveEMA,11.14,100);
inline LinearMotionProfile driveProfile(24.0,35.0,100.0,320,driveVelocityController);