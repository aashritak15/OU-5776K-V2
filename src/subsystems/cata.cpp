#include "subsystems/cata.hpp"
#include "subsystems/ports.hpp"
#include "globals.hpp"

Motor cataMotor(cataMotorPort, true, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

//ADIButton limitSwitch('A', true);
bool catapult = false;

void updateCata(){
    // without limit switch 

    if (controller.getDigital(ControllerDigital::up) == 1){
        catapult = false;

        if(!catapult){
            cataMotor.moveVoltage(-11000);
            catapult = true;
        }
        else{
            cataMotor.moveVoltage(0);
            catapult = false; 
        }
    }

    else if (controller.getDigital(ControllerDigital::down) == 1){
        //catapult = false; 
        catapult = false; 

        if(!catapult){
            cataMotor.moveVoltage(-12000);
            catapult = true;
        }
        else{
            cataMotor.moveVoltage(0);
            catapult = false; 
        }
    } else if (controller.getDigital(ControllerDigital::right) == 1){
      catapult = false;

       if(!catapult){
            cataMotor.moveVoltage(-20000);
            catapult = true;
        }
        else{
            cataMotor.moveVoltage(0);
            catapult = false; 
    }

    }
    
    else if (controller.getDigital(ControllerDigital::left) == 1){
      catapult = false;

       if(!catapult){
            cataMotor.moveVoltage(-10000);
            catapult = true;
        }
        else{
            cataMotor.moveVoltage(0);
            catapult = false; 
    }
}
}


    


/*
void cataInnit(){
    cataMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
    //intakeMotor2.setBrakeMode(AbstractMotor::brakeMode::coast);
   //toggle = false; 
}


Motor cataMotor1(cataMotorPort, true, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);

Motor intakeMotor2(intakePort2, false, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);

//Motor flapjack1(flapjackPort1);
//Motor flapjack2(flapjackPort2);


ControllerButton cataSlow = ControllerButton(ControllerDigital::up);
ControllerButton cataFast = ControllerButton(ControllerDigital::down);
//ControllerButton halfInButton = ControllerButton(ControllerDigital::up);


void updateCata() {


  static CataState currentCataState = CataState::STOPPED;
  //static IntakeState previousIntakeState = IntakeState::STOPPED;


  if (cataSlow.changedToPressed()) {
    if(!catapult){
            currentCataState = CataState::RUNNINGSLOW;
            catapult = true;
        } else{
            currentCataState = IntakeState::STOPPED;
            catapult = false; 
        }    
    }

    if (cataFast.changedToPressed()) {
        if(!catapult){
            currentCataState = CataState::RUNNINGFAST;
            catapult = true;
        } else{
            currentIntakeState = IntakeState::STOPPED;
            catapult = false; 
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
  

    
*/


    // with limit switch (if we end up added) 
/*
    if (controller.getDigital(ControllerDigital::up) == 1){
        while (!limitSwitch.isPressed()) {
            cataMotor.moveVoltage(-9000);
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





Motor cataMotor1(cataPort1, true, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);

Motor intakeMotor2(intakePort2, false, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);

Motor flapjack1(flapjackPort1);
Motor flapjack2(flapjackPort2);



ControllerButton cataRun = ControllerButton(ControllerDigital::up);
ControllerButton cataStop = ControllerButton(ControllerDigital::down);
//ControllerButton halfInButton = ControllerButton(ControllerDigital::up);



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
  
  if (halfInButton.changedToPressed()) {
    if (currentIntakeState == IntakeState::HALF) {
      previousIntakeState = currentIntakeState;
      currentIntakeState = IntakeState::STOPPED;
    } else {
      previousIntakeState = currentIntakeState;
      currentIntakeState = IntakeState::HALF;
    }
  }


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