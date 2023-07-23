#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/drive.hpp"


using namespace okapi;


pros::ADIDigitalOut pistonPTO1(pistonPTO1Port);


bool sharing;


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