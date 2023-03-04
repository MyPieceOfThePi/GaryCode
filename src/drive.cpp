#include "main.h"
bool flybool = true;
int shotsFired = 0;
int APresses = 0;
//method that sets left and right drive power
void setTank(int leftPower, int rightPower){
    l1=leftPower;
    l2=leftPower;
    l3=leftPower;
    r1=rightPower;
    r2=rightPower;
    r3=rightPower;
}

//method called in driver control
void tankDriveControl(){
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    setTank(leftJoystick, rightJoystick);
}

//method that controls the other subsytems
void flywheelTaskF(){
    while(true){
        flywheel = flywheelController.compute(flywheel.get_actual_velocity());
        pros::screen::print(TEXT_MEDIUM,3,"%f",flywheelEMA.compute(flywheel.get_actual_velocity()));
        pros::delay(10);
    }
}

void subsystemControl(){
    int shift = -((int(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))*2)-1);
    bool shiftB = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    int intake_ = int(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));
    bool newFlywheel = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);
    bool flywheel_ = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    bool longRange = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    bool A = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);
    APresses += int(A);
    if(newFlywheel&&!(flywheel_&&shiftB)&&!(longRange&&newFlywheel)){
        flybool=!flybool;
    }
    if(longRange){  
        flywheelController.setTarget((360)+shotsFired*flybool);
    }else{
        flywheelController.setTarget((370+shotsFired)*flybool);
    }
    intake=intake_*shift*127;
    if(newFlywheel&&shiftB||longRange&&newFlywheel){
        shotsFired++;
    }
    if(APresses>5){
        expansion.set_value(true);
    }
    pros::screen::print(TEXT_MEDIUM,7,"%f",APresses);
    flywheel = flywheelController.compute(flywheel.get_actual_velocity());
    tankDriveControl();
    indexer.set_value((flywheel_&&shiftB)||(longRange&&flywheel_));
}