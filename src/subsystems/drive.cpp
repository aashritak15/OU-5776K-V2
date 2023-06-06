#include "main.h"
#include "ports.hpp"

using namespace okapi;

Motor right(rightPort, false, AbstractMotor::gearset::blue,
            AbstractMotor::encoderUnits::degrees);
Motor left(leftPort, false, AbstractMotor::gearset::blue,
           AbstractMotor::encoderUnits::degrees);

std::shared_ptr<OdomChassisController> drive =
    ChassisControllerBuilder()
        .withMotors({left}, {right})
        .withDimensions(AbstractMotor::gearset::blue,
                        {{4_in, 13.7_in}, imev5BlueTPR})
        .withSensors(left.getEncoder(), right.getEncoder())
        // Specify the tracking wheels diam (2.75 in), track (7 in), and TPR
        // (360)
        .withOdometry({{2.75_in, 7.5_in, 1_in, 2.75_in}, quadEncoderTPR})
        .buildOdometry();

static Controller controller = Controller();

void updateDrive() {
  drive->getModel()->tank(controller.getAnalog(ControllerAnalog::leftY),
                          controller.getAnalog(ControllerAnalog::rightY));

  left.setBrakeMode(AbstractMotor::brakeMode::coast);
  right.setBrakeMode(AbstractMotor::brakeMode::coast);
};