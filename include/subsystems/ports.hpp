#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include <chrono>

using namespace okapi;


const std::uint8_t leftFrontPort = 16; //drivetrain motor 1
const std::uint8_t rightFrontPort = 1; //drivetrain motor 2

const std::uint8_t rightBackPort = 20; //drivetrain motor 2
const std::uint8_t leftBackPort = 11; //drivetrain motor 2
 
const std::uint8_t rightTopPort = 10; //drivetrain motor 2
const std::uint8_t leftTopPort = 6; //drivetrain motor 2

const std::uint8_t imuPort1 = 4; //imu port #1
const std::uint8_t imuPort2 = 18; //imu port#2

const std::uint8_t pistonPTO1Port = 8; //piston port
const std::uint8_t intakePort1 = 7; //intake port
const std::uint8_t intakePort2 = 13;

