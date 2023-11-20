#include "subsystems/drive.hpp"
#include "subsystems/auton.hpp"
#include "subsystems/odom.hpp"
#include "subsystems/path.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/pistons.hpp"
#include "subsystems/cata.hpp"
#include "subsystems/ports.hpp"
#include "subsystems/skills.hpp"
#include "globals.hpp"

using namespace okapi;


void intakeSkills(IntakeState currentIntakeState){
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

void gradualMax(int ms, int back){
  int timer = 0;

  int speed = 500 * back;
  int val = 100;
  //int newSpeed = 0;

  
 
  while (timer < ms){
    
   

     left.moveVoltage(speed);
     right.moveVoltage(speed);
    
    val *=1.2;
    speed += val;
    
    timer += 10;
    pros::delay(10);
}
     left.moveVoltage(0);
     right.moveVoltage(0);

}


void updateSkills(int path){
    if (path == 1){


/*

______________________________________________________________________________

going to matchload position

______________________________________________________________________________

*/



       drivetrain(0.8, 1000, 1);

      turnLEFTONLY(107, 1000);

      pros::delay(100);

      drivetrain(1, 2000, 0.3);

/*

______________________________________________________________________________

matchloading 

______________________________________________________________________________

*/

      cataMotor.moveVoltage(10000);

      pros::delay(2700);

      cataMotor.moveVoltage(0);
      
       pros::delay(50);

/*

______________________________________________________________________________

going to other side 

______________________________________________________________________________

*/

    drivetrain(0.5, 1000, 0.3);

      turnClock(60, 1000);

       pros::delay(50);

      drivetrain(-1.5, 1000, 1);

       pros::delay(20);

       turnCounter(45, 500);

      pros::delay(100);



      cataMotor.moveVoltage(5400);

      pros::delay(20);

       drivetrain(-6.6, 4000, 0.5);

         pros::delay(200);

   cataMotor.moveVoltage(0);

       intakeSkills(IntakeState::INTAKING);

         pros::delay(100); 

  /*

______________________________________________________________________________

 scoring from side 

______________________________________________________________________________

*/


       turnLeftTime(900, -500, -200);


       intakeSkills(IntakeState::OUTTAKING);
       //right.moveVoltage(-10000);
       //left.moveVoltage(-10000);

      drivetrain(-2, 1000, 1);

        pros::delay(20);

      drivetrain(1, 1000, 1);

         pros::delay(20);

      drivetrain(-2, 1000, 1);




    /*

______________________________________________________________________________

 going to the front 

______________________________________________________________________________

*/


      drivetrain(0.7, 500, 1);


       turnClock(90, 1000);  

       pros::delay(20);

       drivetrain(2.4, 1000, 1);

       flapjack1.set_value(true);

       pros::delay(100);
       
       
       intakeSkills(IntakeState::INTAKING);

       turnRightTime(1800, 300, 100);

       pros::delay(100);

       drivetrain(2, 1000, 2);
       
        intakeSkills(IntakeState::OUTTAKING);

       pros::delay(100);

       flapjack1.set_value(false);

       pros::delay(100);

       drivetrain(-2, 3000, 0.9);

       pros::delay(100);

       flapjack1.set_value(true);

       drivetrain(2.4, 3000, 1.2);

       pros::delay(100);

       flapjack1.set_value(false);

       drivetrain(-2.5, 3000, 1);

       pros::delay(100);

       turnCounter(90, 1000);

       pros::delay(100);

       drivetrain(2.4, 1000, 1);

       pros::delay(100);

       turnClock(120, 1000);

       pros::delay(100);

       flapjack1.set_value(true);

       pros::delay(100);

       drivetrain(3, 3000, 0.75);

       pros::delay(100);

       drivetrain(-2, 3000, 1);

       pros::delay(100);

       drivetrain(2.5, 3000, 1.5);

       pros::delay(100);

       drivetrain(-0.5, 200, 1);

       flapjack1.set_value(false);


       
/*


      drivetrain(0.4, 500, 0.8);

      pros::delay(100);

       turnLeftTime(150);

      cataMotor.moveVoltage(9500);

      pros::delay(300);

      cataMotor.moveVoltage(0);

       pros::delay(100);


       drivetrain(-0.5, 1000, 1);

       pros::delay(100);

       turnRightTime(150);


      pros::delay(100);

      drivetrain(-1.8, 3000, 0.75);

       pros::delay(100);

       drivetrain(-4.5, 3000, 0.5);
         pros::delay(100);


      //intakeSkills(IntakeState::INTAKING);

   

    //far side awp 

      drivetrain(-.8, 2000, 0.8);
 
      turnClock(180, 700);


      /**/



      /*

       drivetrain(0.9, 2000, 0.8);

      intakeSkills(IntakeState::INTAKING);
      
      //left.moveVelocity(3000);

      pros::delay(100);

      turnCounter(45, 500);

      pros::delay(50);

      flapjack1.set_value(true);

       drivetrain(1, 2000, 0.8);

       turnCounter(75, 500);

       pros::delay(20);

       flapjack1.set_value(false);

       pros::delay(50);

      

    

       intakeSkills(IntakeState::OUTTAKING);

       

       drivetrain(2, 1000, 0.8);
       pros::delay(20);


       

       drivetrain(-1, 500, 1);
       pros::delay(100);

        drivetrain(1.7, 1000, 0.8);
         pros::delay(100);

      drivetrain(-0.6, 1000, 0.8);
       pros::delay(20);

       intakeSkills(IntakeState::STOPPED);


       turnCounter(90, 1000);

       drivetrain(3.2, 1000, 0.8);

       turnClock(90, 1000);

       intakeSkills(IntakeState::INTAKING);

        flapjack1.set_value(true);

         pros::delay(100);

      drivetrain(0.75, 1000, 0.8);

         pros::delay(100);

      turnClock(60, 1000);

      drivetrain(3.5, 2000, 1.5);

      intakeSkills(IntakeState::OUTTAKING);

      drivetrain(-1.3, 500, 1);
       pros::delay(100);

      drivetrain(1.5, 1000, 0.8);
         pros::delay(100);

    flapjack1.set_value(false);

      drivetrain(-2.2, 500, 1);

       turnCounter(90, 1000);

       drivetrain(2, 1000, 0.8);

       turnClock(140, 1000);

       drivetrain(2.5, 1000, 0.8);

*/





        



      


/*
       drivetrain(1.5, 1200, 1);

       turnCounter(30,800);

       intakeSkills(IntakeState::OUTTAKING);

       drivetrain(1.5, 1200, 1);

       pros::delay(20);

       
       pros::delay(20);
       drivetrain(1, 500, 1);
       pros::delay(20);

       drivetrain(-1.3, 1000, 0.8);
       pros::delay(20);
 


       


     */  


      
/*

      turnCounter(30,2000);
      pros::delay(200);

      drivetrain(-3.2, 2000, 1);
      pros::delay(200);

      drivetrain(1, 500, 1);
      pros::delay(20);
      drivetrain(-2, 1000, 0.8);
      pros::delay(20);
      drivetrain(1, 500, 1);
      pros::delay(20);

      turnCounter(90, 400);
      intakeSkills(IntakeState::INTAKING);
      pros::delay(20);
      drivetrain(1.5, 1000, 1);

      turnClock(90, 400);

      flapjack1.set_value(true);
      drivetrain(0.5, 500, 1);
      pros::delay(20);
      turnClock(45, 200);


// first push
      drivetrain(4, 500, 1);
      pros::delay(20);
      intakeSkills(IntakeState::OUTTAKING);
      pros::delay(20);
      drivetrain(-1, 1000, 1);
      pros::delay(20);
      drivetrain(2, 700, .85);
      flapjack1.set_value(false);

      pros::delay(20);
      drivetrain(-2, 1000, 1);

      turnCounter(90, 400);
      intakeSkills(IntakeState::INTAKING);
      pros::delay(20);
      drivetrain(2, 1200, 1);

      turnClock(120, 600);

// second push
      flapjack1.set_value(true);
      drivetrain(4, 500, 1);
      pros::delay(20);
      intakeSkills(IntakeState::OUTTAKING);
      pros::delay(20);
      drivetrain(-1, 1000, 1);
      pros::delay(20);
      drivetrain(2, 700, .85);
      flapjack1.set_value(false);
      pros::delay(20);
      intakeSkills(IntakeState::STOPPED);

      pros::delay(200);
*/

    }
    else if(path == 2){

      /*
______________________________________________________________________________
going to matchload position
______________________________________________________________________________
*/

       drivetrain(0.8, 1000, 1);

      turnLEFTONLY(107, 1000);

      pros::delay(100);

      drivetrain(1, 2000, 0.3);

/*
______________________________________________________________________________
matchloading 
______________________________________________________________________________
*/

cataMotor.moveVoltage(9000);
pros::delay(2000);

cataMotor.moveVoltage(0);

pros::delay(50);

/*
______________________________________________________________________________
going to other side 
______________________________________________________________________________
*/

    drivetrain(0.5, 2000, 0.3);

      turnClock(60, 2000);

       pros::delay(50);

     drivetrain(-1.7, 2000, 0.3);

		turnCounter(35, 2000);

      pros::delay(100);

      cataMotor.moveVoltage(4000);

      pros::delay(100);

	drivetrain(-6.6, 3000, 0.5);
         pros::delay(100);

   cataMotor.moveVoltage(0);

       intakeSkills(IntakeState::INTAKING);

         pros::delay(100); 

  /*
______________________________________________________________________________
 scoring from side 
______________________________________________________________________________
*/


       turnLeftTime(900, -400, -200);

       intakeSkills(IntakeState::OUTTAKING);
			drivetrain(-2, 1000, 2);
       pros::delay(100);




      drivetrain(0.5, 500, 1);


       turnClock(90, 1000);  

       pros::delay(20);

       drivetrain(2.4, 1000, 1);

       flapjack1.set_value(true);

pros::delay(100);

drivetrain(2, 1000, 2);

        intakeSkills(IntakeState::OUTTAKING);
        flapjack1.set_value(true);
        drivetrain(2.4, 3000, 1.2);

       pros::delay(100);
      drivetrain(2, 1000, 1);

       pros::delay(100);

      drivetrain(2.5, 3000, 1.5);

       pros::delay(100);



    }
}

      