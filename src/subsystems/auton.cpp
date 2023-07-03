#include "main.h"
#include "subsystems/auton.hpp"
#include "subsystems/drive.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/ports.hpp"
#include "subsystems/odom.hpp"

/*
using namespace okapi;

void updateAuton(int version){
//alliance side auton 
if(version == 1){
    drivetrain(3);
    turnPID(90, true, 300);
    turnPID(25, false, 300);
    //outake 
    drivetrain(0.4);
    intakeMotor1.moveVelocity(600);
    turnPID(90, true, 3000);
    //start raising the lift 
    drivetrain(0.6);
    pros::delay(20);
    drive->getModel()->tank(0,0);
}


//opponent side auton 
else if(version == 2){
    turnPID(290, false, 3000);
    drivetrain(-0.1);
    intakeMotor1.moveVelocity(600);
    turnPID(70, true, 3000);
    drivetrain(0.6);
    //outake 
    turnPID(35, true, 3000);
    //start raising lift 
    drivetrain(0.7);
    pros::delay(20);
    drive->getModel()->tank(0,0);
}

else{
    drive->getModel()->tank(0,0);
}
}
*/