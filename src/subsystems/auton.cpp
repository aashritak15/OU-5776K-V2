#include "subsystems/drive.hpp"
#include "subsystems/auton.hpp"
#include "subsystems/odom.hpp"
#include "subsystems/path.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/pistons.hpp"
#include "subsystems/cata.hpp"

#include "globals.hpp"

using namespace okapi;

/*
Auton plan (try to test in 4 days maybe like Friday)
    1. drive moving (ria sugar bear)
    2. intake/cata (aashrita)
    3. flipout -> to touch the bar (aashrita)
*/

void intakeAuton(IntakeState currentIntakeState){
    switch (currentIntakeState) {
    case IntakeState::STOPPED:
      //gradualStop();
      break;
      intakeMotor1.moveVoltage(0);
    case IntakeState::INTAKING:
      intakeMotor1.moveVoltage(12000);
      //intakeMotor2.moveVoltage(12000);
      break;
    case IntakeState::OUTTAKING:
      intakeMotor1.moveVoltage(-12000);
      //intakeMotor2.moveVoltage(-12000);
      break;
  //case IntakeState::HALF:
  }
}



void cataAuton(CataState currentCataState) {
    static CataState currentCataState = CataState::STOPPED;
     switch (currentCataState) {
    case CataState::STOPPED:
      break;
      cataMotor.moveVoltage(0);
    case CataState::CONTINUE:
      cataMotor.moveVoltage(12000);
      break;
}
}

void updateAuton(int side){
    if (side == 1){
      //intake
        turnPID(45, false, 3000);
        pros::delay(100);
        drivetrain(9);
        pros::delay(100);
        turnPID(45, true, 3000);
        pros::delay(100);
        intakeAuton(IntakeState::OUTTAKING);
        pros::delay(50);
        intakeAuton(IntakeState::STOPPED);
        pros::delay(100);
        turnPID(180, true, 3000);
        pros::delay(100);
        drivetrain(7);
        pros::delay(100);
        turnPID(45, true, 3000);
        pros::delay(100);
        autonFlipout.set_value(true);
        pros::delay(100);
        drivetrain(-3);
        pros::delay(100);
        autonFlipout.set_value(false);
        pros::delay(100);
        turnPID(135, false, 3000);
        pros::delay(100);
        drivetrain(8);
        pros::delay(100);
    }

    if (side == 2){
        turnPID(10, false, 3000);
        pros::delay(100);
        drivetrain(11);
        pros::delay(100);
        intakeAuton(IntakeState::INTAKING);
        turnPID(100, true, 3000);
        pros::delay(100);
        drivetrain(6);
        pros::delay(100);
        intakeAuton(IntakeState::OUTTAKING);
        
        drivetrain(2);
        
        pros::delay(100);
        
        pros::delay(100);
        turnPID(180, false, 3000);
        pros::delay(100);
        drivetrain(12);
        pros::delay(100);
        intakeAuton(IntakeState::INTAKING);
        turnPID(190, false, 3000);
        pros::delay(100);
        drivetrain(12);
        intakeAuton(IntakeState::OUTTAKING);
        pros::delay(100);
        turnPID(135, true, 3000);
        pros::delay(100);
        drivetrain(11);
        pros::delay(100);
        intakeAuton(IntakeState::INTAKING);
        pros::delay(100);
        turnPID(180, false, 3000);
        pros::delay(100);
        drivetrain(11);
        pros::delay(100);
        intakeAuton(IntakeState::OUTTAKING);
        pros::delay(100);
        turnPID()
        flapjack1.set_value(true);
        flapjack2.set_value(true);
        pros::delay(100);
        //drive forward and push the lil stuf fin ~ RIA
        flapjack1.set_value(false);
        flapjack2.set_value(false);
        //LSF WE FINISHED AUTON 
    }
}