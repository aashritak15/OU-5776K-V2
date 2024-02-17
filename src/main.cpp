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


pros::Motor lF(-7, pros::E_MOTOR_GEARSET_06); 
pros::Motor lM(9, pros::E_MOTOR_GEARSET_06); 
pros::Motor lB(-11, pros::E_MOTOR_GEARSET_06); 

pros::Motor rF(19, pros::E_MOTOR_GEARSET_06); 
pros::Motor rM(-20, pros::E_MOTOR_GEARSET_06); 
pros::Motor rB(12, pros::E_MOTOR_GEARSET_06); 




// motor groups
pros::MotorGroup leftMotors({lF, lM, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rM, rB}); // right motor group



lemlib::Drivetrain drive{
  &leftMotors,
  &rightMotors,
  12.5,
  4,
  300,
  2, 
};


lemlib::ControllerSettings movePID {
  //7, // kP
  //0, //kI
  //5, // kD
  8.6, // kP
  0, //kI
  10.4, // kD
  3, //anti windup
  1, // small error range
  100, // small error timeout 
  3, // large error range 
  500, // large error timeout 
  0 // slew rate 
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
  2.55, // kP
  0.1, // kI
  17, // kD
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
        //pros::lcd::print(2, "Theta: %f", pose.theta);
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
            pros::lcd::print(2, "Theta: %f", Chassis.getPose().theta); 
            pros::lcd::print(3, "Encoder LF: %f", lF.get_position());
            pros::lcd::print(4, "Encoder LM: %f", lM.get_position());
            pros::lcd::print(5, "Encoder LB: %f", lB.get_position());
            pros::lcd::print(6, "Encoder RF: %f", rF.get_position());
            pros::lcd::print(7, "Encoder RM: %f", rM.get_position());
            pros::lcd::print(8, "Encoder RB: %f", rB.get_position());
            
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", Chassis.getPose());
            // delay to save resources$
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
    //blockerInit();
    //PtoInit();
   

}


/**
* Runs while the robot is in the disabled state of Field Management System or
* the VEX Competition Switch, following either autonomous or opcontrol. When
* the robot is enabled, this task will exit.
*/
void disabled() {


}


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

  //Chassis.moveToPoint(0, 48, 100000, true, 100); //x =0, y=18

  /*
  ______________________________________________________________________________________________

  ADARSH 6 BALL AUTON 
  ______________________________________fa_______________________________________________________


*/

/*
//balance.set_value(true); // why tf isnt this working

intakeMotor1.moveVelocity(-600);
Chassis.setPose(0,0,0);
//Chassis.moveToPose(5, -10, 90, 4000, {.forwards = false,.minSpeed = 127});
//pros::delay(20000);

Chassis.moveToPose(2.2, -12, -4, 4000, {.forwards = false,.minSpeed = 127});
//Chassis.waitUntil(5);
pros::delay(1500);
// currently has intaked first tb, abt to drive back

Chassis.moveToPose(1, 1.5, 0, 4000, {.forwards = true,.minSpeed = 127});
pros::delay(1500);

//Chassis.turnTo(-10, -3.5, 4000, false, 127);
Chassis.turnTo(-10000, 0, 4000, false, 127);

intakeMotor1.moveVelocity(600);

Chassis.turnTo(10, 4.75, 4000, false, 127); // turns to face alley

intakeMotor1.moveVelocity(-600);

Chassis.moveToPose(6.5, 1.6, -90, 4000, {.forwards = false,.minSpeed = 127}); // moves towards and intakes tb under alley

Chassis.moveToPose(-7.8, 1.9, 138, 4000, {.forwards = true,.minSpeed = 127}); // moves to awpz area ready to turn and remove awp tb
pros::delay(1500);

/*flapjack1.set_value(true);
flapjack2.set_value(true);
Chassis.turnTo(-9.3, -5.9, 4000, false, 127);
Chassis.turnTo(0, 0, 4000, false, 127);
flapjack1.set_value(false);
flapjack2.set_value(false);

Chassis.moveToPose(-10.8, -5.3, -138, 4000, {.forwards = false,.minSpeed = 127});
Chassis.tank(-127,-127,0);
// add code to make 180 turn
intakeMotor1.moveVelocity(600);
//Chassis.tank(127,127,0);*/
//intakeMotor1.moveVelocity(0);





