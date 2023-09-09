#include "subsystems/drive.hpp"
#include "subsystems/auton.hpp"
#include "subsystems/odom.hpp"
#include "subsystems/path.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/pistons.hpp"
#include "subsystems/cata.hpp"
#include "subsystems/ports.hpp"
//#include "autoSelect/selection.h"

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
      intakeMotor1.moveVoltage(14000);
      //intakeMotor2.moveVoltage(12000);
      break;
    case IntakeState::OUTTAKING:
      intakeMotor1.moveVoltage(-14000);
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

/*
void skills(int side){
  if(side == 1){

  }
  else if(side == 2){

  }

}
*/

void updateAuton(int side){
    if (side == 1){
      //remove intake stuff if it doesn't work (not a priority)
      //awp focused route red pole
      //blocker.set_value(true);
      drivetrain(-2.7, 1000, 1);

      pros::delay(500);

      left.moveVelocity(-1000);

      pros::delay(300);

      left.moveVelocity(0);
      
      drivetrain(-1.2, 1000, 1);

      turnCounter(35, 1000);

      pros::delay(100);

      drivetrain(1.85, 1000, 1);

      pros::delay(100);
      
      turnClock(70, 1000);

      pros::delay(500);

      drivetrain(0.3, 1000, 1);

      lMech.set_value(true);

      pros::delay(500);

      drivetrain(-0.85, 3000, 2);


      pros::delay(500);

      intakeMotor1.moveVelocity(12000);
      pros::delay(600);

      lMech.set_value(false);

      pros::delay(200);

      intakeMotor1.moveVelocity(0);
      pros::delay(200);
    
      turnCounter(90, 1000);

      drivetrain(1.6, 1000, 1);

      turnCounter(45, 1000);

      drivetrain(3, 2000, 0.5);

      intakeMotor1.moveVelocity(-12000);

    }
    if (side == 2){
      //awp for blue pole 
 //remove intake stuff if it doesn't work (not a priority)
      //awp focused route red pole
      //blocker.set_value(true);
      drivetrain(-2.7, 1000, 1);

      pros::delay(500);

      left.moveVelocity(-1000);

      pros::delay(300);

      left.moveVelocity(0);
      
      drivetrain(-1.2, 1000, 1);

      turnCounter(35, 1000);

      pros::delay(100);

      drivetrain(1.85, 1000, 1);

      pros::delay(100);
      
      turnClock(70, 1000);

      pros::delay(500);

      drivetrain(0.3, 1000, 1);

      lMech.set_value(true);

      pros::delay(500);

      drivetrain(-0.85, 3000, 2);


      pros::delay(500);

      intakeMotor1.moveVelocity(12000);
      pros::delay(600);

      lMech.set_value(false);

      pros::delay(200);

      intakeMotor1.moveVelocity(0);
      pros::delay(200);
    
      turnCounter(90, 1000);

      drivetrain(1.6, 1000, 1);

      turnCounter(45, 1000);

      drivetrain(3, 2000, 0.5);

      intakeMotor1.moveVelocity(-12000);

    }

    if(side == 3){
      //triball focused route (blue pole)
      
      cataMotor.moveVelocity(-14000);
      pros::delay(300);
      
      intakeMotor1.moveVelocity(12000);
      pros::delay(500);

      cataMotor.moveVelocity(0);
      pros::delay(500);
    
      drivetrain(4.88, 3000, 1.25);
      pros::delay(500);

      intakeMotor1.moveVelocity(0);
    //pros::delay(100);
      turnCounter(90, 2000);

      pros::delay(200);


      intakeMotor1.moveVelocity(-13000);
      pros::delay(300);

      intakeMotor1.moveVelocity(0);
/*
      intakeMotor1.moveVelocity(0);
      
      pros::delay(500);
      */
      drivetrain(-1.1, 3000, 0.9);
      pros::delay(100);


      turnClock(90, 3000);
      pros::delay(100);

      drivetrain(0.47, 3000, 1);
      pros::delay(300);

      intakeMotor1.moveVelocity(12000);
      pros::delay(500);

      intakeMotor1.moveVelocity(0);
      pros::delay(300);

      turnCounter(90, 3000);
      pros::delay(100);

      drivetrain(0.47, 3000, 1.5);
      pros::delay(300);

      intakeMotor1.moveVelocity(-12000);

      pros::delay(300);

      intakeMotor1.moveVelocity(0);
      drivetrain(1, 3000, 5);

//third triball
      drivetrain(-1.95, 3000, 1.5);
      pros::delay(100);


      turnClock(130, 3000);
      pros::delay(100);

      drivetrain(0.48, 3000, 1);
      pros::delay(300);

      intakeAuton(IntakeState::INTAKING);
      pros::delay(500);

      intakeMotor1.moveVelocity(0);
      pros::delay(200);

      turnCounter(130, 3000);


      drivetrain(1.4, 3000, 1.5);

      pros::delay(100);

      intakeMotor1.moveVelocity(-12000);
      pros::delay(150);

      drivetrain(1, 3000, 3);
    
      intakeMotor1.moveVelocity(0);
      
      //drivetrain(-1.75, 7000, 1);
      //pros::delay(500);
      
      /*
      turnClock(90, 3000);
      pros::delay(500);

      intakeAuton(IntakeState::INTAKING);
      pros::delay(100);
    */
      
    } 

    if(side == 4){
      //triball focused route (red pole)
      
      
      cataMotor.moveVelocity(-14000);
      pros::delay(300);
      
      intakeMotor1.moveVelocity(12000);
      pros::delay(500);

      cataMotor.moveVelocity(0);
      pros::delay(500);
    
      drivetrain(4.88, 3000, 1);
      pros::delay(500);

      intakeMotor1.moveVelocity(0);
    //pros::delay(100);
      turnClock(90, 2000);


      intakeMotor1.moveVelocity(-13000);
      pros::delay(300);

      intakeMotor1.moveVelocity(0);
/*
      intakeMotor1.moveVelocity(0);
      
      pros::delay(500);
      */
      drivetrain(-1.1, 3000, 0.9);
      pros::delay(100);


      turnCounter(90, 3000);
      pros::delay(100);

      drivetrain(0.48, 3000, 1);

      intakeAuton(IntakeState::INTAKING);
      pros::delay(500);

      intakeMotor1.moveVelocity(0);
      pros::delay(300);

      turnClock(90, 3000);

      drivetrain(0.47, 3000, 1.5);
      pros::delay(300);

      intakeMotor1.moveVelocity(-12000);

      pros::delay(300);

      intakeMotor1.moveVelocity(0);
      drivetrain(1, 3000, 5);

//third triball
      drivetrain(-1.8, 3000, 1.5);
      pros::delay(100);


      turnCounter(127, 3000);
      pros::delay(100);

      drivetrain(0.4, 3000, 1);

      intakeAuton(IntakeState::INTAKING);
      pros::delay(500);

      intakeMotor1.moveVelocity(0);
      pros::delay(200);

      turnClock(130, 3000);


      drivetrain(1.4, 3000, 1.5);

      pros::delay(100);

      intakeMotor1.moveVelocity(-12000);
      pros::delay(150);

      drivetrain(1.2, 3000, 3);
    
      intakeMotor1.moveVelocity(0);
      
      //drivetrain(-1.75, 7000, 1);
      //pros::delay(500);
      
      /*
      turnClock(90, 3000);
      pros::delay(500);

      intakeAuton(IntakeState::INTAKING);
      pros::delay(100);
    */
      
    }
  }

