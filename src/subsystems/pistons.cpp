#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/drive.hpp"
#include "subsystems/pistons.hpp"
#include "globals.hpp"
#include "subsystems/ports.hpp"


using namespace okapi;

ControllerButton extendButton = ControllerButton(ControllerDigital::R1);
ControllerButton retractButton = ControllerButton(ControllerDigital::R2);

//flapjack
pros::ADIDigitalOut flapjack1 (flapjackPort1);
pros::ADIDigitalOut flapjack2 (flapjackPort2);

pros::ADIDigitalOut pistonPTO1(pistonPort1);


bool sharing;
bool flapjackOutwards = false;


void pistonsInnit() {
    pistonPTO1.set_value(false);
    sharing = false;
}


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

void extendFlapjack(){
    flapjack1.set_value(true);
    flapjack2.set_value(true);
}

void retractFlapjack(){
    flapjack1.set_value(false);
    flapjack2.set_value(false);
}

void stopFlapjack(){
    flapjack1.set_value(false);
    flapjack2.set_value(false);
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
        } else (!extendButton.isPressed() && !retractButton.isPressed()){
            stopFlapjack();
            flapjackOutwards = false;
        }
    }
}