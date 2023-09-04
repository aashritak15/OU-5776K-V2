//pistons.cpp

#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/drive.hpp"
#include "subsystems/pistons.hpp"
#include "globals.hpp"


using namespace okapi;


pros::ADIDigitalOut flapjack1 = pros::ADIDigitalOut(flapjackPort1);
//pros::ADIDigitalOut flapjack2 = pros::ADIDigitalOut(flapjackPort2);

//pros::ADIDigitalOut awpFlipout = pros::ADIDigitalOut(awpFlipoutPort);
pros::ADIDigitalOut lMech = pros::ADIDigitalOut(lMechPort);
pros::ADIDigitalOut balance = pros::ADIDigitalOut(balancePort);
pros::ADIDigitalOut blocker = pros::ADIDigitalOut(blockerPort);

//flapjack
//pros::ADIDigitalOut flapjack1(flapjackPort1);
//pros::ADIDigitalOut flapjack2(flapjackPort2);

//pros::ADIDigitalOut pistonPTO1(pistonPort1);
//pros::ADIDigitalOut pistonPTO1 = pros::ADIDigitalOut(pistonPort1);

//pros::ADIDigitalOut autonFlipout = pros::ADIDigitalOut(autonFlipoutPort);


void pistonsInnit(){
    //intakeFlipout.set_value(false);
    flapjack1.set_value(false);
    lMech.set_value(false);
    balance.set_value(false);
    blocker.set_value(false);

    //awpFlipout.set_value(false);
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


bool sharing = false;
bool flapjackOutwards = false;
//bool lMech = false;
//bool balance = false;
//bool blocker = false;

/*a = balance
x = blocker
b = l
*/

void lMechInit (){lMech.set_value(false);}

int lMechState = 0;

void updatelMech(){
    if (controller.getDigital(ControllerDigital::B) == 1){
        if(lMechState == 0){
            lMech.set_value(true);
            lMechState++;
            pros::delay(400);
        }
        else{
            lMech.set_value(false);
            lMechState--;
            pros::delay(400);
        }
    }
}

void balanceInit (){balance.set_value(false);}

int balanceState = 0;

void updateBalance(){
    if (controller.getDigital(ControllerDigital::A) == 1){
        if(balanceState == 0){
            balance.set_value(true);
            balanceState++;
            pros::delay(400);
        }
        else{
            balance.set_value(false);
            balanceState--;
            pros::delay(400);
        }
    }
}

void blockerInit (){blocker.set_value(false);}

int blockerState = 0;

void updateBlocker(){
        if (controller.getDigital(ControllerDigital::X) == 1){
        if(blockerState == 0){
            blocker.set_value(true);
            blockerState++;
            pros::delay(400);
        }
        else{
            blocker.set_value(false);
            blockerState--;
            pros::delay(400);
        }
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
//