#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/odo.hpp"
#include "subsystems/drive.hpp"
#include "subsystems/pistons.hpp"
#include "globals.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "okapi/impl/device/rotarysensor/integratedEncoder.hpp"
#include "pros/misc.h"

//#include "odom.hpp"
//#include "pistons.hpp"

using namespace okapi;


/*

All drive stuff moved to odom.cpp 

*/










/*
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

std::shared_ptr<OdomChassisController> drive1 =
    ChassisControllerBuilder()
        .withMotors(left, right)
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

*/

/*

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






  
}

*/