//Chassis.waitUntil(15);



 /*
  ______________________________________________________________________________________________

  ADARSH DO NOT CROSS THIS [DANGER]
  ______________________________________________________________________________________________

*/

    /*
  ______________________________________________________________________________________________

  PROG SKILLS
  ______________________________________________________________________________________________

*/
/*

cataMotor.moveVoltage(10500);

pros::delay(50000);  // <------------ IS THIS 30??

cataMotor.moveVoltage(0);
*/
/*
Chassis.setPose(0,0,0);

Chassis.moveToPose(-1, 14, -61, 4000, {.forwards = true, .minSpeed = 127});
Chassis.waitUntil(14);

pros::delay(100);

Chassis.moveToPose(-10, 0, -68, 4000, {.forwards = false,  .minSpeed = 90});
Chassis.waitUntil(14);

flapjack2.set_value(true);

// CATA DELAY CATA CATA CHANGE BEFORE GAME STARTS 30 SECOND CHECK 
cataMotor.moveVoltage(12000);

pros::delay(2000);  // <------------ IS THIS 30??

cataMotor.moveVoltage(0);

Chassis.moveToPose(0, 0, 0, 4000, {.forwards = true,  .minSpeed = 90} );
*/

/*
Chassis.setPose(0,0,0);
Chassis.moveToPoint(0,0,5000);
Chassis.moveToPose(-12.828, 33.341, -61, 4000, {.forwards = false,  .minSpeed = 90} );
Chassis.moveToPose(-12.089, 14.428, -68, 4000, {.forwards = false,  .minSpeed = 90} );

Chassis.moveToPose(102.563, 15.474, -42, 5000, {.forwards = true  .minSpeed = 90});

Chassis.moveToPoint(106.262, 32.878, 5000);

// out from the side 

Chassis.moveToPose(88.866, 15.474, 5000);


*/




  
/*


UNCOMMENT UNTILL HERE -----------------------------------------------------------------------------------------------_

*/


    /*
  ______________________________________________________________________________________________

  Close side AWP ONLY  (need to do file handling uh)
  ______________________________________________________________________________________________


*/

/*
Chassis.setPose(0, 0, 45);

Chassis.moveToPose(-27, -19, 60, 2500, {.forwards = false, .chasePower = 20, .minSpeed = 110});
  Chassis.waitUntil(70);

Chassis.tank(-50, -50);
pros::delay(200);
Chassis.tank(0, 0);

//-7.36,31/6,44.3

Chassis.moveToPose(-7.5, -4, 45, 2000, {.forwards = true, .chasePower = 20});
  Chassis.waitUntilDone();
  flapjack2.set_value(true);
pros::delay(300);

  Chassis.turnTo(-11, -4, 2000);

pros::delay(680);
  flapjack2.set_value(false);

Chassis.moveToPose(-6, 35, 0, 3000, {.forwards = true, .chasePower = 20});
   Chassis.waitUntilDone();
*/


/*
  flapjack1.set_value(false);

  Chassis.moveToPose(-50, 20, -90, 2500, {.chasePower = 18, .minSpeed = 110});

Chassis.moveToPose(-15, 1, -45, 2000, {.forwards = false, .chasePower = 18});
  Chassis.waitUntilDone();
 
  Chassis.cancelMotion();
  */

/*
Chassis.setPose(0, 0, 0);

Chassis.moveToPose(6.9, 9.6, 45, 5000, {.minSpeed = 127});

Chassis.turnTo(2.9, 9.6, 1600);

flapjack1.set_value(true);

Chassis.turnTo(6.9, 9.6, 5000);


Chassis.turnTo(6.9, 9.6, 5000, false);


Chassis.moveToPose(15, 8, -90, 4000, {.forwards = false, .minSpeed = 127});

Chassis.moveToPose(-20, -35, -180, 4000, {.forwards = false, .minSpeed = 127});
*/

