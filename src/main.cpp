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
#include "pros/motors.h"
#include "pros/rtos.hpp"

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
    Chassis.calibrate();

     pros::lcd::initialize();
   
  

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

void closeSideNEW(){

  
  Chassis.setPose(0,0,-45);
  Chassis.moveToPoint(14, -13, 1000, false, 127);
  Chassis.moveToPose(20, -26, 0, 500, {.forwards = false, .chasePower = 200});
  Chassis.waitUntil(80);
  Chassis.cancelAllMotions();
  Chassis.tank(-80, -80);
pros::delay(500);
Chassis.tank(0, 0);


Chassis.moveToPose(8, -10, -45, 1000, {.forwards = true, .chasePower = 200});
  Chassis.waitUntilDone();
  flapjack2.set_value(true);
pros::delay(300);

Chassis.turnToHeading(-127, 700, true);

pros::delay(680);
  flapjack2.set_value(false);

Chassis.turnToHeading(-40, 700, true);

Chassis.moveToPose(-31, -4, -90, 2000, {.forwards = true, .chasePower = 200});


  intakeMotor1.moveVelocity(-600);



//13, -13, -45

  /*
  Chassis.setPose(0,0,-45);
balanceTrue();

pros::delay(200);

balanceInit();


Chassis.moveToPose(20, -20, 0, 700, {.forwards = false, .chasePower = 200});
 // Chassis.waitUntil(70);
 */
  
}


void closeSideDisrupt(){


  Chassis.setPose(0, 0, 12.1);

  balance.set_value(true);

  
  Chassis.moveToPoint(12.7, 47.45, 2000, true, 127);
  intakeMotor1.moveVelocity(600);
flapjack1.set_value(false);
  pros::delay(100);

  Chassis.moveToPoint(13.1, 45.8, 1000, false, 127);
   Chassis.turnToHeading(90, 500, true);
   Chassis.waitUntilDone();
   Chassis.cancelAllMotions();

     flapjack2V.set_value(true);

  balance.set_value(false);
   Chassis.moveToPoint(33, 47.5, 1000, true, 80);
   Chassis.waitUntilDone();
   Chassis.cancelAllMotions();


   Chassis.moveToPose(3, 5.2 ,0, 2500, {.forwards = false, .chasePower = 200});
    flapjack2V.set_value(false);
   Chassis.turnToHeading(90, 500, true);
     Chassis.waitUntilDone();
   Chassis.cancelAllMotions();

   pros::delay(300);

  intakeMotor1.moveVelocity(-600);

     pros::delay(300);


  Chassis.moveToPose(-25.4, 25.8, 180, 1000, {.forwards = false, .chasePower = 200} );

Chassis.waitUntil(30);

Chassis.moveToPoint(-25.4, 40, 600, false, 127 );


Chassis.moveToPose(-14, 5.7 , 135, 3000, {.forwards = true, .chasePower = 200});
flapjack2.set_value(true);

Chassis.turnToHeading(45, 500, true);

Chassis.turnToHeading(180, 500, true);

flapjack2.set_value(false);


Chassis.moveToPose(34, 1, 270, 2200, {.forwards = false, .chasePower = 200, .minSpeed = 100});

Chassis.moveToPose(-13.5, 11.1, 314, 2000, {.forwards = true, .chasePower = 200});
   Chassis.waitUntilDone();
   Chassis.cancelAllMotions();

pros::delay(200);

flapjack1.set_value(true);

flapjack2.set_value(true);




/*
  intakeMotor1.moveVelocity(600);

  Chassis.moveToPoint(0, 24, 500, true, 127);


intakeMotor1.moveVelocity(600);

  Chassis.moveToPose(9, 56, 0, 800, {.forwards = true, .chasePower = 200,  .minSpeed = 100});

  Chassis.waitUntilDone();
  Chassis.cancelAllMotions();

pros::delay(250);

  balance.set_value(true);

  flapjack2V.set_value(true);

  Chassis.turnToHeading(90, 500, true);

  Chassis.moveToPoint(27, 58, 1000, true, 127);


  balance.set_value(false);

  Chassis.moveToPose(-2,9,0, 2500, {.forwards = false, .chasePower = 200});
   flapjack2V.set_value(false);

  
  Chassis.turnToHeading(90, 500, true);

  
intakeMotor1.moveVelocity(-600);

Chassis.moveToPose(-29, 34, 180, 2500, {.forwards = false, .chasePower = 200});

  

//24, 58

      

     // Chassis.moveToPoint(-29, 40, 2000);

  //hello
  */
}

