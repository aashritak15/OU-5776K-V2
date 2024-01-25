#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/drive.hpp"
#include "subsystems/odo.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/pistons.hpp"
#include "subsystems/cata.hpp"
#include "subsystems/auton.hpp"
#include "subsystems/skills.hpp"
#include "globals.hpp"

#include "selection.h"


#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"

// drive motors
pros::Motor lF(-12, pros::E_MOTOR_GEARSET_06); 
pros::Motor lM(20, pros::E_MOTOR_GEARSET_06); 
pros::Motor lB(-19, pros::E_MOTOR_GEARSET_06); 

pros::Motor rF(11, pros::E_MOTOR_GEARSET_06); 
pros::Motor rM(-9, pros::E_MOTOR_GEARSET_06); 
pros::Motor rB(10, pros::E_MOTOR_GEARSET_06); 



// motor groups
pros::MotorGroup leftMotors({lF, lM, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rM, rB}); // right motor group



lemlib::Drivetrain drive{
  &leftMotors,
  &rightMotors,
  10,
  lemlib::Omniwheel::NEW_325,
  300,
  2, 
};


lemlib::ControllerSettings movePID {
  13, // kP
  0, //kI
  6, // kD
  3, //anti windup
  1, // small error range
  100, // small error timeout 
  3, // large error range 
  500, // large error timeout 
  20 // slew rate 
};

pros::Imu intertial1(imuPort1);

//pros::Imu intertial2(imuPort2);

lemlib::OdomSensors sensors {
  nullptr, //no tracking wheels 
  nullptr,
  nullptr,
  nullptr,
  &intertial1
};

lemlib::ControllerSettings turnPID {
  2, // kP
  0, // kI
  10, // kD
  3, //anti windup 
  1, // small error range
  100, // small error timeout 
  3, // large error range 
  500, // large error timeout 
  0 // slew rate 
};

lemlib::Chassis Chassis(drive, movePID, turnPID, sensors);

inline double remap(double d) {
    if (d == 0) {
        return 0;
    }

    double fp = d - (int)d;
    int id = (int)d;

    if (d > 0) {
        id = id % 360;
    } else {
        id = (-id % 360) * -1 + 360;
    }

    d = id + fp;
    return (d <= 180) ? d : (d - 360);
}





/*
  ______________________________________________________________________________________________

  Controller Stuff 
  ______________________________________________________________________________________________

*/

void screen(){
    while (true) {
        lemlib::Pose pose = Chassis.getPose(); // get chassis position
        pros::lcd::print(0, "X: %f", pose.x);
        pros::lcd::print(1, "Y: %f", pose.y);
        pros::lcd::print(2, "Theta: %f", pose.theta);
        pros::delay(10);
    }
}




//okapi::IntegratedEncoder leftEncoder = IntegratedEncoder(rightTopPort, true);

/**
* Runs initialization code. This occurs as soon as the program is started.
*
* All other competition modes are blocked by initialize; it is recommended
* to keep execution time for this mode under a few seconds.
*/
void initialize() {
    pros::lcd::initialize();
    Chassis.calibrate();
   
    
    Chassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0

	// print odom values to the brain
    pros::lcd::initialize();
    pros::Task screen_task(screen);

   // selector::init();
    //IEInnit();

    pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", Chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", Chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", Chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", Chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });

    
    //imuInnit();
    intakeInit();
    cataInit();
    //flipoutMechInnit();
    //resetEncoders();
    //pistonsInnit();
    //lMechInit();
    //balanceInit();
    blockerInit();
    //PtoInit();
   

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


 

//tatic path =ASSET("path.jerryio.txt");

