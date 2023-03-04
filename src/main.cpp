#include "main.h"
#include <fstream>
float t = 80;
pros::Task driveTask(driveTaskF);
pros::Task flyTask(flywheelTaskF);
using namespace std;
void initialize() {
	pros::lcd::initialize();
	imu.reset();
	driveTask.suspend();
	l1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	l2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	l3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	r1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	r2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	r3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	pros::delay(2000);
}
void disabled() {}
void competition_initialize() {}
void autonomous() {
	driveTask.resume();
	flyTask.resume();
	fiveDiskRight();
} 
void opcontrol() {
	driveTask.suspend();
	flyTask.suspend();
	while(true){
		pros::screen::print(TEXT_MEDIUM,
		7,"10");
		subsystemControl();
		pros::delay(10);
	}
}