void closeSide(){

  Chassis.setPose(0, 0, 45);

balanceTrue();

pros::delay(200);

balanceInit();


Chassis.moveToPose(-27, -19, 60, 2500, {.forwards = false, .chasePower = 20, .minSpeed = 110});
  Chassis.waitUntil(70);

Chassis.moveToPoint(-35, -19, 600, false, 127);

//-7.36,31/6,44.3

Chassis.moveToPose(-7.5, -4, 45, 2000, {.forwards = true, .chasePower = 20});
  Chassis.waitUntilDone();
  flapjack2.set_value(true);
pros::delay(300);

  Chassis.turnTo(-11, -4, 2000);

pros::delay(680);
  flapjack2.set_value(false);

  intakeMotor1.moveVelocity(-600);

Chassis.moveToPose(-4, 35, 0, 3000, {.forwards = true, .chasePower = 200});
   Chassis.waitUntilDone();

  
}





void skills() {

//going to score two preloads 
Chassis.setPose(0, 0, 39);
 

 Chassis.moveToPoint(-8.6, -10.2, 1000, false, 127);

 Chassis.turnToHeading(-27, 2000, true);

 Chassis.moveToPoint(-8.4, -16.2, 1000, false, 127);
 Chassis.waitUntilDone();
 Chassis.cancelAllMotions();

 lemlib::Pose startingPose = Chassis.getPose();

  
flapjack2.set_value(true);

cataMotor.moveVoltage(12000);
Chassis.setBrakeMode(MOTOR_BRAKE_HOLD);

pros::delay(19000); //<------ MATCHLOADING PART 

cataMotor.moveVoltage(0);

Chassis.setPose(startingPose);

pros::delay(50);

Chassis.setBrakeMode(MOTOR_BRAKE_BRAKE);

Chassis.moveToPoint(-8.6, -10.2, 1000, true, 127);
flapjack2.set_value(false);

 Chassis.turnToHeading(45, 1000, true);

 Chassis.moveToPose(-32, -22, 90, 1000,{.forwards = false, .chasePower = 200} );

 Chassis.waitUntil(70);

Chassis.moveToPoint(-40, -22, 800, false, 90);


Chassis.moveToPose(-1, -1, 45, 1600, {.forwards = true, .chasePower = 200});

Chassis.turnToHeading(-90, 500, true); //turns to go into alley 

Chassis.turnToHeading(180, 600, true);

Chassis.moveToPose(-3, 71, 180, 2000, {.forwards = false, .chasePower = 200}); // going under alley 


Chassis.moveToPose(-59, 104, 90, 800, {.forwards = false, .chasePower = 200}); 
flapjack2.set_value(true);
pros::delay(100);

Chassis.moveToPoint(-50, 104, 1100, false, 95); //first push from side 
Chassis.waitUntilDone();
Chassis.cancelAllMotions();
 flapjack2.set_value(false);
 Chassis.moveToPose(-15, 91, 135, 1000, {.forwards = true, .chasePower = 200});
// going under alley 
//Chassis.moveToPoint(-27, 104, 1200, true, 100); //first push from side
pros::delay(100);

Chassis.moveToPoint(-50, 104, 800, false, 100); //first push from side 
pros::delay(100);

Chassis.moveToPose(-15, 100, 135, 1000, {.forwards = true, .chasePower = 200}); // moves out from alley (START BY CHANGING THIS)


Chassis.turnToHeading(45, 1000, {.minSpeed = 90}, true);

//Chassis.moveToPoint(-25, 82, 500, false, 127);
flapjack2.set_value(true);

Chassis.moveToPose(-42, 82, 90, 1000, {.forwards = false, .chasePower = 200}); //gets in position to push the tb (w left flap open


Chassis.moveToPoint(-47, 82, 500, false, 127 ); 
Chassis.waitUntilDone();
Chassis.cancelAllMotions();
flapjack2.set_value(false);


Chassis.moveToPoint(-37, 82, 500, true, 127);



Chassis.turnToHeading(0, 700, true); // turns to go to the middle barrier 
Chassis.waitUntilDone();
Chassis.cancelAllMotions();


Chassis.moveToPoint(-37, 67, 1000, false, 127);
flapjack2.set_value(true);

Chassis.turnToHeading(65, 600, true);

Chassis.moveToPoint(-47, 62, 1000, false, 100);

Chassis.turnToHeading(135, 600, true);
Chassis.waitUntilDone();
Chassis.cancelAllMotions();
flapjack1.set_value(true);
flapjack2.set_value(true);


Chassis.moveToPoint(-72, 140, 1500, false, 90); // PUSH #1
Chassis.waitUntilDone();
Chassis.cancelAllMotions();
flapjack1.set_value(false);
flapjack2.set_value(false);


Chassis.moveToPose(-44, 66, 180, 1500, {.forwards = true, .chasePower = 200}); // goes back to where it came from 


Chassis.turnToHeading(90, 500, true);
Chassis.waitUntilDone();
Chassis.cancelAllMotions();
flapjack2.set_value(true);


Chassis.moveToPoint(-108, 66, 1700, false, 60); //moving along middle barrier for second psuh 

Chassis.turnToHeading(195, 600,  {.minSpeed = 40}, true); //angle for second push 
Chassis.waitUntilDone();
Chassis.cancelAllMotions();
flapjack1.set_value(true);
flapjack2.set_value(true);


Chassis.moveToPoint(-69.5, 127, 1500, false, 100); // PUSH #2

pros::delay(1100);
flapjack2.set_value(false);

Chassis.waitUntilDone();
Chassis.cancelAllMotions();
pros::delay(200);
flapjack1.set_value(false);


Chassis.moveToPoint(-90, 73, 700, true, 127); //moves back to middle barrier 


Chassis.turnToHeading(270, 500, true);

Chassis.moveToPoint(-55, 72, 1000, false ,127);

Chassis.turnToHeading(180, 500, true); //angle for third push

Chassis.moveToPoint(-55, 140, 1000, false, 100); // PUSH #3
flapjack1.set_value(true);
flapjack2.set_value(true);
Chassis.waitUntilDone();
Chassis.cancelAllMotions();
flapjack1.set_value(false);
flapjack2.set_value(false);

Chassis.moveToPoint(-52, 75, 1000, true, 127); 

Chassis.turnToHeading(90, 1000, true);
Chassis.waitUntilDone();
Chassis.cancelAllMotions();
flapjack1.set_value(true);
flapjack2.set_value(true);

Chassis.moveToPoint(-85, 73, 1000, false, 127);

Chassis.turnToHeading(155, 500, true);

Chassis.turnToHeading(140, 500, true);

///Chassis.moveToPose(-113, 104, 152, 2000, {.forwards = false, .chasePower = 200}); // pushes into the corner (last corner)


Chassis.moveToPoint(-108, 101, 1000, false, 127);


flapjack2.set_value(true);
Chassis.waitUntilDone();
Chassis.cancelAllMotions();




Chassis.turnToHeading(-118, 1000, {.minSpeed = 20},  true);
Chassis.waitUntilDone();
Chassis.cancelAllMotions();
flapjack2.set_value(false);

// Chassis.moveToPose(-124, 72, 180, 1000, {.forwards = true, .chasePower = 200}); //backs up into alley 
// Chassis.moveToPose(-116, 108, -135, 2000, {.forwards = false, .chasePower = 200});
// flapjack2.set_value(true);


Chassis.moveToPose(-94, 120, 270, 600, {.forwards = false, .chasePower = 200} );


Chassis.moveToPoint(-18, 120, 1000, false, 127);
Chassis.waitUntilDone();
Chassis.cancelAllMotions();


Chassis.moveToPose(-99, 114, 265, 600, {.forwards = false, .chasePower = 200} );

Chassis.moveToPose(-94, 120, 270, 600, {.forwards = false, .chasePower = 200} );


Chassis.moveToPoint(-18, 120, 1000, false, 127);
Chassis.waitUntilDone();
Chassis.cancelAllMotions();

Chassis.tank(70,70);

pros::delay(300);

Chassis.tank(0,0);

}
 




