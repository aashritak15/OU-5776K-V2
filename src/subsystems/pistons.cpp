#include "main.h"
#include "subsystems/ports.hpp"


using namespace okapi;


pros:ADIDigitalOut pistionPTO1(pistonPTO1Port);


bool sharing;


void pistonsInnit() {
pistionPTO1.set_value(false);
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
