#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include <chrono>

using namespace okapi;


const std::uint8_t leftFrontPort = 11; //drivetrain motor 1
const std::uint8_t rightFrontPort = 9; //drivetrain motor 2

const std::uint8_t rightBackPort = 12; //drivetrain motor 2
const std::uint8_t leftBackPort = 4; //drivetrain motor 2

const std::uint8_t rightTopPort = 19; //drivetrain motor 2
const std::uint8_t leftTopPort = 10; //drivetrain motor 2

//const std::uint8_t imuPort1 = 9; //imu port #1
//const std::uint8_t imuPort2 = 10; //imu port#2

const std::uint8_t pistonPTO1Port = 8; //piston port
const std::uint8_t intakePort = 20; //intake port

//leftFront, leftBack, rightBack, rightTop, 