void farTB() {
    
 // initializations
  Chassis.setPose(0, 0, 0); 
  pros::delay(50);
   Chassis.setBrakeMode(MOTOR_BRAKE_BRAKE); // dont wanna get pushed around by other bots 
  
  // drop intake
  intakeMotor1.moveVelocity(600);
  balance.set_value(true);
  pros::delay(750);

  // drive towards mlzb & swing turn that pushes mlztb out 
  Chassis.moveToPoint(0,-24.5, 600, false, 127, true); // -25.5
  balance.set_value(false);
  //Chassis.moveToPose(15, -48, -45, 1000, {.forwards = false, .chasePower=200}, true); //13.5 -46   // ADD BACK IF NEED 2 SEPARATE MOVEMENTS TO REMOVE MLZ TB
  Chassis.moveToPose(16, -51, -45, 1000, {.forwards = false, .chasePower=200}, true); //goes closer to perimeter 15 -47 // consolidates 2 movements for removing mlz tb
  pros::delay(100); // not an actual delay; prevents wing opening right after the moveToPose function starts
  flapjack1.set_value(true);
  //intakeMotor1.moveVelocity(0); //stop intake
  
  // move towards side of goal
  Chassis.waitUntilDone();
  pros::delay(200);

  //Chassis.moveToPose(16, -52, -45, 1500, {.forwards = false, .chasePower=200}, true); //goes closer to perimeter 15 -47 // ADD BACK IF NEED 2 SEPARATE MOVEMENTS TO REMOVE MLZ TB
  Chassis.moveToPose(25, -52, -90, 700, {.forwards = false, .chasePower=200}, true); //pushes 2 tbs next to goal

  // scores first 2 tbs (preload + mlz)
  //Chassis.moveToPose(40, -52, -90, 700, {.forwards = false, .chasePower=200, .minSpeed=127}, true); //scores 2 tbs into goal ADD BACK IF MOVE TO POINT DOESNT WORK
  Chassis.moveToPoint(40,-52, 600, false, 127, true); //scores 2 tbs into goal
  flapjack1.set_value(false);

  // scores alley tb
  Chassis.moveToPoint(26,-52, 700, true, 127, true); //move  away from goal 30x  27.5 -52
  Chassis.turnTo(100, -52, 1000, true, 127, true); //turn to face goal
  pros::delay(500); // outtake line begins at the very end of the turnTo function
  //Chassis.waitUntilDone();
  intakeMotor1.moveVelocity(-600);
  Chassis.moveToPoint(42,-52, 700, true, 127, true); //score alley tb into goal
  //intakeMotor1.moveVelocity(0);
  //Chassis.setPose(29, -52, 90); 

  //pros::delay(2000);

  //Chassis.setPose(0, 0, 90); 


  // start 3 clump
  //Chassis.moveToPose(30, -48, 45, 2000, {.forwards = false, .chasePower = 200}, true);  //align w perim 

  Chassis.turnToHeading(0,1000);
  //Chassis.turnTo(100, 0, 1000, true, 127, true); //turn to 1st tb clump
  //pros::delay(3000);


 
  //Chassis.moveToPose(26, -52, 0, 2000, {.forwards = false, .chasePower = 200}, true);  //align w perim  BEFORE 30     26
  //Chassis.waitUntilDone();
  //Chassis.turnTo(34, -6, 750, true, 127, true); //turn to face tb clump #1
  //Chassis.moveToPoint(34,-6, 700, true, 127, true); //move to 1st tb clump
  
  Chassis.moveToPose(32, -5, 20, 2000, {.forwards = true, .chasePower = 200}, true);  //1st clump  32.5 -4.1      36 -5   -6   24.6    33 -6
  pros::delay(700); // delay opening of balance
  intakeMotor1.moveVelocity(600);
  balance.set_value(true);
  Chassis.waitUntilDone();
  pros::delay(100); // intaking delay

  //intakeMotor1.moveVelocity(0);

  Chassis.moveToPose(40, -6, 150, 4000, {.forwards = true, .chasePower = 200}, true);  //outtake 1st clump 43.5 -17.5    52    43 -15  50 -9      47.5 -9     46 -8
  //Chassis.turnToHeading(135,1000);
  //Chassis.waitUntilDone();
  //Chassis.cancelAllMotions();
  pros::delay(600); // delay outtaking

  intakeMotor1.moveVelocity(-600);
  //pros::delay(100); // delay outtaking
  //Chassis.waitUntilDone();
  //Chassis.cancelAllMotions();

  //pros::delay(3000); // temp testing delay

  Chassis.moveToPose(55, -0.75, 45, 1000, {.forwards = true, .chasePower = 200}, true);  //2nd clump 58 -1.7 30   PREEV 62, 2    50    56 -0.5
  intakeMotor1.moveVelocity(600);
  pros::delay(2000); // delay intaking
  Chassis.turnTo(60, -100, 700, true, 80, true); // turning to face goal //60
  //Chassis.turnToHeading(-180,1000);
  //Chassis.waitUntilDone();
  //Chassis.cancelAllMotions();
  pros::delay(500); // delay outtaking

  flapjack1V.set_value(true); // either v wing code works
  balance.set_value(false); // either v wing code works
  intakeMotor1.moveVelocity(-600);
  //pros::delay(500);

  //Chassis.moveToPose(65, -40, -180, 1500, {.forwards = true, .chasePower = 200}, true);  //score 3 //67
  Chassis.moveToPoint(60,-40, 1000, true, 127, true); //score front 3
  //Chassis.moveToPoint(60,-20, 700, false, 127, true); //move back
  Chassis.moveToPose(50, -20, 0, 1000, {.forwards = false, .chasePower = 200}, true);  //move back
  pros::delay(300); // delay wings
  flapjack1V.set_value(false); // either v wing code works
  intakeMotor1.moveVelocity(0);
  Chassis.turnToHeading(0,1000);

  //pros::delay(500);
  //Chassis.setBrakeMode(MOTOR_BRAKE_COAST); // for testing purposes only

  //Chassis.moveToPose(-30, 7.5, 90, 4000, {.forwards = false, .chasePower = 200}, true);  //move back

 

  /* REFERENCE FUNCTIONS
  Chassis.setPose(0, 0, 0);  
  Chassis.moveToPose(x, y, theta, 4000, {.forwards = true, .chasePower = 20, .minSpeed = 270}, true);
  Chassis.moveToPoint(x,y, 4000, true, 127, true);
  Chassis.turnTo(x, y, 4000, true, 127, true);
  Chassis.tank(left, right);

  Chassis.waitUntilDone();
  pros::delay(100);

  flapjack2.set_value(true); // left wing
  flapjack1.set_value(true); // right wing
  flapjack1V.set_value(true); // either v wing code works
  flapjack2V.set_value(true); // either v wing code works
  balanceTrue();
  balanceInit();
  
  intakeMotor1.moveVelocity(-600);
  */

}

