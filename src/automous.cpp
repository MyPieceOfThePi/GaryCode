#include "main.h"
//hi
bool shootT = false;
void onRoller(int b){
	driveTask.suspend();
    setTank(50,50);
    intake = -80;
    pros::delay(200);
    setTank(0,0);
    setTank(-50,-50);
    pros::delay(b);
    intake=0;
    setTank(0,0);
	driveTask.resume();
}
void offRoller(){
    Drive(24);
    driveWait();
    Turn(90);
    turnWait();
    driveTask.suspend();
    onRoller(200);
    driveTask.resume();
}

void fiveDiskRight(){
	flywheelControllerA.setTarget(445);
	intake=127;
	Drive(41,49,113,420);
	driveWait();
	Drive(-5,15.6,90,1500);
	driveWait();
	intake=50;
	Turn(-135);
	turnWait();
	shoot(500,3,200);
	Drive(-5,12,49,800);
	driveWait();
	intake=100;
	Turn(-225);
	turnWait();
	Drive(40,40,117,613);
	driveWait();
	Turn(-160);
	turnWait();
	shoot(520,2,200);
	Turn(-225);
	turnWait();
	Drive(25,37,96,420);
	driveWait();
	Turn(-180);
	turnWait();
	driveTask.suspend();
	onRoller(200);
	driveTask.resume();
}
void shoot(double d,int n, double s){
	for(int i = 0; i<n-1; i++){
		indexer.set_value(true);
		pros::delay(s);
		indexer.set_value(false);
		pros::delay(d);
	}
	indexer.set_value(true);
	pros::delay(s);
	indexer.set_value(false);
}
void leftHalfWinpoint(){
	flywheelController.setTarget(430);
	onRoller(100);
	intake=-127;
	Turn(135+90-360+3);
	turnWait();
	Drive(28,36,42,170);
	driveWait();
	intake=127;
	Drive(20,18,25,140);
	driveWait();
	Turn(135+90+90-360+12);
	turnWait();
	pros::delay(1000);
	shoot(500,3,200);
}

void skills(){
	//Roller and first intaking first disk
	flywheelController.setTarget(370);
    onRoller(0);
	intake=127;
	Turn(135);
	turnWait();
	Drive(29,50,180,593);
	driveWait();
	Turn(90);  
	turnWait();
	onRoller(100);
	Turn(0);
	turnWait();

	//First Volley
	Drive(-40,53,126,584);
	driveWait();
	Turn(8);
	turnWait();
	shoot(450,3,200);
	Drive(-12,24,49,800);
	driveWait();
	Turn(0);
	turnWait();

	//Second cycle
	Turn(-90);
	turnWait();
	intake=127;
	Drive(34,20,28,97);
	driveWait();
	Turn(-30);
	turnWait();
	shoot(300,3,200);

	//Third Cycle
	flywheelController.setTarget(380);
	Turn(-90);
	turnWait();
	Drive(18,28,110,818);
	driveWait();
	Turn(45);
	turnWait();
	Drive(38,53,134,390);
	driveWait();
	Turn(-20);
	turnWait();
	shoot(300,3,200);

	//Fourth Cycle
	Turn(0);
	turnWait();
	Drive(37,20,100,520);
	intake=-127;
	pros::delay(1000);
	intake=127;
	driveWait();
	Drive(-12,28,110,818);
	driveWait();
	Turn(-10);
	turnWait();

	//Fifth Cycle
	shoot(300,3,200);
	Turn(-90);
	turnWait();
	Drive(30,20,100,520);
	intake=-127;
	pros::delay(500);
	intake=127;
	driveWait();
	Drive(-18,28,110,818);
	driveWait();
	Turn(170);
	shoot(300,3,200);

	//Sixth cycle
	Turn(225);
	turnWait();
	Drive(33,53,134,390);
	driveWait();
	Turn(-20);
	turnWait();
	shoot(300,3,200);

	//Seventh cycle
}