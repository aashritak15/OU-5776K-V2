#include "main.h"
#include "subsystems/ports.hpp"
#include "subsystems/odom.hpp"


using namespace okapi;

static Controller controller = Controller();

Motor rightFront(rightFrontPort, false, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

Motor rightTop(rightTopPort, false, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

Motor rightBack(rightBackPort, false, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);

Motor leftFront(leftFrontPort, true, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees);

Motor leftBack(leftBackPort, true, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees);

Motor leftTop(leftTopPort, true, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees);

okapi::MotorGroup left({leftFront, leftBack, leftTop});
okapi::MotorGroup right({rightFront, rightBack, rightTop});

std::shared_ptr<OdomChassisController> drive =
    ChassisControllerBuilder()
        .withMotors(left, right)
        .withDimensions(AbstractMotor::gearset::blue,
                        {{3.25_in, 13.7_in}, imev5BlueTPR})
        .withSensors(leftFront.getEncoder(), rightFront.getEncoder())
        // Specify the tracking wheels diam (2.75 in), track (7 in), and TPR
        // (360)
        .withOdometry()
        .buildOdometry();



void updateDrive() {
  drive->getModel()->tank(controller.getAnalog(ControllerAnalog::leftY),
                          controller.getAnalog(ControllerAnalog::rightY));

/*
  if (controller.getDigital(ControllerDigital::left) == 1) {
    leftFront.setBrakeMode(AbstractMotor::brakeMode::hold);
    leftBack.setBrakeMode(AbstractMotor::brakeMode::hold);
    leftTop.setBrakeMode(AbstractMotor::brakeMode::hold);

    rightFront.setBrakeMode(AbstractMotor::brakeMode::hold);
    rightBack.setBrakeMode(AbstractMotor::brakeMode::hold);
    rightTop.setBrakeMode(AbstractMotor::brakeMode::hold);
  }
  */

  /*
  if(controller.getDigital(ControllerDigital::right) == 1){
    leftFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftBack.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftTop.setBrakeMode(AbstractMotor::brakeMode::coast);

    rightFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightBack.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightTop.setBrakeMode(AbstractMotor::brakeMode::coast);
  }
  */

  if (controller.getDigital(ControllerDigital::Y) == 1) {
    movePID(24, 1);
  }
}


/*if(controller.getDigital(ControllerDigital::Y) == 1){
  drive(24.0);
}*/

/*
  if (controller.getDigital(ControllerDigital::B) == 1){
    turnPID(90, true, 3000);
  }
}
*/