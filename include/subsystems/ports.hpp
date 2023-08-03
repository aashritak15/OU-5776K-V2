#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"

using namespace okapi;


const std::uint8_t leftFrontPort = 20;
const std::uint8_t rightFrontPort = 11; 

const std::uint8_t rightBackPort = 9;
const std::uint8_t leftBackPort = 1; 
 
const std::uint8_t rightTopPort = 6; 
const std::uint8_t leftTopPort = 10; 

const std::uint8_t imuPort1 = 13; //imu port #1
const std::uint8_t imuPort2 = 18; //imu port#2

const std::uint8_t pistonPort1 = 8;
const std::uint8_t flapjackPort1 = 3;
const std::uint8_t flapjackPort2 = 12;

const std::uint8_t intakePort1 = 7;
const std::uint8_t autonFlipoutPort = 13;

const std::uint8_t cataMotorPort = 19;