void farSide() {
 // initializations
  Chassis.setPose(0, 0, 0); 
  pros::delay(50);
   Chassis.setBrakeMode(MOTOR_BRAKE_BRAKE); // dont wanna get pushed around by other bots 
  
  // drop intake
  intakeMotor1.moveVelocity(600);
  balance.set_value(true);
  pros::delay(750);

  // drive towards mlzb & swing turn that pushes mlztb out 
  Chassis.moveToPoint(0,-24.5, 600, false, 127, true); // -25.5
  balance.set_value(false);
  //Chassis.moveToPose(15, -48, -45, 1000, {.forwards = false, .chasePower=200}, true); //13.5 -46   // ADD BACK IF NEED 2 SEPARATE MOVEMENTS TO REMOVE MLZ TB
  Chassis.moveToPose(16, -51, -45, 1000, {.forwards = false, .chasePower=200}, true); //goes closer to perimeter 15 -47 // consolidates 2 movements for removing mlz tb
  pros::delay(100); // not an actual delay; prevents wing opening right after the moveToPose function starts
  flapjack1.set_value(true);
  //intakeMotor1.moveVelocity(0); //stop intake
  
  // move towards side of goal
  Chassis.waitUntilDone();
  pros::delay(200);

  //Chassis.moveToPose(16, -52, -45, 1500, {.forwards = false, .chasePower=200}, true); //goes closer to perimeter 15 -47 // ADD BACK IF NEED 2 SEPARATE MOVEMENTS TO REMOVE MLZ TB
  Chassis.moveToPose(25, -52, -90, 700, {.forwards = false, .chasePower=200}, true); //pushes 2 tbs next to goal

  // scores first 2 tbs (preload + mlz)
  //Chassis.moveToPose(40, -52, -90, 700, {.forwards = false, .chasePower=200, .minSpeed=127}, true); //scores 2 tbs into goal ADD BACK IF MOVE TO POINT DOESNT WORK
  Chassis.moveToPoint(40,-52, 600, false, 127, true); //scores 2 tbs into goal
  flapjack1.set_value(false);

  // scores alley tb
  Chassis.moveToPoint(26,-52, 700, true, 127, true); //move  away from goal 30x  27.5 -52
  Chassis.turnTo(100, -52, 1000, true, 127, true); //turn to face goal
  pros::delay(500); // outtake line begins at the very end of the turnTo function
  //Chassis.waitUntilDone();
  intakeMotor1.moveVelocity(-600);
  Chassis.moveToPoint(42,-52, 700, true, 127, true); //score alley tb into goal
  //intakeMotor1.moveVelocity(0);
  //Chassis.setPose(29, -52, 90); 

  //pros::delay(2000);

  //Chassis.setPose(0, 0, 90); 


  // start 3 clump
  //Chassis.moveToPose(30, -48, 45, 2000, {.forwards = false, .chasePower = 200}, true);  //align w perim 

  Chassis.turnToHeading(0,1000);
  //Chassis.turnTo(100, 0, 1000, true, 127, true); //turn to 1st tb clump
  //pros::delay(3000);


 
  //Chassis.moveToPose(26, -52, 0, 2000, {.forwards = false, .chasePower = 200}, true);  //align w perim  BEFORE 30     26
  //Chassis.waitUntilDone();
  //Chassis.turnTo(34, -6, 750, true, 127, true); //turn to face tb clump #1
  //Chassis.moveToPoint(34,-6, 700, true, 127, true); //move to 1st tb clump
  
  Chassis.moveToPose(32, -5, 20, 2000, {.forwards = true, .chasePower = 200}, true);  //1st clump  32.5 -4.1      36 -5   -6   24.6    33 -6
  pros::delay(700); // delay opening of balance
  intakeMotor1.moveVelocity(600);
  balance.set_value(true);
  Chassis.waitUntilDone();
  pros::delay(100); // intaking delay

  //intakeMotor1.moveVelocity(0);

  Chassis.moveToPose(40, -6, 150, 4000, {.forwards = true, .chasePower = 200}, true);  //outtake 1st clump 43.5 -17.5    52    43 -15  50 -9      47.5 -9     46 -8
  //Chassis.turnToHeading(135,1000);
  //Chassis.waitUntilDone();
  //Chassis.cancelAllMotions();

  intakeMotor1.moveVelocity(0);

  Chassis.moveToPose(50, -34, 180, 4000, {.forwards = true, .chasePower = 200}, true);

  Chassis.moveToPose(24, -5, 90, 4000, {.forwards = false, .chasePower = 200}, true);


}
    
  



