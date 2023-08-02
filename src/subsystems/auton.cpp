#include "subsystems/drive.hpp"
#include "subsystems/auton.hpp"
#include "subsystems/odom.hpp"
#include "subsystems/path.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/pistons.hpp"

#include "globals.hpp"

using namespace okapi;

/*
Auton plan (try to test in 4 days maybe like Friday)
    1. drive moving (ria sugar bear)
    2. intake/cata (aashrita)
    3. flipout -> to touch the bar (aashrita)
*/

void updateAuton(int side){
    if (side == 1){
        
        turnPID(90, false, 3000);
        pros::delay(100);
        drivetrain(0.75);
        pros::delay(100);
        turnPID(45, false, 3000);
        pros::delay(100);
        autonFlipout.set_value(true);
        drivetrain(-0.75);
        pros::delay(100);
        previousIntakeState = currentIntakeState;
        currentIntakeState = IntakeState::STOPPED;
        pros::delay(100);
        turnPID(135, true, 3000);
        pros::delay(100);
        drivetrain(0.7);
        pros::delay(100);
        turnPID(90, true, 3000);
        pros::delay(100);
        drivetrain(2);
        pros::delay(100);
        previousIntakeState = currentIntakeState;
        currentIntakeState = IntakeState::STOPPED;
        turnPID(135, true, 3000);
        pros::delay(100);
        drivetrain(4.2);

    }

    if (side == 2){
        drivetrain(-4);
        
    }
}