//Chassis.turnTo(9,3, 3000, false);



//Chassis.moveToPoint(-60.379, -26.589, 5000);



/*
Chassis.setPose(0,0,0);


intakeMotor1.moveVelocity(-600);

Chassis.moveToPose(-1, -6, 48, 4000, {.forwards = false, .minSpeed = 127});
Chassis.waitUntil(5);

intakeMotor1.moveVelocity(0);

flapjack1.set_value(true);

Chassis.turnTo(-2, 48, 3000, true, 100);


Chassis.waitUntil(-13);

pros::delay(200);

flapjack1.set_value(false);
*/

/*

Chassis.turnTo(0, 0, 1500, true, 100);

Chassis.moveToPose(-15, -6, 0, 2000, {.forwards = false, .chasePower = 18, .minSpeed = 127});
Chassis.waitUntil(15);
Chassis.cancelAllMotions();
*/



//CV #6 close side AWP 

/*
Chassis.setPose(0,0,0);

Chassis.moveToPose(-2, -6, 48, 4000, {.forwards = false, .minSpeed = 127});
Chassis.waitUntil(5);
flapjack1.set_value(true);
Chassis.turnTo(-2, 1, 3000);
Chassis.waitUntil(13);

pros::delay(100);

flapjack1.set_value(false);

Chassis.moveToPose(-10, 9, -90, 5000, {.forwards = true, .minSpeed = 100});

pros::delay(200);

flapjack1.set_value(true);
flapjack1.set_value(true);
*/

//CV #6 close side AWP 














/*
pros::delay(100);
flapjack1.set_value(false);
Chassis.moveToPose(-6, -6, 90, 4000, {.forwards = false, .minSpeed = 90});
Chassis.waitUntil(30);

intakeMotor1.moveVelocity(-600);
*/






/*

Chassis.moveToPose(-9.5, -7, 70, 4000, {.forwards = false, .minSpeed = 90});
Chassis.waitUntil(50);

intakeMotor1.moveVelocity(600);

pros::delay(400);

Chassis.moveToPose(-14, -4, 90, 4000, {.forwards = false, .minSpeed = 90});

//Chassis.moveToPose(-3, 7, 0, 5000, {.forwards = true, .minSpeed = 100});

Chassis.moveToPose(-9.5, -9, 270, 4000, {.forwards = true, .minSpeed = 90});
*/











    /*
  ______________________________________________________________________________________________

  Far Side AWP (need to do file handling uh)
  ______________________________________________________________________________________________

*/


/*
Chassis.setPose(0, 0, 0);

intakeMotor1.moveVelocity(-600);

Chassis.moveToPose(1, -1, -45, 4000,  {.forwards = false, .minSpeed = 127});

Chassis.waitUntil(5);

intakeMotor1.moveVelocity(0);


Chassis.turnTo(3, 3, 1000, false);
Chassis.waitUntil(-9);
Chassis.cancelMotion();

Chassis.moveToPose(5, -1, -90, 4000,  {.forwards = false, .minSpeed = 127});
Chassis.waitUntil(30);
Chassis.cancelMotion();

Chassis.moveToPose(0, 3, -180, 3000, {.forwards = true, .minSpeed = 100});
Chassis.waitUntil(4);
Chassis.cancelMotion();

Chassis.moveToPose(5, 13, -150, 5000, {.forwards = false, .minSpeed = 90});
Chassis.waitUntil(30);
Chassis.cancelMotion();

intakeMotor1.moveVelocity(-600);

pros::delay(600);

Chassis.turnTo(15, -6, 2000, false, 90);
Chassis.waitUntil(60);
Chassis.cancelMotion();

pros::delay(100);

intakeMotor1.moveVelocity(600);

pros::delay(100);

Chassis.moveToPose(10, 12, -120, 5000, {.forwards = false, .minSpeed = 90});
Chassis.waitUntil(10);
Chassis.cancelMotion();

intakeMotor1.moveVelocity(600);


pros::delay(600);
Chassis.moveToPose(15, -6, 0, 5000, {.forwards = true, .minSpeed = 90});

*/