/*
        turnPID(10, false, 3000);
        pros::delay(100);

        drivetrain(11, 7000);
        pros::delay(100);

        intakeAuton(IntakeState::INTAKING);
        turnPID(100, true, 3000);
        pros::delay(100);

        drivetrain(6, 7000);
        pros::delay(100);

        intakeAuton(IntakeState::OUTTAKING);
        drivetrain(2, 7000);
        pros::delay(100);

        turnPID(180, false, 3000);
        pros::delay(100);

        drivetrain(12, 7000);
        pros::delay(100);
        intakeAuton(IntakeState::INTAKING);
        turnPID(190, false, 3000);
        pros::delay(100);
        drivetrain(12, 7000);
        intakeAuton(IntakeState::OUTTAKING);
        pros::delay(100);
        turnPID(135, true, 3000);
        pros::delay(100);
        drivetrain(11, 7000);
        pros::delay(100);
        intakeAuton(IntakeState::INTAKING);
        pros::delay(100);
        turnPID(180, false, 3000);
        pros::delay(100);
        drivetrain(11, 7000);
        pros::delay(100);
        intakeAuton(IntakeState::OUTTAKING);
        pros::delay(100);
        flapjack1.set_value(true);
        //flapjack2.set_value(true);
        pros::delay(100);
        drivetrain(3, 7000);
        flapjack1.set_value(false);
        //flapjack2.set_value(false);
        //LSF WE FINISHED AUTON 

    }
    */

/*
    if (side == 3){
      //awp but other side 
      drivetrain(3, 7000);
      pros::delay(500);
      drivetrain(-0.6, 7000);
      pros::delay(500);
      turnCounter(180, 7000);
      pros::delay(100);
      drivetrain(1, 7000);
      pros::delay(500);
      turnCounter(25, 7000);
      pros::delay(100);
    }
*/