void autonomous() {



    /*
  ______________________________________________________________________________________________

  PROG SKILLS
  ______________________________________________________________________________________________

*/

Chassis.moveToPoint(0, 0,5000);
Chassis.moveToPoint(-6.06, 8.08, 5000);
Chassis.moveToPoint(-3.02, 0.76, 5000);
Chassis.moveToPoint(1.2, -0.75, 5000);
Chassis.moveToPoint(13.2, 0, 5000);



   


  
/*


UNCOMMENT UNTILL HERE -----------------------------------------------------------------------------------------------_

*/



    /*
  ______________________________________________________________________________________________

  Far Side AWP (need to do file handling uh)
  ______________________________________________________________________________________________

*/



/*


    Chassis.setPose(0, 0, 0);

    blocker1.set_value(true);

    pros::delay(100);

    intakeMotor1.moveVelocity(-600);

     pros::delay(200);

    blocker1.set_value(false);

      pros::delay(100);


    intakeMotor1.moveVelocity(-600);
   pros::delay(100);
    
    Chassis.moveToPose(0, -21, 0, 4000, {.forwards = false, .minSpeed = 75}); 
    Chassis.waitUntil(55);
    Chassis.cancelMotion();

  pros::delay(300);
   
    Chassis.moveToPose(0, -21, 90, 1000, {.forwards = false, .minSpeed = 75}); 
    
     pros::delay(400);

   intakeMotor1.moveVelocity(600);

 pros::delay(300);

    Chassis.moveToPose(-6, -21, 90, 1000, {.forwards = false, .minSpeed = 75}); 
    Chassis.waitUntil(5);
    Chassis.cancelMotion();

      Chassis.moveToPose(0, -21, 90, 1000, {.forwards = false, .minSpeed = 75}); 
    Chassis.waitUntil(5);
    Chassis.cancelMotion();

      intakeMotor1.moveVelocity(-600);
  

    Chassis.moveToPose(10, -9, 280, 4000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(65);
    Chassis.cancelMotion();


     pros::delay(400);

    Chassis.moveToPose(-8, -19, 90, 4000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();

    intakeMotor1.moveVelocity(600);

    Chassis.moveToPose(-7, -19, 90, 1000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();

     pros::delay(50);

    Chassis.moveToPose(-8, -19, 90, 1000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();


     pros::delay(400);





    Chassis.moveToPose(6, -14, 0, 4000, {.forwards = false, .minSpeed = 75});
     Chassis.waitUntil(55);
    Chassis.cancelMotion();

    Chassis.moveToPose(14, -14, 260, 2000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();

  //  pros::delay(200);

     intakeMotor1.moveVelocity(-600);

    pros::delay(400);


/*
 ELIMS AUTON CHANGE: SCORES THE THIRD TRIBALL NO BAR 

*/


/*
Chassis.moveToPose(-9, -19, 90, 1000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();



    Chassis.moveToPose(-5, -19, 90, 1000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();
*/












/*

ENDING AWP TASKS: BARRIER 
   Chassis.moveToPose(7, -2, 0, 2000, {.forwards = true, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion(); 


intakeMotor1.moveVelocity(300);

    flapjack1.set_value(true);
    flapjack2.set_value(true);
*/






/*


UNCOMMENT UNTILL HERE -----------------------------------------------------------------------------------------------_

*/





/*

Chassis.moveTo(0, 0, 5000);
Chassis.moveTo(0.743, -31.711, 5000);


     pros::delay(300);

    Chassis.moveToPose(5, -17, 0, 4000, {.forwards = false, .minSpeed = 50}); 
      Chassis.waitUntil(55);
    Chassis.cancelMotion();

    intakeMotor1.moveVelocity(600);

    pros::delay(300);

     intakeMotor1.moveVelocity(0);

    */

   // Chassis.moveToPose(0, -22, 90, 4000, {.forwards = false, .minSpeed = 50});






  



   


    /*

    intakeMotor1.moveVelocity(0);

    intakeMotor1.moveVelocity(-600);

    Chassis.moveToPose(17, -12, 260, 4000, {.forwards = false});

    intakeMotor1.moveVelocity(-600);

    Chassis.turnTo(17, -21, 1000);

     flapjack1.set_value(true);
    flapjack2.set_value(true);

    Chassis.moveToPose(17, -28, 180, 4000, {.forwards = true, .minSpeed = 100});


    Chassis.moveToPose(-4, -25, 275, 4000, {.forwards = true, .minSpeed = 50}); 

    pros::delay(1000);

    flapjack1.set_value(false);
    flapjack2.set_value(false);


    intakeMotor1.moveVelocity(600);

    pros::delay(300);

    intakeMotor1.moveVelocity(0);

    Chassis.moveToPose(17, -5, 0, 4000, {.forwards = true});

    flapjack1.set_value(true);
    flapjack2.set_value(true);

*/









  /*
  ______________________________________________________________________________________________

  Close Side AWP (need to do file handling uh)
  ______________________________________________________________________________________________

*/


/*
//did not add delays because im p sure lem lib doesnt need
leftFront.setBrakeMode(AbstractMotor::brakeMode::brake);
    leftTop.setBrakeMode(AbstractMotor::brakeMode::brake);
    leftBack.setBrakeMode(AbstractMotor::brakeMode::brake);

    rightFront.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightTop.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightBack.setBrakeMode(AbstractMotor::brakeMode::brake);

// adarsh hi read here
Chassis.setPose(0, 0, 0); //change this based on how we are angling bot 


//flapjack2.set_value(true);

pros::delay(600);

flapjack2.set_value(false);

Chassis.moveToPoint(0, 14, 4000, true, 127); 

Chassis.turnTo(10, 20, 1000, true, 90);

Chassis.turnTo(10, -25, 1000, true, 90);

//flapjack2.set_value(true);

Chassis.moveToPose(-6.5, 0, 180, 5000, {.forwards = true, .minSpeed = 90}); 

pros::delay(100);

flapjack2.set_value(false);

// going to the goal to score till now 

Chassis.moveToPose(-6.5, -9, 180, 1000, {.forwards = true, .minSpeed = 45}); 

pros::delay(300);

Chassis.moveToPose(-11, 6, 180, 2000, {.forwards = false, .minSpeed = 127});

pros::delay(100);

Chassis.moveToPose(-14, 22, 180, 2000, {.forwards = false, .minSpeed = 127});

//Chassis.moveToPose(-12, 11, 180, 2000, {.forwards = false, .minSpeed = 90});


Chassis.moveToPose(-2, 0, 40, 5000,{.forwards = true, .minSpeed = 75});
//Chassis.moveToPose(-1, 1, 40, 5000,{.forwards = true, .minSpeed = 75});
// line above is to go to matchload zone (uncomment if line 543 isnt working)


flapjack1.set_value(true);

Chassis.turnTo(0, 5, 2000);

Chassis.moveToPose(13, -4.5, 90, 5000, {.forwards = true, .minSpeed = 50});

flapjack1.set_value(false);

pros::delay(300);

flapjack2.set_value(true);

*/


/*


UNCOMMENT UNTILL HERE -----------------------------------------------------------------------------------------------_

*/

/*

chassis.moveTo(0, 0, 5000);
chassis.moveTo(14.07, -40.021, 5000);
chassis.moveTo(28.491, -48.31, 5000);


Chassis.moveToPose(0, 12, 0, 3000);

Chassis.moveToPose(23, 0, 45, 5000, {.forwards = true, .minSpeed = 75});

//Chassis.turnTo(-4, -5, 2000);

flapjack1.set_value(true);


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
  pros::Controller controller1(pros::E_CONTROLLER_MASTER);
   

  int reverseDrive = 2;
  int driveState = 0;




    
    while (true) {

        int rightY = controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int leftY = controller1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        switch (reverseDrive) {
          case 1:
            Chassis.tank(rightY, leftY, 2); 
            
            break;
          case 2:
            Chassis.tank(-leftY, -rightY, 2);
            break; 
        }
        if (controller.getDigital(ControllerDigital::X) == 1) {
            if (driveState == 0) {
                reverseDrive = 1;
                driveState++;
                pros::delay(400);
            } else {
                reverseDrive = 2;
                driveState--;
                pros::delay(400);
            }
        }
        





        //all subsystem functions 

           //updateDrive();
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