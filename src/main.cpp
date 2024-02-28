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

void closeSideDisrupt(){
  Chassis.setPose(0, 0, 0);

  intakeMotor1.moveVelocity(600);

  Chassis.moveToPoint(0, 51, 2000, true, 127);

  Chassis.waitUntilDone();



  balance.set_value(true);

  flapjack2V.set_value(true);
  intakeMotor1.moveVelocity(0);

  Chassis.turnTo(27, 51, 1000);
  Chassis.moveToPoint(30, 51, 2000, true, 80);

  Chassis.moveToPose(0, 10, 0, 2500, {.forwards = false, .chasePower = 20, .minSpeed = 110});

  balance.set_value(false);

  flapjack2V.set_value(false);

  Chassis.waitUntilDone();

    Chassis.turnTo(20, 10, 1000);

      Chassis.moveToPose(-29, 43, 180, 2500, {.forwards = false, .chasePower = 20, .minSpeed = 110});

      Chassis.turnTo(20, 10, 1000);

     // Chassis.moveToPoint(-29, 40, 2000);

  //hello
  
}

void closeSide(){

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

  
}

void farSide(){
 
  /*
//OLD FAR SIDE (GOOGLE)
  Chassis.setPose(0, 0, 0);

intakeMotor1.moveVelocity(600);

Chassis.moveToPoint(0, 51, 4000, true, 127); 

Chassis.turnTo(100, 51, 1000);

intakeMotor1.moveVelocity(-600);
Chassis.moveToPoint(11, 53, 1000, true, 127); 


Chassis.moveToPoint(0, 51, 4000, false, 127); //finishes scoring preload

Chassis.turnTo(-5, 39, 1000);


intakeMotor1.moveVelocity(600);

Chassis.moveToPoint(-5, 41, 5000, true,  80);

Chassis.turnTo(-20, 39, 1000);

Chassis.moveToPoint(-20, 41, 5000, true,  40);

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

*/ 

  /*
//NEW FAR SIDE
   Chassis.setPose(0, 0, 0);
balanceTrue();

intakeMotor1.moveVelocity(600);

Chassis.moveToPoint(0, 51, 4000, true, 127); 
Chassis.waitUntilDone();


Chassis.turnTo(100, 51, 1000);

intakeMotor1.moveVelocity(-600);



Chassis.moveToPoint(25, 53, 600, true, 127);

Chassis.moveToPoint(0, 51, 1000, false, 127);  //finishes scoring preload



Chassis.turnTo(-25, 49, 1000,  true);

intakeMotor1.moveVelocity(600);

Chassis.moveToPoint(-24, 45.54, 2000, true, 80);
Chassis.waitUntil(90);

Chassis.moveToPoint(-25, 40, 2000, false, 127);



Chassis.turnTo(-19, 52, 2000, true);

intakeMotor1.moveVelocity(0);

Chassis.moveToPoint(11, 60, 2000, true);

flapjack2V.set_value(true);

Chassis.moveToPoint(-2, 55, 2000, true);

Chassis.moveToPoint(4, 55, 2000, false);

Chassis.waitUntilDone();

flapjack2V.set_value(false);
Chassis.turnTo(-29, 40, 1000, false);


Chassis.moveToPoint(-29, 23, 2000, false);


flapjack1.set_value(true);

//Chassis.moveToPoint(13, 50.4 2000, true);


flapjack2V.set_value(true);

Chassis.moveToPoint(-6, 55, 2000, false);

Chassis.waitUntilDone();

flapjack2V.set_value(false);
Chassis.turnTo(-29, 40, 1000, false);


Chassis.moveToPoint(-29, 23, 2000, false);


flapjack1.set_value(true);



}




void skills() {

//going to score two preloads 
/*
 Chassis.setPose(0, 0, 45);


              Chassis.moveToPose(-27, -19, 60, 2500, {.forwards = false, .chasePower = 20, .minSpeed = 110});
              Chassis.waitUntil(70);


              Chassis.tank(-80, -80);
              pros::delay(400);
              Chassis.tank(0, 0);

              //going to matchload zone 
              //Chassis.moveToPoint(-13, -6, 2000, true, 80);
              Chassis.moveToPoint(-14, -4, 2000, true, 80);
              //Chassis.moveToPoint(-13, -6.5, 2000, true, 80);
              Chassis.waitUntilDone();

              
             
             
      
              // FATTTTTTTTTTSSSSSSS CHANGE ANGLE HERE


              // ***********************************************************

               
              Chassis.turnTo(-21.3, 8.8, 1000, true);

            balance.set_value(true);
            pros::delay(500);
            flapjack2V.set_value(true);
            pros::delay(500);
            balance.set_value(false);
          
              Chassis.moveToPoint(-12.96, -9, 2000, false, 40);
              Chassis.waitUntilDone();

              lemlib::Pose startingPose = Chassis.getPose();

              flapjack2V.set_value(false);
              //Chassis.moveToPoint(-21.4, -7.5, 2000, false, 40);

              
              flapjack2.set_value(true);

            

              cataMotor.moveVoltage(12000);

              pros::delay(20000);

              cataMotor.moveVoltage(0);

              flapjack2.set_value(false);

              pros::delay(200);

              Chassis.setPose(startingPose);

            pros::delay(50);

             Chassis.moveToPoint(-14, -5.91, 2000, true, 40);


              
             Chassis.turnTo(-7, 5.13, 1000, false);

             Chassis.moveToPoint(-7, 5.77, 400, false, 127);

             Chassis.turnTo(-7, 9.9, 400, false);

             //GOING UNDER ALLEY TO PUSH 

              Chassis.moveToPoint(-7, 50, 2000, false, 127);

               

             Chassis.moveToPoint(-7, 70, 2000, false, 127);

                flapjack2.set_value(true);

             Chassis.moveToPose(-15, 91.8, -225, 3000, {.forwards = false}); //IF ON DRC FIELD IT IS GETTING STUCK ON THE MLZ ZONE MAKE X MORE NEGATIVE
            
            flapjack2.set_value(false);
            Chassis.moveToPose(-40, 106, -250, 2500, {.forwards = false, .chasePower = 20, .minSpeed = 100});

         

            Chassis.tank(-80, -80);
              pros::delay(400);
              Chassis.tank(0, 0);


              Chassis.moveToPoint(-24, 103, 2000, true, 105);
              Chassis.waitUntil(15);
              Chassis.cancelAllMotions();

              Chassis.tank(-127, -127);
              pros::delay(900);
              Chassis.tank(0, 0);

              //Chassis.moveToPoint(-31, 104, 2000, true, 127);

              flapjack2.set_value(false);

      

              Chassis.moveToPoint(-21.2, 93, 2000, true, 127);


              Chassis.turnTo(-32, 77, 1000, false);
              flapjack2.set_value(true);

              Chassis.moveToPoint(-32, 77, 2000, false, 127);

              Chassis.turnTo(-33, 70, 1000, false);

              Chassis.moveToPoint(-32.7, 66.7, 2000, false, 127);

              Chassis.turnTo(-46, 63, 1000, false);
              Chassis.waitUntilDone();

               Chassis.moveToPoint(-46, 63, 2000, false, 127);

               Chassis.turnTo(-42, 59, 1000, true);

               flapjack1.set_value(true);

                Chassis.moveToPoint(-62, 90, 2000, false, 127);
                Chassis.waitUntil(35);
              Chassis.cancelAllMotions();

                Chassis.tank(-100, -100);
              pros::delay(500);
              Chassis.tank(0, 0);


              Chassis.moveToPoint(-48, 59, 3000, true, 127);

              

              flapjack1.set_value(false);
              flapjack2.set_value(false);

              Chassis.turnTo(-46, 63, 1000, true);

              Chassis.moveToPoint(-85, 63, 2000, false, 127);

              Chassis.turnTo(-79, 82, 1000, false);
              flapjack1.set_value(true);
              flapjack2.set_value(true);

              Chassis.moveToPoint(-75, 82, 2000, false, 127);
              Chassis.waitUntil(35);
              Chassis.cancelAllMotions();

              Chassis.tank(-100, -100);
              pros::delay(500);
              Chassis.tank(0, 0);

              Chassis.moveToPoint(-85, 63, 2000, true, 127);

               Chassis.turnTo(-79, 82, 1000, false);
              flapjack1.set_value(true);
              flapjack2.set_value(true);

              Chassis.moveToPoint(-75, 82, 2000, false, 127);
              Chassis.waitUntil(35);
              Chassis.cancelAllMotions();

              Chassis.tank(-100, -100);
              pros::delay(500);
              Chassis.tank(0, 0);


              
            */







/*

              flapjack1.set_value(true);
              flapjack2.set_value(true);

              Chassis.moveToPoint(-43, 65, 2000, false, 127);

              flapjack1.set_value(false);

              Chassis.turnTo(-44.92, 73.34, 1000, false);

              flapjack2.set_value(true);

              Chassis.moveToPoint(-55, 90, 2000, false, 127);

              Chassis.waitUntil(45);

              Chassis.cancelAllMotions();

              Chassis.tank(-100, -100);
              pros::delay(700);
              Chassis.tank(0, 0);

               

*/
              
             
             
/*
pros::delay(500);
Chassis.moveToPoint(-10.26, -9, 2000, false, 40);



flapjack2.set_value(false);

// going to barrier to push over tribals over 


Chassis.moveToPoint(-38, 19, 3000, true, 90);

intakeMotor1.moveVelocity(-600); 

Chassis.turnTo(-48, 19, 3000);
Chassis.waitUntilDone();

flapjack1V.set_value(true);

flapjack2V.set_value(true);
Chassis.moveToPoint(-83, 19, 3000, true);

pros::delay(200);

//Chassis.turnTo(-37, 23, 1000);

balanceInit();

Chassis.moveToPoint(-120, 19, 3000, true, 50);
Chassis.waitUntilDone();

flapjack1V.set_value(false);

flapjack2V.set_value(false);

Chassis.turnTo(-110, 2, 1000, false);

Chassis.moveToPoint(-110, 2, 3000, false, 50);

Chassis.turnTo(-136, -3, 1000, false);

Chassis.moveToPoint(-136, -3, 3000, false, 50);

Chassis.turnTo(-143, 12, 1000, false);
*/

/*
flapjack1V.set_value(true);

flapjack2V.set_value(true);

intakeMotor1.moveVelocity(-600); 


Chassis.moveToPoint(-80, 20, 3000, true, 127);

Chassis.moveToPoint(-107, 20, 3000, true, 90);

//going under alley 

pros::delay(1000);

flapjack1V.set_value(false);

flapjack2V.set_value(false);
balanceInit();

Chassis.turnTo(-92, 2, 1000, false);

Chassis.moveToPoint(-98, 14, 2000, false, 90);


Chassis.turnTo(-110, -4, 1000, false);
Chassis.moveToPoint(-130, -3, 2000, false, 90);

Chassis.turnTo(-136, 20, 1000, false);
Chassis.waitUntilDone();


flapjack1.set_value(true);
flapjack2.set_value(true);

Chassis.moveToPoint(-136, 70, 2000, false, 90);



flapjack1.set_value(false);

Chassis.moveToPose(-100, 113, 245, 5000,{.forwards = false, .minSpeed = 127});

Chassis.tank(-60, -60);

pros::delay(400);

Chassis.tank(0, 0);


Chassis.moveToPoint(-124, 94, 3000, true, 127);
Chassis.turnTo(-91, 52, 3000, true);
Chassis.moveToPoint(-91, 52, 3000, true,  127);
Chassis.turnTo(-87, 65, 3000, false, 127);

flapjack1.set_value(true);
flapjack2.set_value(true);

Chassis.moveToPoint(-85, 98, 3000, false, 127);

Chassis.waitUntil(55);

flapjack1.set_value(false);
flapjack2.set_value(false);

Chassis.moveToPoint(-59, 61, 3000, true, 127);

Chassis.turnTo(-59, 100, 3000, false);


flapjack1.set_value(true);
flapjack2.set_value(true); 

Chassis.moveToPoint(-59, 100, 3000, false, 127);

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

//Chassis.moveToPose(4, -11, -77, 2000, {.forwards = true, .minSpeed = 90});
//Chassis.turnTo(-18, -4, 1000);
Chassis.moveToPoint(-13, -6, 2000, true, 80);

Chassis.turnTo(-17, -0, 1000);
Chassis.moveToPoint(-11, -10, 2000, false, 80);

cataMotor.moveVelocity(10000);

pros::delay(5000);

cataMotor.moveVelocity(0);



//BARRIER PUSH BARRIER PUSH 


Chassis.moveToPoint(20, -5, 3000, true, 90);

Chassis.turnTo(20, -2, 1000);
/*
balanceTrue();
pros::delay(100);
flapjack1V.set_value(true);

flapjack2V.set_value(true);

Chassis.moveToPoint(-94, 23, 3000, true, 127);

pros::delay(2000);

flapjack1V.set_value(false);

flapjack2V.set_value(false);
balanceInit();

Chassis.turnTo(-92, 2, 1000);

Chassis.moveToPoint(-92, 2, 2000, true, 90);


Chassis.turnTo(-110, -4, 1000);
Chassis.moveToPoint(-110, -4, 2000, true, 90);

Chassis.turnTo(-122, 20, 1000);
Chassis.moveToPoint(-122, 20, 2000, true, 90);
*/
/*

ALLEY PUSH ALLEY PUSH 

Chassis.moveToPose(-5, 35, 185, 3000, {.forwards = false, .chasePower = 20});
//Chassis.turnTo(-12, 82, 1000, false);

Chassis.moveToPoint(-5, 80, 2000, false, 80);
Chassis.turnTo(-13, 83, 1000, false);

Chassis.moveToPose(-44, -96, 0, 2500, {.forwards = false, .chasePower = 20, .minSpeed = 110});
*/

}
 
