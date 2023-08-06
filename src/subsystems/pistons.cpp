//pistons.cpp

#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/drive.hpp"
#include "subsystems/pistons.hpp"
#include "globals.hpp"


using namespace okapi;

ControllerButton extendButton = ControllerButton(ControllerDigital::R1);

ControllerButton retractButton = ControllerButton(ControllerDigital::R2);

pros::ADIDigitalOut flapjack1 = pros::ADIDigitalOut(flapjackPort1);
//pros::ADIDigitalOut flapjack2 = pros::ADIDigitalOut(flapjackPort2);

pros::ADIDigitalOut intakeFlipout = pros::ADIDigitalOut(intakeFlipoutPort);

//flapjack
//pros::ADIDigitalOut flapjack1(flapjackPort1);
//pros::ADIDigitalOut flapjack2(flapjackPort2);

//pros::ADIDigitalOut pistonPTO1(pistonPort1);
//pros::ADIDigitalOut pistonPTO1 = pros::ADIDigitalOut(pistonPort1);

//pros::ADIDigitalOut autonFlipout = pros::ADIDigitalOut(autonFlipoutPort);




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


void pistonsInnit() {
    //pistonPTO1.set_value(false);
    intakeFlipout.set_value(false);
    //autonFlipout.set_value(false);
    sharing = false;
}

void updateIntakeFlipout(){
    if (controller.getDigital(ControllerDigital::up) == 1){
        if(!sharing){
            intakeFlipout.set_value(true);
            sharing = true;
        }
        else{
            intakeFlipout.set_value(false);
            sharing = false; 
        }
    }
}



/*
void updatePistons(){
    if (controller.getDigital(ControllerDigital::down) == 1){
        if (!sharing){
            pistonPTO1.set_value(true);
            sharing = true;
        } else {
            pistonPTO1.set_value(false);
            sharing = false;
        }
    }

}
*/

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

