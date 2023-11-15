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
//close auton

      drivetrain(-2, 2000, 0.8);

       pros::delay(100);

      left.moveVelocity(-2000);
      
      pros::delay(300);

       left.moveVelocity(0);

      drivetrain(-1, 1000, 1);

      drivetrain(1.2, 1000, 0.8);

       left.moveVelocity(3000);

      intakeMotor1.moveVelocity(0);

      pros::delay(180);

      left.moveVelocity(0);


       drivetrain(0.2, 1000, 2);

       flapjack1.set_value(true);


       left.moveVelocity(4000);

       pros::delay(200);

       left.moveVelocity(0);


       left.moveVelocity(7000);

       pros::delay(300);

       left.moveVelocity(0);

        pros::delay(100);

       flapjack1.set_value(false);

       pros::delay(200);

       turnClock(45, 2000);

       pros::delay(200);


       drivetrain(1.4, 3000, 0.7);

        turnCounter(43, 2000);

        intakeAuton(IntakeState::OUTTAKING);

        drivetrain(3.5, 2000, 0.6);

         pros::delay(400);

         intakeAuton(IntakeState::STOPPED);




                       







      /*
      drivetrain(-4, 3000, 3);

      pros::delay(100);

       drivetrain(0.8, 3000, 1);

       pros::delay(100);

       intakeMotor1.moveVelocity(0);

       turnCounter(125, 2000);

       pros::delay(100);

       drivetrain(2.9, 3000, 0.7);

       pros::delay(100);

       turnClock(35, 1000);

        intakeMotor1.moveVelocity(-14000);

       drivetrain(2.1, 3000, 0.3);

       pros::delay(100);

       drivetrain(0.2, 1000, 0.1);

        intakeMotor1.moveVelocity(0);

        drivetrain(0.1, 1000, 1);

      */


      //remove intake stuff if it doesn't work (not a priority)
      //awp red pole, blue goal
      //awp blue pole, red goal

     /*drivetrain(0.89, 4000, 0.7);

      intakeMotor1.moveVelocity(12000);
      

      right.moveVelocity(4000);

       intakeMotor1.moveVelocity(0);

      pros::delay(180);

      right.moveVelocity(0);


       drivetrain(0.2, 1000, 2);

      flapjack1.set_value(true);


       right.moveVelocity(7000);

       pros::delay(200);

       right.moveVelocity(0);

       drivetrain(0.6, 4000, 1);

       right.moveVelocity(7000);

       pros::delay(300);

       right.moveVelocity(0);

       pros::delay(200);

       flapjack1.set_value(false);

       pros::delay(200);

       turnCounter(25, 2000);

       pros::delay(100);

       drivetrain(1.4, 2000, 1.5);

       right.moveVelocity(7000);

       pros::delay(300);

       right.moveVelocity(0);

       drivetrain(-0.5, 2000, 1.5);

       intakeMotor1.moveVelocity(-12000);

       pros::delay(100);

          intakeMotor1.moveVelocity(0);

       drivetrain(1, 3000, 4);

        pros::delay(100);
  

       drivetrain(-0.8, 3000, 1);

       pros::delay(100);

      right.moveVelocity(-7000);

       pros::delay(400);

       right.moveVelocity(0);

       pros::delay(200);

       drivetrain(-1.7, 5000, 0.7);

       left.moveVelocity(-7000);

       pros::delay(400);

       left.moveVelocity(0);


       drivetrain(-3.2, 5000, 0.7);

*/





    }
    if (side == 2){
      //awp blue pole, blue goal
      //awp red pole, red goal
      
      cataMotor.moveVoltage(-12000);

      pros::delay(200);

      cataMotor.moveVoltage(0);

      intakeMotor1.moveVoltage(-14000);

      pros::delay(200);

      drivetrain(-1.7, 3000, 0.8);


      pros::delay(50);

  
  

      turnClock(180, 2000);



       intakeMotor1.moveVoltage(0);


          pros::delay(50);
       
      drivetrain(1, 4000, 0.7);
      
      left.moveVelocity(3000);

      pros::delay(180);

      left.moveVelocity(0);


      // drivetrain(0.2, 1000, 2);

       flapjack1.set_value(true);


       left.moveVelocity(4000);

       pros::delay(320);

       left.moveVelocity(0);

       drivetrain(0.6, 4000, 1);

       left.moveVelocity(7000);

       pros::delay(300);

       left.moveVelocity(0);

        pros::delay(100);

       flapjack1.set_value(false);

       pros::delay(50);

       turnClock(27, 2000);

       pros::delay(50);


       drivetrain(1.4, 2000, 1.5);

       left.moveVelocity(7000);

       pros::delay(300);

       left.moveVelocity(0);


       drivetrain(-0.5, 2000, 1.5);   
       

        intakeMotor1.moveVoltage(14000);

       drivetrain(1, 3000, 3); 

      pros::delay(50);

       drivetrain(-0.85, 3000, 0.8);

       pros::delay(20);

       turnClock(25, 1000);

       pros::delay(20);

       drivetrain(1.1, 3000, 3);

      pros::delay(20);

       drivetrain(-0.9, 3000, 0.8);

        intakeMotor1.moveVoltage(0);
       
       turnCounter(90, 2000);

       pros::delay(50);

       drivetrain(4, 3000, 0.8);

       pros::delay(50);

       flapjack1.set_value(true);

       drivetrain(0.9, 1000, 1);

       


       /*

       turnCounter(125, 2000);

       pros::delay(100);

       drivetrain(2.9, 3000, 0.7);

       pros::delay(100);

       turnClock(35, 1000);

        intakeMotor1.moveVelocity(-14000);

       drivetrain(2.1, 3000, 0.3);

       pros::delay(100);

       drivetrain(0.2, 1000, 0.1);

        intakeMotor1.moveVelocity(0);

        drivetrain(0.1, 1000, 1);
        */
      

      /*
      drivetrain(1.2, 1000, 2);
      
      

      pros::delay(100);

      turnClock(45, 1000);

      pros::delay(100);

      drivetrain(1.65, 1000, 1);

      pros::delay(100);

      
      turnCounter(83, 1000);

      pros::delay(500);

      drivetrain(0.9, 3000, 0.75);

      lMech.set_value(true);

      pros::delay(500);

      drivetrain(-0.95, 3000, 2);

      pros::delay(500);

      lMech.set_value(false);

       pros::delay(600);

      intakeMotor1.moveVelocity(12000);

      drivetrain(0.7, 3000, 0.9);


      pros::delay(700);

      intakeMotor1.moveVelocity(0);
      pros::delay(200);
    
      turnClock(90, 1000);

      drivetrain(1.7, 1000, 1);

      turnClock(45, 1000);

      drivetrain(3.5, 2000, 0.5);

      intakeMotor1.moveVelocity(-12000);
      */

    }

    if(side == 3){
      //triball focused route, blue pole, red goal
      //triball focused route, red pole, blue goal
//       cataMotor.moveVelocity(-14000);
//       pros::delay(300);
      
//       intakeAuton(IntakeState::INTAKING);
//       pros::delay(200);

//       cataMotor.moveVelocity(0);
//       pros::delay(500);

   
    
//       drivetrain(4.85, 3000, 1.25);

//          intakeMotor1.moveVelocity(0);

//       pros::delay(500);
//     //pros::delay(100);


//       turnCounter(90, 2000);

//        imuInnit();

//       pros::delay(200);


//       intakeAuton(IntakeState::OUTTAKING);

//        pros::delay(100);
      
//       drivetrain(-1, 3000, 0.9);
//       pros::delay(100);

//       intakeMotor1.moveVelocity(0);

//       turnClock(90, 3000);

//        imuInnit();

//       pros::delay(100);

//       intakeAuton(IntakeState::INTAKING);
//       //pros::delay(700);

//       drivetrain(0.47, 3000, 1);
//       pros::delay(700);


//       intakeMotor1.moveVelocity(0);
//       pros::delay(300);

//       turnCounter(90, 3000);

//        imuInnit();

//       pros::delay(100);

//       drivetrain(0.47, 3000, 1.5);
//       pros::delay(300);

//       intakeAuton(IntakeState::OUTTAKING);

//       pros::delay(300);

//       intakeMotor1.moveVelocity(0);

  
//       drivetrain(1, 3000, 5);

//       pros::delay(200);

// //third triball
//       drivetrain(-1.5, 3000, 1.5);
//       pros::delay(100);


//       turnClock(130, 3000);

//       // imuInnit();
//       pros::delay(100);

//       intakeAuton(IntakeState::INTAKING);
//       ;pros::delay(700);

//       drivetrain(0.6, 3000, 1);
//       pros::delay(700);


//       intakeMotor1.moveVelocity(0);
//       pros::delay(200);

//       turnCounter(130, 3000);
//       // imuInnit();

//       drivetrain(1.4, 3000, 1.5);

//       pros::delay(100);

//       intakeAuton(IntakeState::OUTTAKING);
//       pros::delay(150);

//       flapjack1.set_value(true);

//       drivetrain(1, 3000, 3);
    
//       intakeMotor1.moveVelocity(0);

//       flapjack1.set_value(false);

  
      
//     } 

//     if(side == 4){
//       //triball focused route, red pole, red goal
//       //triball focused route, blue pole, blue goal
      
      
//       //cataMotor.moveVelocity(-14000);
//       //pros::delay(300);

//        intakeMotor1.moveVelocity(-14000);

//       pros::delay(100);
    
//       drivetrain(4.4, 3500, 1.5);

//       pros::delay(100);
  
//       turnClock(90, 2000);

//       pros::delay(50);

//       drivetrain(0.5, 1000, 1);

//       pros::delay(100);

//       intakeMotor1.moveVelocity(14000);

//       pros::delay(100);

// //second triball
//       drivetrain(-1.35, 1000, 1);

//       pros::delay(100);

//       intakeMotor1.moveVelocity(0);

//          pros::delay(100);

//       turnCounter(95, 2000);

//          pros::delay(100);

//       intakeMotor1.moveVelocity(-14000);

//          pros::delay(100);

//       drivetrain(0.7, 1000, 1);

//          pros::delay(100);

//       intakeMotor1.moveVelocity(0);

//          pros::delay(100);

//       turnClock(90, 2000);

//       pros::delay(100);

//      flapjack1.set_value(true);

//       pros::delay(100);

//       drivetrain(2.3, 1000, 2);

//        pros::delay(100);

//        flapjack1.set_value(false);

//       drivetrain(-0.5, 1000, 1);

//       pros::delay(100);

//       pros::delay(100);

//       turnCounter(180, 1000);

//       pros::delay(100);

//       drivetrain(2.3, 1000, 1.5);

//       pros::delay(100);

//        intakeMotor1.moveVelocity(-14000);

//       pros::delay(100);

//       drivetrain(0.5, 1000, 1.5);

//        pros::delay(100);

//        turnClock(180, 1000);

//           pros::delay(100);

//       drivetrain(3, 2000, 2);

//       intakeMotor1.moveVelocity(14000);

//       //fourth triball

//       turnClock(135, 1000);



  flapjack1.set_value(true);
  pros::delay(10);
  flapjack1.set_value(false);
  pros::delay(100);

  intakeAuton(IntakeState::INTAKING); 
  drivetrain(2.6, 1300, 1.5);
  turnClock(135, 500);
  pros::delay(100);

  flapjack1.set_value(true);
  intakeAuton(IntakeState::STOPPED); 
  drivetrain(2.2, 1300, 1.5);
  intakeAuton(IntakeState::OUTTAKING); 
  pros::delay(400);

  intakeAuton(IntakeState::STOPPED); 
  drivetrain(-1.3, 800, 1);
  flapjack1.set_value(false);
  pros::delay(50);
  
  turnClock(135, 450);
  intakeAuton(IntakeState::INTAKING);
  pros::delay(20);
  drivetrain(1, 450, 1.5);
  pros::delay(200);

  turnCounter(90, 200);
  drivetrain(1, 450, 1.5);
  pros::delay(10);
  intakeAuton(IntakeState::OUTTAKING);
  pros::delay(100);
  turnClock(45, 100);
  drivetrain(1, 450, 1.5);
  pros::delay(10);
  drivetrain(.2, 100, 1.5);
  turnClock(90, 200);
  pros::delay(10);
  
  intakeAuton(IntakeState::INTAKING);
  drivetrain(2, 1000, 3);
  pros::delay(10);
  intakeAuton(IntakeState::STOPPED);
  pros::delay(20);

  drivetrain(-0.3, 500, .5);
  drivetrain(-1.7, 2000, 3);
  turnClock(135, 450);
  flapjack1.set_value(true);
  intakeAuton(IntakeState::OUTTAKING);
  drivetrain(1, 300, 1);
  pros::delay(100);

  flapjack1.set_value(false);
  turnCounter(45,200);
  drivetrain(1, 400, 3);
  pros::delay(10);
  drivetrain(-.3, 200, 3);
  pros::delay(20);
  drivetrain(.8, 300, 3);
  pros::delay(20);
  








  


















    







/*
//third triball
      drivetrain(-1.5, 3000, 1.5);
      pros::delay(100);

      intakeAuton(IntakeState::INTAKING); 


      turnCounter(123, 1000);

      // imuInnit();

      //pros::delay(700);

      drivetrain(0.8, 3000, 1);
      pros::delay(100);
 

      intakeMotor1.moveVelocity(0);
      pros::delay(100);

      turnClock(123, 4000);

      pros::delay(100);

      drivetrain(1, 3000, 1.5);

      pros::delay(100);

      intakeAuton(IntakeState::OUTTAKING);
      pros::delay(150);

      flapjack1.set_value(true);

      drivetrain(1.5, 3000, 2);

      pros::delay(100);
    
      intakeMotor1.moveVelocity(0);

      flapjack1.set_value(false);

      drivetrain(1, 3000, 2);

      
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