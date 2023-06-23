#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/drive.hpp"

using namespace okapi;

Motor intakeMotor(intakePort, true, AbstractMotor::gearset::green,
           AbstractMotor::encoderUnits::degrees);

void updateIntake(){

    intakeMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

    if (controller.getDigital(ControllerDigital::L1) == 1){
        intakeMotor.moveVelocity(600);
        
    } 
    else if (controller.getDigital(ControllerDigital::L2) == 1){
        intakeMotor.moveVelocity(-600);
    }
    else{
        intakeMotor.moveVelocity(0);
    }

    }

