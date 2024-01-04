#include "subsystems/drive.hpp"
#include "subsystems/auton.hpp"
#include "subsystems/odo.hpp"
#include "subsystems/path.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/pistons.hpp"
#include "subsystems/cata.hpp"
#include "subsystems/ports.hpp"
#include "subsystems/skills.hpp"



#include "globals.hpp"

using namespace okapi;


void intakeSkills(IntakeState currentIntakeState){
    switch (currentIntakeState) {

    case IntakeState::STOPPED:
      //gradualStop();
      break;
      intakeMotor1.moveVoltage(0);
    case IntakeState::INTAKING:
      intakeMotor1.moveVoltage(-14000);
      //intakeMotor2.moveVoltage(12000);
      break;
    case IntakeState::OUTTAKING:
      intakeMotor1.moveVoltage(14000);
      //intakeMotor2.moveVoltage(-12000);
      break;
  //case IntakeState::HALF:

  }
}


void printToLCD(const char* text) {
    lv_obj_t* label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, text);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
}

void gradualMax(int ms, int back){
  int timer = 0;

  int speed = 500 * back;
  int val = 100;
  //int newSpeed = 0;

  
 
  while (timer < ms){
    
   

     left.moveVoltage(speed);
     right.moveVoltage(speed);
    
    val *=1.2;
    speed += val;
    
    timer += 10;
    pros::delay(10);
}
     left.moveVoltage(0);
     right.moveVoltage(0);

}



void updateSkills(int path){
    if (path == 1){}
}
