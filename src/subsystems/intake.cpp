#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/drive.hpp"

using namespace okapi;

Motor intakeMotor(intakePort, true, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees);

ControllerButton intakeButton = ControllerButton(ControllerDigital::L1);

void updateIntake(){

    intakeMotor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

    if(/*controller.getDigital(ControllerDigital::L1) == 1*/ intakeButton.changedToPressed()){
        intakeMotor.moveVelocity(600);
        
    } 
    //else if (controller.getDigital(ControllerDigital::L2) == 1){
      //  intakeMotor.moveVelocity(-600);
    //}
    else{
        intakeMotor.moveVelocity(0);
    }

    }

