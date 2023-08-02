#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/intake.hpp"
#include "globals.hpp"


using namespace okapi;

/*
Motor intakeMotor1(intakePort1, true, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees);
Motor intakeMotor2(intakePort2, false, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees);



ControllerButton intakeButton = ControllerButton(ControllerDigital::L1);
ControllerButton outakeButton = ControllerButton(ControllerDigital::L2);

*/

//bool toggle;


void intakeInnit(){
    intakeMotor1.setBrakeMode(AbstractMotor::brakeMode::coast);
    //intakeMotor2.setBrakeMode(AbstractMotor::brakeMode::coast);
   //toggle = false; 
}


/*
void updateIntake(){

    if(/*controller.getDigital(ControllerDigital::L1) == 1*/ /*intakeButton.changedToPressed()){
        intakeMotor1.moveVelocity(-600);
        intakeMotor2.moveVelocity(-600);*/

        /*
        //if(!toggle){
            
            toggle = true; 
       //}
        else{
            intakeMotor1.moveVelocity(0);
            intakeMotor2.moveVelocity(0);
            toggle = false; 
        }
        */
    /*
    } 
    //else if (controller.getDigital(ControllerDigital::L2) == 1){
      //  intakeMotor.moveVelocity(-600);
    //}

    else if(outakeButton.changedToPressed()){
        intakeMotor1.moveVelocity(600);
        intakeMotor2.moveVelocity(600);
    }

    else{
        intakeMotor1.moveVelocity(0);
        intakeMotor2.moveVelocity(0);
    }

    }
*/



Motor intakeMotor1(intakePort1, true, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);

/*Motor intakeMotor2(intakePort2, false, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);*/

//Motor flapjack1(flapjackPort1);
//Motor flapjack2(flapjackPort2);



ControllerButton intakeButton = ControllerButton(ControllerDigital::L1);
ControllerButton outakeButton = ControllerButton(ControllerDigital::L2);
//ControllerButton halfInButton = ControllerButton(ControllerDigital::up);

void intakeInit() { 
  intakeMotor1.setBrakeMode(AbstractMotor::brakeMode::hold); 
  //intakeMotor2.setBrakeMode(AbstractMotor::brakeMode::hold); 
  }

/*
=======

>>>>>>> 8e4267a2d59b1da6124cdef653260e72ff9a29d7
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


void updateIntake() {

  static IntakeState currentIntakeState = IntakeState::STOPPED;
  static IntakeState previousIntakeState = IntakeState::STOPPED;

  // if (outakeButton.changedToPressed()) {
  //   previousIntakeState = currentIntakeState;
  //   currentIntakeState = IntakeState::OUTTAKING;
  // } else if (outakeButton.changedToReleased()) {
  //   currentIntakeState = previousIntakeState;
  // }

  if (intakeButton.changedToPressed()) {
    if (currentIntakeState == IntakeState::INTAKING) {
      previousIntakeState = currentIntakeState;
      currentIntakeState = IntakeState::STOPPED;
    } else {
      previousIntakeState = currentIntakeState;
      currentIntakeState = IntakeState::INTAKING;
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
  if (outakeButton.changedToPressed()) {
    if (currentIntakeState == IntakeState::OUTTAKING) {
      previousIntakeState = currentIntakeState;
      currentIntakeState = IntakeState::STOPPED;
    } else {
      previousIntakeState = currentIntakeState;
      currentIntakeState = IntakeState::OUTTAKING;
    }
  }

  switch (currentIntakeState) {
    case IntakeState::STOPPED:
      //gradualStop();
      break;
      intakeMotor1.moveVoltage(0);
      intakeMotor2.moveVoltage(0);
      gradualStop();
    case IntakeState::INTAKING:
      intakeMotor1.moveVoltage(12000);
      //intakeMotor2.moveVoltage(12000);
      break;
    case IntakeState::OUTTAKING:
      intakeMotor1.moveVoltage(-12000);
      //intakeMotor2.moveVoltage(-12000);
      break;
  //case IntakeState::HALF:
    
    
  }
}

 
IntakeState getIntakeState() { 
  return currentIntakeState; 
  }

void setIntakeState(IntakeState IState) { 
  currentIntakeState = IState; 
  }