void farTB() {
    
  //initializations
  Chassis.setPose(0, 0, 0);  
  Chassis.setBrakeMode(MOTOR_BRAKE_BRAKE);
  
  //drop intake
  intakeMotor1.moveVelocity(600);
  balance.set_value(true);
  pros::delay(400);

  //drive towards mlzb
  Chassis.moveToPoint(0,-26.5, 4000, false, 127, true); //25y
  balance.set_value(false);

  // swing turn that pushes mlztb out 
  //Chassis.moveToPose(10.7, -42, -45, 4000, {.forwards = false, .chasePower=100}, true);  
  Chassis.moveToPose(14, -48, -45, 4000, {.forwards = false, .chasePower=200}, true); //13.5 -46  
  pros::delay(100); // not an actual delay; prevents wing opening right after the moveToPose function starts
  flapjack1.set_value(true);
  //pros::delay(1500); 
  //flapjack1.set_value(false);
  intakeMotor1.moveVelocity(0); //stop intake
  
  //move towards side of goal
  Chassis.waitUntilDone();
  //Chassis.moveToPoint(15, -47, 1500, false, 127, true);
  Chassis.moveToPose(16, -52, -45, 1500, {.forwards = false, .chasePower=200}, true); //goes closer to perimeter 15 -47
  Chassis.moveToPose(25, -50, -70, 700, {.forwards = false, .chasePower=200}, true); //pushes 2 tbs next to goal
 // REPLACE PREVIOUS LINE WITH SWING TURN + MOVE BACK 

  //scores first 2 tbs (preload + mlz)
  //Chassis.moveToPoint(40, -50, 1000, false, 127, true); //scores tbs
  //scores tbs
  Chassis.tank(-127,-127,0);
  pros::delay(300);
  Chassis.tank(0,0,0);
  flapjack1.set_value(false);

  //score alley tb
  Chassis.moveToPoint(25,-50, 1000, true, 127, true); //move forward away from goal and get ready to turn 
  Chassis.turnTo(100, -50, 1000, true, 127, true);
  pros::delay(300); // outtake line begins at the very end of the turnTo function
  intakeMotor1.moveVelocity(-600);
  //Chassis.waitUntil(85);
  //Chassis.cancelAllMotions();
  Chassis.moveToPoint(50,-50, 700, true, 127, true); //score alley tb into goal
  intakeMotor1.moveVelocity(0);
  pros::delay(3000); // temp testing delay
  Chassis.moveToPose(22, -50, 0, 2000, {.forwards = false, .chasePower = 100}, true);  //align w perim
  pros::delay(3000); // temp testing delay
  //Chassis.moveToPose(32.5, -4.1, 10, 2000, {.forwards = true, .chasePower = 20, .minSpeed = 270}, true);  //1st clump
  Chassis.moveToPose(32.5, -4.1, 10, 2000, {.forwards = true, .chasePower = 100}, true);  //1st clump
  intakeMotor1.moveVelocity(600);
  pros::delay(1000); // temp testing delay

  //balance.set_value(true); // either v wing code works*/

  //Chassis.moveToPose(43.5, -17.5, 150, 2000, {.forwards = true, .chasePower = 20, .minSpeed = 270}, true);  //outtake 2nd clump
  //intakeMotor1.moveVelocity(-600);

  //Chassis.moveToPose(52.5, -6, 46, 2000, {.forwards = true, .chasePower = 20, .minSpeed = 270}, true);  //2nd clump


  //Chassis.moveToPose(40, -47, -90, 2000, {.forwards = true, .chasePower = 20, .minSpeed = 270}, true);  //drive back to mlz and turn to remove mlztb

  //score tb in goal
  /*flapjack1V.set_value(true); // either v wing code works
  balance.set_value(false); // either v wing code works
  flapjack1V.set_value(true); // either v wing code works*/
  intakeMotor1.moveVelocity(0);
  pros::delay(2000);
  Chassis.setBrakeMode(MOTOR_BRAKE_COAST); // for testing purposes only
 

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



void autonomous() {

 //skills(); 
 //closeSide();
 //closeSideDisrupt();
 //farSide();
 farTB();


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


          if (controller.getDigital(ControllerDigital::left) == 1) {
             /*
             fatass code
             Chassis.setPose(0, 0, 45);
              balanceTrue();
              pros::delay(100);
              balanceInit();
              Chassis.moveToPose(-27, -19, 60, 2500, {.forwards = false, .chasePower = 20, .minSpeed = 110});
                Chassis.waitUntil(70);

              Chassis.tank(-50, -50);
              pros::delay(200);
              Chassis.tank(0, 0);

              //going to matchload zone 
              Chassis.moveToPoint(-13, -6, 2000, true, 80);

              Chassis.turnTo(-17, -0, 1000);
              Chassis.moveToPoint(-11, -10, 2000, false, 80);
              */
              Chassis.setPose(0, 0, 45);


              Chassis.moveToPose(-27, -19, 60, 2500, {.forwards = false, .chasePower = 20, .minSpeed = 110});
              Chassis.waitUntil(70);


              Chassis.tank(-80, -80);
              pros::delay(400);
              Chassis.tank(0, 0);

              //going to matchload zone 
              //Chassis.moveToPoint(-13, -6, 2000, true, 80);
              Chassis.moveToPoint(-11.5, -4, 2000, true, 80);
              //Chassis.moveToPoint(-13, -6.5, 2000, true, 80);
              Chassis.waitUntilDone();

              balanceTrue();
            pros::delay(100);
            flapjack1V.set_value(true);
            pros::delay(100);
            balanceInit();
            pros::delay(100);
            flapjack1V.set_value(false);
          
             
             
      
              // FATTTTTTTTTTSSSSSSS CHANGE ANGLE HERE


              // ***********************************************************

              Chassis.turnTo(-27.5, 28.5, 1000);
              //Chassis.moveToPoint(-6.5, -7, 2000, false, 40);
              Chassis.moveToPoint(-10.26, -7, 2000, false, 40);

              flapjack2.set_value(true);

              

              cataMotor.moveVoltage(12000);

              



              //flapjack2V.set_value(true);



              //calling button b goes here
              // balanceTrue();
              // pros::delay(100);
              // balanceInit();
              // pros::delay(1000);
              // flapjack1V.set_value(true);
              // flapjack2V.set_value(true);
              // pros::delay(100);
              // balanceFalse();
              // flapjack1V.set_value(false);
              // flapjack2V.set_value(false);
              
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