//pistons.cpp

#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/drive.hpp"
#include "subsystems/pistons.hpp"
#include "globals.hpp"


using namespace okapi;

ControllerButton extendButton = ControllerButton(ControllerDigital::right);

ControllerButton retractButton = ControllerButton(ControllerDigital::left);

pros::ADIDigitalOut flapjack1 = pros::ADIDigitalOut(flapjackPort1);
//pros::ADIDigitalOut flapjack2 = pros::ADIDigitalOut(flapjackPort2);

pros::ADIDigitalOut intakeFlipout = pros::ADIDigitalOut(intakeFlipoutPort);

pros::ADIDigitalOut awpFlipout = pros::ADIDigitalOut(awpFlipoutPort);

//flapjack
//pros::ADIDigitalOut flapjack1(flapjackPort1);
//pros::ADIDigitalOut flapjack2(flapjackPort2);

//pros::ADIDigitalOut pistonPTO1(pistonPort1);
//pros::ADIDigitalOut pistonPTO1 = pros::ADIDigitalOut(pistonPort1);

//pros::ADIDigitalOut autonFlipout = pros::ADIDigitalOut(autonFlipoutPort);


void pistonsInnit(){
    intakeFlipout.set_value(false);
    flapjack1.set_value(false);
    awpFlipout.set_value(false);
}

/*
void flipoutMech(){
    if (controller.getDigital(ControllerDigital::up) == 1){
        if(!sharing){
            autonFlipout.set_value(true);
            sharing = true;
        }
        else{
            autonFlipout.set_value(false);
            sharing = false;
        }
    }
}
*/


bool sharing;
bool flapjackOutwards = false;


void UpdateIntakeFlipout(){
    if (controller.getDigital(ControllerDigital::left) == 1) {
        intakeFlipout.set_value(true);
  }
    if(controller.getDigital(ControllerDigital::right) == 1) {
        intakeFlipout.set_value(false);
    }   
}



void updateFlapjack(){
    if (controller.getDigital(ControllerDigital::R2) == 1) {
        flapjack1.set_value(true);
  }
    if(controller.getDigital(ControllerDigital::R1) == 1) {
        flapjack1.set_value(false);
    }
}



/*
void extendFlapjack(){
    flapjack1.set_value(true);
   // flapjack2.set_value(true);
}

void retractFlapjack(){
    flapjack1.set_value(false);
   // flapjack2.set_value(false);
}

void stopFlapjack(){
    flapjack1.set_value(false);
   // flapjack2.set_value(false);
}

void flapjackCode(){
    while (true){
        if (extendButton.isPressed() && !flapjackOutwards){
            extendFlapjack();
            pros::delay(500);
            stopFlapjack();
            flapjackOutwards = true;
        } else if (retractButton.isPressed() && flapjackOutwards){
            retractFlapjack();
            pros::delay(500);
            stopFlapjack();
            flapjackOutwards = false;
        } else if((!extendButton.isPressed()) && (!retractButton.isPressed())){
            stopFlapjack();
            flapjackOutwards = false;
        }
    }
}
*/