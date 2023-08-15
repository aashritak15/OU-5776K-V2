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

std::shared_ptr<AsyncMotionProfileController> profileController =
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      1.0, // Maximum linear velocity of the Chassis in m/s
      2.0, // Maximum linear acceleration of the Chassis in m/s/s
      10.0 // Maximum linear jerk of the Chassis in m/s/s/s
    })
    .withOutput(drive)
    .buildMotionProfileController();

profileController->generatePath({
  {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
  {1_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
  "A" // Profile name
);

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


/*
void cataAuton(CataState currentCataState) {
    static CataState currentCataState = CataState::STOPPED;
     switch (currentCataState) {
    case CataState::STOPPED:
      break;
      //cataMotor.moveVoltage(0);
    case CataState::CONTINUE:
     // cataMotor.moveVoltage(12000);
      break;
}`
}
*/

void updateAuton(int side){
    if (side == 1){

      /*intakeFlipout.set_value(false);
      pros::delay(10);
      intakeAuton(IntakeState::INTAKING);
      pros::delay(10);
      */
      drivetrain(3, 7000);
      pros::delay(500);
      drivetrain(-0.6, 7000);
      pros::delay(500);
      turnClock(180, 7000);
      drivetrain(1, 7000);
      pros::delay(500);
      turnClock(25, 7000);
      pros::delay(100);
      intakeFlipout.set_value(true);
      
      pros::delay(100);
      drivetrain(-1, 7000);
      /*
      drivetrain(-0.6, 7000);
      turnClock(180, 7000);
      */
      //turnCounter(55, 1000);

      drivetrain(6);    


    }
}
      /*
      //outtaking and pushin in preload 
      intakeAuton(IntakeState::OUTTAKING);
      pros::delay(100);
      //flapjacks too big to use 
      drivetrain(3); 
      pros::delay(100);

      //going to get the matchload 
      drivetrain(-1.5);
      pros::delay(100);
      turnPID(180, true, 3000);
      pros::delay(100);

      //intake matchload 
      intakeAuton(IntakeState::INTAKING);
      pros::delay(100);


      //going to the bar 
      turnPID(90, true, 3000);
      //intake flipout push out 
      drivetrain(6);
      //prolly need to turn just a little bit so the flipout touches the bar 

    }
*/

/*
    if(side == 2){
      //triball focused route 

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
        flapjack1.set_value(true);
        //flapjack2.set_value(true);
        pros::delay(100);
        drivetrain(3);
        flapjack1.set_value(false);
        //flapjack2.set_value(false);
        //LSF WE FINISHED AUTON 

    }
    
    if(side == 3){
      //awp but other side 

    }


}
    
*/