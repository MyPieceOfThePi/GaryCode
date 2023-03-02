#include "main.h"

//method that sets left and right drive power
void setTank(int leftPower, int rightPower){
    left.move_voltage(leftPower);
    right.move_voltage(rightPower);
}

//method called in driver control
void tankDriveControl(){
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    setTank(rightJoystick, leftJoystick);
}