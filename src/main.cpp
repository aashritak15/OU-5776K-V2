#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/drive.hpp"
#include "subsystems/odo.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/pistons.hpp"
#include "subsystems/cata.hpp"
#include "subsystems/auton.hpp"
#include "subsystems/skills.hpp"

#include "selection.h"


#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"


pros::Motor rightFront1(11, pros::E_MOTOR_GEARSET_06, true);
pros::Motor rightTop1(9, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightBack1(10, pros::E_MOTOR_GEARSET_06, true);

pros::Motor leftFront1(12, pros::E_MOTOR_GEARSET_06, false);
pros::Motor leftTop1(20, pros::E_MOTOR_GEARSET_06, true);
pros::Motor leftBack1(19, pros::E_MOTOR_GEARSET_06, false);


pros::MotorGroup left1({leftFront1, leftTop1, leftBack1});
pros::MotorGroup right1({rightFront1, rightTop1, rightBack1});



lemlib::Drivetrain_t drive {
  &left1,
  &right1,
  10,
  3.25,
  300
};


lemlib::ChassisController_t movePID {
  14, // kP
  8, // kD
  1, // small error range
  100, // small error timeout 
  3, // large error range 
  500, // large error timeout 
  0 // slew rate 
};

pros::Imu intertial1(imuPort1);
pros::Imu intertial2(imuPort2);

lemlib::OdomSensors_t sensors {
  nullptr, //no tracking wheels 
  nullptr,
  nullptr,
  nullptr,
  &intertial1
};

lemlib::ChassisController_t turnPID {
  0, // kP
  0, // kD
  1, // small error range
  100, // small error timeout 
  3, // large error range 
  500, // large error timeout 
  0 // slew rate 
};

lemlib::Chassis Chassis(drive, movePID, turnPID, sensors);


/*
  ______________________________________________________________________________________________

  Controller Stuff 
  ______________________________________________________________________________________________

*/






//okapi::IntegratedEncoder leftEncoder = IntegratedEncoder(rightTopPort, true);

/**
* Runs initialization code. This occurs as soon as the program is started.
*
* All other competition modes are blocked by initialize; it is recommended
* to keep execution time for this mode under a few seconds.
*/
void initialize() {

    // lem lib stuff
   
    

    selector::init();
    //IEInnit();

    /*
    imuInnit();
    intakeInit();
    cataInit();
    //flipoutMechInnit();
    //resetEncoders();
    //pistonsInnit();
    //lMechInit();
    //balanceInit();
    blockerInit();
    //PtoInit();
   */

}


/**
* Runs while the robot is in the disabled state of Field Management System or
* the VEX Competition Switch, following either autonomous or opcontrol. When
* the robot is enabled, this task will exit.
*/
void disabled() {}


/**
* Runs after initialize(), and before autonomous when connected to the Field
* Management System or the VEX Competition Switch. This is intended for
* competition-specific initialization routines, such as an autonomous selector
* on the LCD.
*
* This task will exit when the robot is enabled and autonomous or opcontrol
* starts.
*/

int side = -1;
//int num = -1;
void competition_initialize() {
    

// if (selector::auton == 1){side = 2;}
// if (selector::auton == 2){side = 1;}
// if (selector::auton == 3) {side = 4;}
// if (selector::auton == -1) {side = 2;}
// if (selector::auton == -2) {side = 1;}
// if (selector::auton == -3) {side = 4;}
// if (selector::auton == 0) {side = 0;}

}


/**
* Runs the user autonomous code. This function will be started in its own task
* with the default priority and stack size whenever the robot is enabled via
* the Field Management System or the VEX Competition Switch in the autonomous
* mode. Alternatively, this function may be called in initialize or opcontrol
* for non-competition testing purposes.
*
* If the robot is disabled or communications is lost, the autonomous task
* will be stopped. Re-enabling the robot will restart the task, not re-start it
* from where it left off.
*/
void autonomous() {
    //turnCounter(120, 1000);





   /* 
   if (side == 0) {
   updateSkills(2);
   } else {
    //updateAuton(side);
   }

   */


    
   
}


/**
* Runs the operator control code. This function will be started in its own task
* with the default priority and stack size whenever the robot is enabled via
* the Field Management System or the VEX Competition Switch in the operator
* control mode.
*
* If no competition control is connected, this function will run immediately
* following initialize().
*
* If the robot is disablsed or communications is lost, the
* operator control task will be stopped. Re-enabling the robot will restart the
* task, not resume it from where it left off.
*/
void opcontrol() {
  
  okapi::Rate rate;
  pros::Controller controller(pros::E_CONTROLLER_MASTER);

    while (true) {
        
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        Chassis.curvature(leftY, rightX);



        
           updateDrive();
            //updateRVDrive();
            updateIntake();
            updateCata();
            updateFlapjack();
            //updateDriverSkills();
           // updatelMech();
            updateBalance();
            updateBlocker();
            //DarshyMech();
           // PtoMech();


          

       


           
            rate.delay(100_Hz); 
}
}