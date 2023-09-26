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


void updateSkills(int path){
    if (path == 1){
      
      cataMotor.moveVelocity(-14000);
      pros::delay(300);
      
      intakeSkills(IntakeState::INTAKING);
      pros::delay(700);

      cataMotor.moveVelocity(0);
      pros::delay(500);

      intakeMotor1.moveVelocity(0);
    
      drivetrain(5.3, 3000, 1.25);

      pros::delay(500);
    //pros::delay(100);


      turnCounter(90, 2000);

      pros::delay(200);


      intakeSkills(IntakeState::OUTTAKING);

      pros::delay(400);

      intakeMotor1.moveVelocity(0);

      pros::delay(100);
      
      flapjack1.set_value(true);

      drivetrain(1, 1000, 2);

      flapjack1.set_value(false);

      pros::delay(100);

      drivetrain(-1, 1000, 1);
      
      pros::delay(100);

      turnCounter(90, 3000);
       //imuInnit();

      pros::delay(200);

      drivetrain(2.45, 3000, 1);

      pros::delay(400);

      
      //imuInnit();
      
      turnCounter(100, 4000);
      // imuInnit();

      pros::delay(300); 

      lMech.set_value(true);

      cataMotor.moveVelocity(-14000);

      drivetrain(-3.25, 3000, 0.95); 

      pros::delay(32000);

      cataMotor.moveVelocity(0);

      lMech.set_value(false);

      turnClock(5, 1000);

      pros::delay(100);

      drivetrain(4.5, 3000, 2);

      pros::delay(100);

      drivetrain(-0.75, 1000, 1);

      pros::delay(100);

      flapjack1.set_value(true);

      pros::delay(100);

      drivetrain(10, 4000, 5);


    }

 else if (path == 2){
      blocker.set_value(true);
      drivetrain(-2.7, 1000, 1);

      pros::delay(500);

      left.moveVelocity(-1000);

      pros::delay(300);
      

      left.moveVelocity(0);

      drivetrain(-1.8, 1000, 2);

      left.moveVelocity(2000);

      pros::delay(660);
      
      blocker.set_value(false);

      drivetrain(-1, 1000, 1);

      pros::delay(100);

      lMech.set_value(true);

      cataMotor.moveVelocity(-14000);

      pros::delay(10000);

      cataMotor.moveVelocity(0);

      lMech.set_value(false);

      pros::delay(100);

      drivetrain(1.2, 1000, 1);

      pros::delay(100);
      
      intakeSkills(IntakeState::INTAKING);

      pros::delay(100);

      drivetrain(3.2, 2000, 0.75);

      pros::delay(100);

      turnClock(18, 1000);

      drivetrain(0.8, 2000, 0.6);

      intakeMotor1.moveVelocity(0);

      drivetrain(0.5, 2000, 1.5);
      
      pros::delay(100);

      drivetrain(-1, 2000, 1);

       pros::delay(100);
      
      drivetrain(7, 2000, 5);

      turnCounter(20, 3000);

      flapjack1.set_value(true);

      drivetrain(3, 2000, 2);


      

 }


}
