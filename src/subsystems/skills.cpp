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
      pros::delay(500);

      cataMotor.moveVelocity(0);
      pros::delay(500);

      intakeMotor1.moveVelocity(0);
    
      drivetrain(4.8, 3000, 1.25);

      pros::delay(500);
    //pros::delay(100);
      turnCounter(90, 2000);

      pros::delay(200);


      intakeSkills(IntakeState::OUTTAKING);

      pros::delay(300);

      intakeMotor1.moveVelocity(0);
      
      pros::delay(500);
      
      drivetrain(-1, 3000, 0.9);
      pros::delay(100);

      turnClock(90, 3000);
      pros::delay(100);

      drivetrain(0.47, 3000, 1);
      pros::delay(300);

      intakeSkills(IntakeState::INTAKING);
      pros::delay(500);

      intakeMotor1.moveVelocity(0);
      pros::delay(300);

      turnCounter(90, 3000);
      pros::delay(100);

      drivetrain(0.47, 3000, 1.5);
      pros::delay(300);

      intakeSkills(IntakeState::OUTTAKING);

      pros::delay(300);

      intakeMotor1.moveVelocity(0);
      drivetrain(1, 3000, 5);

//third triball
      drivetrain(-1.7, 3000, 1.5);
      pros::delay(100);


      turnClock(130, 3000);
      pros::delay(100);

      drivetrain(0.5, 3000, 1);
      pros::delay(300);

      intakeSkills(IntakeState::INTAKING);
      pros::delay(500);

      intakeMotor1.moveVelocity(0);
      pros::delay(200);

      turnCounter(130, 3000);

      drivetrain(1.4, 3000, 1.5);

      pros::delay(100);

      intakeSkills(IntakeState::OUTTAKING);
      pros::delay(150);

      drivetrain(1, 3000, 3);
    
      intakeMotor1.moveVelocity(0);

      //main testing 

      pros::delay(100);

      drivetrain(-1, 1000, 1);
      
      pros::delay(100);

      turnCounter(90, 3000);

      pros::delay(100);

      drivetrain(2.3, 3000, 1);

      pros::delay(100);

      turnCounter(105, 3000);

      pros::delay(100);

      drivetrain(-2.6, 3000, 1); 

      pros::delay(100);

      turnCounter(15, 1000);

      pros::delay(100);

      //drivetrain(-0.5, 3000, 0.5);

      lMech.set_value(true);

      cataMotor.moveVelocity(-14000);

      pros::delay(30000);

      cataMotor.moveVelocity(0);

      pros::delay(20);

      turnCounter(10, 1000);

      pros::delay(40);

      drivetrain(2.5, 3000, 1);

  

      pros::delay(100);

      //getting over barrier 

      drivetrain(2, 2000, 1);

      pros::delay(100);

      turnCounter(15, 1500);

      pros::delay(100);

      drivetrain(4, 3000, 2);

      pros::delay(100);

      drivetrain(-0.5, 1000, 1);

      pros::delay(100);

      drivetrain(4, 4000, 5);

      pros::delay(100);

      flapjack1.set_value(true);

      drivetrain(5, 3000, 3);
      
      
            

    }

}