void autonomous() {


 //skills(); 
 //closeSide();
 closeSideDisrupt();
 //farSide();
 //farTB();
 //closeSideNEW();


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

balanceTrue();

pros::delay(200);

balanceInit();


Chassis.moveToPose(-27, -19, 60, 2500, {.forwards = false, .chasePower = 20, .minSpeed = 110});
  Chassis.waitUntil(70);

Chassis.tank(-60, -60);
pros::delay(350);
Chassis.tank(0, 0);

//-7.36,31/6,44.3

Chassis.moveToPose(-7.5, -4, 45, 2000, {.forwards = true, .chasePower = 20});
  Chassis.waitUntilDone();
  flapjack2.set_value(true);
pros::delay(300);

  Chassis.turnTo(-11, -4, 2000);

pros::delay(680);
  flapjack2.set_value(false);

  intakeMotor1.moveVelocity(-600);

Chassis.moveToPose(-3, 35, 0, 3000, {.forwards = true, .chasePower = 20});
   Chassis.waitUntilDone();

*/






    /*
  ______________________________________________________________________________________________

  Far Side AWP (need to do file handling uh)
  ______________________________________________________________________________________________

*/


//NEW FAR SIDE RUN THIS FOR GOOGLE
 
/*
Chassis.setPose(0, 0, 0);
balanceTrue();

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

pros::delay(600);

Chassis.tank(0 , 0);

Chassis.moveToPoint(-5, 68, 1000, false, 127);

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
bool hasRunMacro = false;

void opcontrol() {
  
 
  pros::Controller controller1(pros::E_CONTROLLER_MASTER);
   

  int reverseDrive = 2;
  int driveState = 0;


Chassis.setBrakeMode(MOTOR_BRAKE_COAST);
    
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
       


          if (controller.getDigital(ControllerDigital::X) == 1 && ! hasRunMacro) {
                Chassis.setPose(0, 0, 39);
                pros::delay(200);

                balance.set_value(true);
                //Chassis.setBrakeMode(MOTOR_BRAKE_COAST);


                Chassis.moveToPoint(-8.6, -10.2, 1000, false, 127);

                Chassis.turnToHeading(-26, 600, true); // -27 deg, 500 kill timer
                pros::delay(100);

                flapjack1V.set_value(true);


                Chassis.moveToPoint(-8.4, -16.2, 1000, false, 127);
                balance.set_value(false);
                pros::delay(200);
                flapjack1V.set_value(false);
                Chassis.setBrakeMode(MOTOR_BRAKE_COAST);
                //cataMotor.moveVoltage(12000);


                hasRunMacro = true;
                //pros::delay(200);
                //pros::delay(200);
                
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
           // updateBlocker();
            //DarshyMech();
           // PtoMech()

           mech();

          

       


           
           pros::delay(10);
}
}