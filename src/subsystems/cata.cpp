#include "subsystems/cata.hpp"
#include "subsystems/ports.hpp"
#include "globals.hpp"
#include "subsystems/odo.hpp"
#include "subsystems/drive.hpp"



Motor cataMotor(cataMotorPort, true, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

using namespace okapi;





ControllerButton cataHighButton = ControllerButton(ControllerDigital::down);
ControllerButton cataMedButton = ControllerButton(ControllerDigital::up);
ControllerButton cataLowButton = ControllerButton(ControllerDigital::left);

void cataInit() { 
  cataMotor.setBrakeMode(AbstractMotor::brakeMode::coast); 
  //intakeMotor2.setBrakeMode(AbstractMotor::brakeMode::hold); 
  }




void updateCata() {


  static CataState currentCataState = CataState::STOPPED;
  //static IntakeState previousIntakeState = IntakeState::STOPPED;



  if (cataHighButton.changedToPressed()) {
    if (currentCataState == CataState::HI) {
      //previousIntakeState = currentIntakeState;
      currentCataState = CataState::STOPPED;
    } else {
      //previousIntakeState = currentIntakeState;
      currentCataState = CataState::HI;
    }
  } 

  if (cataMedButton.changedToPressed()) {
    if (currentCataState == CataState::MED) {
      //previousIntakeState = currentIntakeState;
      currentCataState = CataState::STOPPED;
    } else {
      //previousIntakeState = currentIntakeState;
      currentCataState = CataState::MED;
    }
  } 

  if (cataLowButton.changedToPressed()) {
    if (currentCataState == CataState::LO) {
      //previousIntakeState = currentIntakeState;
      currentCataState = CataState::STOPPED;
    } else {
      //previousIntakeState = currentIntakeState;
      currentCataState = CataState::LO;
    }
  } 
  

  switch (currentCataState) {
    case CataState::STOPPED:
      cataMotor.moveVoltage(0);
      break;
    case CataState::HI:
      cataMotor.moveVoltage(10000);
      break;
    case CataState::MED:
      cataMotor.moveVoltage(9500);
      break;  
    case CataState::LO:
      cataMotor.moveVoltage(9000);
      break;
    
    
  }
}

 
CataState getCataState() { 
  return currentCataState; 
  }

void setCataState(CataState CState) { 
  currentCataState = CState; 
  }

  void updateDriverSkills(){

    if (controller.getDigital(ControllerDigital::Y) == 1){
      leftFront.setBrakeMode(AbstractMotor::brakeMode::coast);
      leftTop.setBrakeMode(AbstractMotor::brakeMode::coast);
      leftBack.setBrakeMode(AbstractMotor::brakeMode::coast);

      rightFront.setBrakeMode(AbstractMotor::brakeMode::coast);
      rightTop.setBrakeMode(AbstractMotor::brakeMode::coast);
      rightBack.setBrakeMode(AbstractMotor::brakeMode::coast);

      drivetrain(0.8, 1000, 1);

      turnLEFTONLY(107, 1000);

      pros::delay(100);

      drivetrain(1, 2000, 0.3);

    cataMotor.moveVoltage(9000);

      pros::delay(30000);

      cataMotor.moveVoltage(0);
      
       pros::delay(50);

    }
}
