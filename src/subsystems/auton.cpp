#include "subsystems/drive.hpp"
#include "subsystems/auton.hpp"
#include "subsystems/odo.hpp"
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
      intakeMotor1.moveVoltage(-14000);
      //intakeMotor2.moveVoltage(12000);
      break;
    case IntakeState::OUTTAKING:
      intakeMotor1.moveVoltage(14000);
      //intakeMotor2.moveVoltage(-12000);
      break;
  //case IntakeState::HALF:

  }
}




void updateAuton(int side){
  if(side == 1){
     /*
  ______________________________________________________________________________________________

    Close Side AWP 
  ______________________________________________________________________________________________

*/

  

  



  }
  else if(side == 2){
    /*
  ______________________________________________________________________________________________

    Far Side AWP
  ______________________________________________________________________________________________

*/
  

  }
  else if(side == 3){
    /*
  ______________________________________________________________________________________________

    Far Side Tri Ball Focus 
  ______________________________________________________________________________________________

*/

  

  
  }
}