//NEW FAR SIDE RUN THIS FOR GOOGLE
 

Chassis.setPose(0, 0, 0);

intakeMotor1.moveVelocity(600);

Chassis.moveToPoint(0, 51, 4000, true, 127); 

Chassis.turnTo(100, 51, 1000);

intakeMotor1.moveVelocity(-600);
Chassis.moveToPoint(11, 53, 1000, true, 127);



Chassis.moveToPoint(0, 51, 4000, false, 127); 

Chassis.turnTo(-5, 39, 1000);


intakeMotor1.moveVelocity(600);

Chassis.moveToPoint(-5, 39, 5000, true,  80);

Chassis.turnTo(-20, 39, 1000);

Chassis.moveToPoint(-20, 39, 5000, true,  40);

pros::delay(2000); //tune this later


Chassis.turnTo(-14, 50 , 1000);

Chassis.moveToPoint(-14, 50, 2000,  true,  127);
flapjack1V.set_value(true);
flapjack2V.set_value(true);

Chassis.turnTo(-3, 68, 1000);

Chassis.moveToPoint(-3, 68, 3000, true, 127);

Chassis.turnTo(9.5, 68, 1000);

flapjack1V.set_value(true);
flapjack2V.set_value(true);

intakeMotor1.moveVelocity(-600);

Chassis.moveToPoint(14, 68, 1000, true, 127);
Chassis.waitUntilDone();

Chassis.tank(127 , 127);

pros::delay(400);

Chassis.tank(0 , 0);

Chassis.moveToPoint(-5, 68, 1000, false, 127);


/*
Chassis.turnTo(100, 51, 1000);

Chassis.waitUntil(55);

intakeMotor1.moveVelocity(600);

Chassis.moveToPoint(15, 51, 1000, true, 127);
*/




















//FAR SIDE CV #6
/*

    Chassis.setPose(0, 0, 0);

    balanceTrue();

  


    intakeMotor1.moveVelocity(600);
    pros::delay(100);
    
    Chassis.moveToPoint(0, -14.5, 4000, false, 127); 

    balanceInit();

    Chassis.waitUntil(55);
    Chassis.cancelMotion();

   
    Chassis.moveToPose(0, -15, 90, 1000, {.forwards = false, .minSpeed = 75}); 
    
     pros::delay(400);

   intakeMotor1.moveVelocity(-600);

 pros::delay(300);

     Chassis.moveToPose(-6.5, -15, 90, 1000, {.forwards = false, .minSpeed = 75}); 
    Chassis.waitUntil(5);
    Chassis.cancelMotion();

      Chassis.moveToPose(0, -15, 90, 1000, {.forwards = false, .minSpeed = 75}); 
    Chassis.waitUntil(5);
    Chassis.cancelMotion();

      intakeMotor1.moveVelocity(600);

      Chassis.turnTo(-100, -14, 1000);
  

     Chassis.moveToPose(5.5, -9, 280, 4000, {.forwards = false, .minSpeed = 80});
    Chassis.waitUntil(65);
    Chassis.cancelMotion();

    pros::delay(600);
    Chassis.turnTo(100, 14, 1500);

    Chassis.moveToPose(-14, -18, 90, 4000, {.forwards = false, .minSpeed = 127});

   // Chassis.moveToPose(-10, -17, 90, 4000, {.forwards = true, .minSpeed = 75});

    Chassis.turnTo(-100, 90, 1000);
    //-30, 0
    Chassis.moveToPose(-3.5, -12, 290, 4000, {.forwards = false, .minSpeed = 127});

    Chassis.turnTo(100, 8, 1000);

    Chassis.moveToPose(-12, -18, 90, 2000, {.forwards = false, .minSpeed = 127});

     flapjack1.set_value(true);
    flapjack2.set_value(true);

   
    Chassis.moveToPose(1.5, -0.5, 15, 2000, {.forwards = true, .minSpeed = 127});
    Chassis.waitUntil(55);
    Chassis.cancelMotion(); 


intakeMotor1.moveVelocity(300);


    Chassis.turnTo(-15, 15, 1000);

    
*/
    //FAR SIDE CV #6





    /*




     pros::delay(600);

    Chassis.moveToPose(-11, -16.5, 90, 4000, {.forwards = false, .minSpeed = 127});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();

    intakeMotor1.moveVelocity(-600);

    Chassis.moveToPose(-7, -16.5, 90, 1000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();

     pros::delay(50);

    Chassis.moveToPose(-8, -16.5, 90, 1000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();


     pros::delay(400);

    Chassis.moveToPose(9, -14, 260, 2000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();

  //  pros::delay(200);

     intakeMotor1.moveVelocity(600);

    pros::delay(900);
*/
  

