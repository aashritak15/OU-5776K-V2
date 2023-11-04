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
      pros::delay(30000);
      cataMotor.moveVelocity(0);
      pros::delay(100);

      turnClock(20, 1000);
      pros::delay(20);
      

      drivetrain(-6.5,3000,1);
      pros::delay(100);

      turnCounter(30,200);
      pros::delay(20);

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


    }
    else if(path == 2){

    }
}

      