#include "subsystems/cata.hpp"
#include "subsystems/ports.hpp"
#include "globals.hpp"

Motor cataMotor(cataMotorPort, true, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

//need to add a limit switch 

void updateCata(){
    
    if (controller.getDigital(ControllerDigital::R1) == 1){
        cataMotor.moveVoltage(12000);
    }

    if (controller.getDigital(ControllerDigital::R2) == 1){
        cataMotor.moveVoltage(0);
    }

}