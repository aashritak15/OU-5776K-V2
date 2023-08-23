#include "subsystems/cata.hpp"
#include "subsystems/ports.hpp"
#include "globals.hpp"

Motor cataMotor(cataMotorPort, true, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);
  
  
//  




bool catapult = false;


void cataInnit(){
    cataMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
    //intakeMotor2.setBrakeMode(AbstractMotor::brakeMode::coast);
   //toggle = false; 
}


Motor cataMotor1(cataMotorPort, true, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);

/*Motor intakeMotor2(intakePort2, false, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);*/

//Motor flapjack1(flapjackPort1);
//Motor flapjack2(flapjackPort2);


ControllerButton cataRun = ControllerButton(ControllerDigital::up);
ControllerButton cataStop = ControllerButton(ControllerDigital::down);
//ControllerButton halfInButton = ControllerButton(ControllerDigital::up);


void updateCata() {


  static CataState currentCataState = CataState::STOPPED;
  //static IntakeState previousIntakeState = IntakeState::STOPPED;



  if (cataRun.changedToPressed()) {
    if (currentCataState == CataState::RUNNINGSLOW) {
        currentCataState = CataState::STOPPED;
    } else if(currentCataState == CataState::RUNNINGFAST){
        currentCataState = CataState::STOPPED;
    }
      
    }

    if (cataStop.changedToPressed()) {
        if (currentCataState == CataState::RUNNINGSLOW) {
            currentCataState = CataState::STOPPED;
        } else if (currentCataState == CataState::RUNNINGFAST){
            currentCataState == CataState::STOPPED;
        }
  }
 




  switch (currentCataState) {
    case CataState::STOPPED:
      //gradualStop();
      cataMotor.moveVoltage(0);
      break;
    case CataState::RUNNINGSLOW:
      cataMotor.moveVoltage(-9000);
      break;
    case CataState::RUNNINGFAST:
      cataMotor.moveVoltage(-12000);
      break;
  }

}
  


 
CataState getCataState() { 
  return currentCataState; 
  }

void setCataState(CataState IState) { 
  currentCataState = IState; 
  }
  

    

    
/*


    /* with limit switch (if we end up added) 

    if (controller.getDigital(ControllerDigital::R1) == 1){
        while (!limitSwitch.isPressed()) {
            cataMotor.moveVoltage(12000);
        }
        
        cataMotor.moveVoltage(0);
    }

    else {
        if (!limitSwitch.isPressed()) {
            cataMotor.moveVoltage(12000);
        }

        else {
            cataMotor.moveVoltage(0);
        }
    }
    
    */
/*

    void cataInnit(){
    cataMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
    //intakeMotor2.setBrakeMode(AbstractMotor::brakeMode::coast);
   //toggle = false; 
}

*/

/*

Motor cataMotor1(cataPort1, true, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);

/*Motor intakeMotor2(intakePort2, false, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);*/

//Motor flapjack1(flapjackPort1);
//Motor flapjack2(flapjackPort2);

/*

ControllerButton cataRun = ControllerButton(ControllerDigital::up);
ControllerButton cataStop = ControllerButton(ControllerDigital::down);
//ControllerButton halfInButton = ControllerButton(ControllerDigital::up);
*/

/*
void gradualStop() {
  int stopTime = 5000;
  int voltage = 200;
  int timer = 0;

  while(timer < stopTime){
    int currentVoltage = (stopTime - timer) / (stopTime) * voltage;

    intakeMotor1.moveVoltage(currentVoltage);
    intakeMotor2.moveVoltage(currentVoltage);

    pros::delay(10);
    timer += 10;
   }

}
*/
/*
void updateCata() {


  static cataState currentCataState = CataState::STOPPED;
  //static IntakeState previousIntakeState = IntakeState::STOPPED;



  if (cataRun.changedToPressed()) {
    if (currentCataState == CataState::RUNNING) {
      //previousIntakeState = currentIntakeState;
      currentCataState = CataState::STOPPED;
    };
      
    }
  } 
  /*
  if (halfInButton.changedToPressed()) {
    if (currentIntakeState == IntakeState::HALF) {
      previousIntakeState = currentIntakeState;
      currentIntakeState = IntakeState::STOPPED;
    } else {
      previousIntakeState = currentIntakeState;
      currentIntakeState = IntakeState::HALF;
    }
  }*/

/*
  if (cataStop.changedToPressed()) {
    if (currentCataState == CataState::RUNNING) {
      //previousIntakeState = currentIntakeState;
      currentCataState = CataState::STOPPED;
    }
  }

  switch (currentCataState) {
    case cataState::STOPPED:
      //gradualStop();
      cataMotor.moveVoltage(0);
      break;
    case cataState::RUNNINGSLOW:
      cataMotor.moveVoltage(-9000);
      break;
    case cataState::RUNNINGFAST:
      cataMotor.moveVoltage(-12000);
      break;
  }
  


 
CataState getCataState() { 
  return currentCataState; 
  }

void setCataState(bool CataState IState) { 
  currentCataState = IState; 
  }
  */