#include "subsystems/cata.hpp"
#include "subsystems/ports.hpp"
#include "globals.hpp"

Motor cataMotor(cataMotorPort, true, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);


ADIButton limitSwitch('A', true);


bool catapult = false;

void updateCata(){

    // without limit switch 

    if (controller.getDigital(ControllerDigital::up) == 1){
       // catapult = false;
        
        if(!catapult){
            cataMotor.moveVoltage(-9000);
            catapult = true;
        }
        else{
            cataMotor.moveVoltage(0);
            catapult = false; 
        }
    }

    else if (controller.getDigital(ControllerDigital::down) == 1){
       // catapult = false; 

        if(!catapult){
            cataMotor.moveVoltage(-10000);
            catapult = true;
        }
        else{
            cataMotor.moveVoltage(0);
            catapult = false; 
        }
    }

}
    

    



    /* with limit switch (if we end up added) 

    if (controller.getDigital(ControllerDigital::R1) == 1){
        while (!limitSwitch.isPressed()) {
            cataMotor.moveVoltage(12000);
        }
        
        cataMotor.moveVoltage(0);
    }

    else {
        if (!limitSwitch.isPressed()) {
            cataMotor.moveVoltage(12000);
        }

        else {
            cataMotor.moveVoltage(0);
        }
    }
    
    */