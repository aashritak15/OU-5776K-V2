#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/odo.hpp"
#include "subsystems/drive.hpp"
#include "subsystems/pistons.hpp"
#include "globals.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "okapi/impl/device/rotarysensor/integratedEncoder.hpp"
//#include "odom.hpp"
//#include "pistons.hpp"

using namespace okapi;



Motor rightFront(rightFrontPort, true, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

Motor rightTop(rightTopPort, false, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

Motor rightBack(rightBackPort, true, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

          

Motor leftFront(leftFrontPort, false, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees);

Motor leftBack(leftBackPort, false, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees);


Motor leftTop(leftTopPort, true, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees); 


okapi::IntegratedEncoder leftEncoder = IntegratedEncoder(20, true);


okapi::MotorGroup left({leftFront, leftTop, leftBack});
okapi::MotorGroup right({rightFront, rightTop, rightBack});



std::shared_ptr<OdomChassisController> drive =
    ChassisControllerBuilder()
        .withMotors(left, right)
        .withDimensions(AbstractMotor::gearset::blue,
                        {{3.25_in, 10._in}, imev5BlueTPR})
        .withSensors(leftFront.getEncoder(), rightFront.getEncoder())
        // Specify the tracking wheels diam (2.75 in), track (7 in), and TPR
        // (360)
        .withOdometry({{3.25_in, 14.5_in, 7.25_in, 3.25_in}, quadEncoderTPR})
        .buildOdometry();





void updateDrive() {
  drive->getModel()->tank(controller.getAnalog(ControllerAnalog::rightY),
                          controller.getAnalog(ControllerAnalog::leftY));

  
  if (controller.getDigital(ControllerDigital::right) == 1) {
    leftFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftTop.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftBack.setBrakeMode(AbstractMotor::brakeMode::coast);

    rightFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightTop.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightBack.setBrakeMode(AbstractMotor::brakeMode::coast);
  } 
 // thats what we did last item ya what did u change can u move ur curser to tehre rq
  else if (controller.getDigital(ControllerDigital::left) == 1) {
    leftFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftTop.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftBack.setBrakeMode(AbstractMotor::brakeMode::coast);

    rightFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightTop.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightBack.setBrakeMode(AbstractMotor::brakeMode::coast);
  } 

/*
 if (controller.getDigital(ControllerDigital::right) == 1) {
    int ms = 500000;
    int time = 0;
    leftEncoder.reset();
    while(time < ms){
      if (leftEncoder.get() >= 4400 && leftEncoder.get() <= 4800){
         pros::Controller master (pros::E_CONTROLLER_MASTER);
   
  
    
    
     
      master.print(0, 0, "STOP %i %s");
      master.rumble(".--. --");
      
    
  

         pistonPTO1.set_value(false);
         time = 500000;
      }

      time += 10;
    }
    
    drive->getModel()->tank(0,0);


  }

*/




  
}



//////




// reverse

/*
Motor RVrightFront(rightFrontPort, false, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

Motor RVrightTop(rightTopPort, true, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

Motor RVrightBack(rightBackPort, false, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

Motor RVleftFront(leftFrontPort, true, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees);

Motor RVleftBack(leftBackPort, true, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees);


Motor RVleftTop(leftTopPort, false, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees); 
          

okapi::MotorGroup RVleft({RVleftFront, RVleftTop, RVleftBack});
okapi::MotorGroup RVright({RVrightFront, RVrightTop, RVrightBack});

std::shared_ptr<OdomChassisController> RVdrive =
    ChassisControllerBuilder()
        .withMotors(RVleft, RVright)
        .withDimensions(AbstractMotor::gearset::blue,
                        {{3.25_in, 10._in}, imev5BlueTPR})
        .withSensors(leftFront.getEncoder(), rightFront.getEncoder())
        // Specify the tracking wheels diam (2.75 in), track (7 in), and TPR
        // (360)
        .withGains(
          {0.001, 0, 0.0001}, 
          {0.001, 0, 0.0001},  
          {0.001, 0, 0.0001})
        .withOdometry({{3.25_in, 14.5_in, 7.25_in, 3.25_in}, quadEncoderTPR})
        .buildOdometry();

std::shared_ptr<OdomChassisController> driveTemp;
    

bool reverse = false; 

*/

/*
// not switching at all

void updateRVDrive() {
  bool reverse = false;
  
  if (controller.getDigital(ControllerDigital::X) == 1){
    if(!reverse){
      drive->getModel()->tank(controller.getAnalog(ControllerAnalog::leftY),
                          controller.getAnalog(ControllerAnalog::rightY));
    } else {
      drive->getModel()->tank(controller.getAnalog(ControllerAnalog::rightY),
                          controller.getAnalog(ControllerAnalog::leftY));
      reverse = !reverse;
    }
    
  }
}
  
  */

