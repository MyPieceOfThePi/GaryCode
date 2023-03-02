#include "main.h"
#pragma once
//Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
//Motors
inline pros::MotorGroup left({1,2,3});
inline pros::MotorGroup right({6,7,8});
inline pros::Motor intake(7,pros::E_MOTOR_GEARSET_06,true);
inline pros::Motor flywheel(8,pros::E_MOTOR_GEARSET_06,false);