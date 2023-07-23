#include "subsystems/cata.hpp"
#include "subsystems/ports.hpp"
#include "subsystems/drive.hpp"

Motor cataMotor(cataMotorPort, true, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);


void updateCata(){
    if (controller.getDigital(ControllerDigital::R1) == 1){
        cataMotor.moveVoltage(12000);
    }
    if (controller.getDigital(ControllerDigital::R2) == 1){
        cataMotor.moveVoltage(0);
    }
}