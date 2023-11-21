#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"

using namespace okapi;


const std::uint8_t leftFrontPort = 11;
const std::uint8_t rightFrontPort = 12; 

const std::uint8_t rightBackPort = 19;
const std::uint8_t leftBackPort = 10; 
 
const std::uint8_t rightTopPort = 20; 
const std::uint8_t leftTopPort = 9; 

const std::uint8_t imuPort1 = 13; //imu port #1
const std::uint8_t imuPort2 = 4; //imu port#2

//const std::uint8_t pistonPort1 = 8;
const std::uint8_t flapjackPort1 = 'A';
//const std::uint8_t lMechPort = 'G';


const std::uint8_t blockerPort = 'H';
const std::uint8_t PtoPort = 'C';


const std::uint8_t intakePort1 = 1;
//const std::uint8_t autonFlipoutPort = 'A';

const std::uint8_t cataMotorPort = 2;

//imu is 13 