/*
 ELIMS AUTON CHANGE: SCORES THE THIRD TRIBALL NO BAR 

*/

/*

Chassis.moveToPose(-10, -19, 90, 2000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();



    Chassis.moveToPose(-7, -19, 90, 1000, {.forwards = false, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion();


*/




//ENDING AWP TASKS: BARRIER 

/*
   Chassis.moveToPose(7, -2, 0, 2000, {.forwards = true, .minSpeed = 75});
    Chassis.waitUntil(55);
    Chassis.cancelMotion(); 


intakeMotor1.moveVelocity(300);

    flapjack1.set_value(true);
    flapjack2.set_value(true);


*/




/*

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

//------------------------------ WORKS NEED TO ADD MLZ PART


/*
Chassis.setPose(0, 0, 0); //change this based on how we are angling bot 


//flapjack2.set_value(true);

pros::delay(600);

Chassis.moveToPoint(0, 15, 0, 6000, true); 
Chassis.waitUntil(36);
Chassis.cancelMotion();


Chassis.moveToPose(4, 15, 90, 6000,{.minSpeed = 127} );
Chassis.waitUntil(24);
Chassis.cancelMotion();

pros::delay(100);

// going to the goal to score till now 

Chassis.moveToPose(-5, -8, 180, 10000, {.forwards = true, .minSpeed = 60}); 
Chassis.waitUntil(50);
Chassis.cancelMotion();

Chassis.moveToPose(-7.5, 7, 180, 10000, {.forwards = false, .minSpeed = 127});
Chassis.waitUntil(60);
Chassis.cancelMotion();
pros::delay(200);

Chassis.tank(0, -120);

pros::delay(600);

Chassis.tank(0, 0);

pros::delay(200);

Chassis.moveToPose(-2, 0, 40, 5000,{.forwards = true, .minSpeed = 75});

flapjack1.set_value(true);

Chassis.moveToPose(13, -4.5, 90, 5000, {.forwards = true, .minSpeed = 70});
*/


/*


UNCOMMENT UNTILL HERE -----------------------------------------------------------------------------------------------_

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
  
 
  pros::Controller controller1(pros::E_CONTROLLER_MASTER);
   

  int reverseDrive = 2;
  int driveState = 0;




    
    while (true) {
        int rightY = controller1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        int leftY = controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

        switch (reverseDrive) {
          case 1:
            Chassis.tank(-leftY, -rightY, 2); 
            
            break;
          case 2:
            Chassis.tank(leftY, rightY, 2);
            break; 
        }
        /*if (controller.getDigital(ControllerDigital::X) == 1) {
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
        */ // adarsh commented this out





        //all subsystem functions 

           //updateDrive();
            //updateRVDrive();
            //updateIntake();
            updateCata();
            updateFlapjack();
            //updateDriverSkills();
           // updatelMech();
            //updateBalance();
           // updateBlocker();
            //DarshyMech();
           // PtoMech()

          // mech();

          

       


           
           pros::delay(10);
}
}