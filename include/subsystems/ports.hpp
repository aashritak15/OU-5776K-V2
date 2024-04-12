#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"

using namespace okapi;

// orig
const std::uint8_t rightFrontPort = 11;
const std::uint8_t leftFrontPort = 12; 

const std::uint8_t leftBackPort = 19;
const std::uint8_t rightBackPort = 10; 
 
const std::uint8_t leftTopPort = 20; 
const std::uint8_t rightTopPort = 9; 

/* reverse left and right
const std::uint8_t rightFrontPort = 12;

const std::uint8_t leftFrontPort = 11; 

const std::uint8_t leftBackPort = 10;
const std::uint8_t rightBackPort = 19; 
 
const std::uint8_t leftTopPort = 9; 
const std::uint8_t rightTopPort = 20; */





const std::uint8_t imuPort1 = 14; //imu port #1
const std::uint8_t imuPort2 = 13; //imu port#2

//const std::uint8_t pistonPort1 = 8;
const std::uint8_t flapjackPort1 = 'B';
const std::uint8_t flapjackPort2 = 'H';

const std::uint8_t flapjackPort1V = 'F';
const std::uint8_t flapjackPort2V = 'F';

//const std::uint8_t lMechPort = 'G';


const std::uint8_t blockerPort = 'C';
const std::uint8_t blockerPort1 = 'E';

const std::uint8_t balancePort = 'D';


const std::uint8_t intakePort1 = 8;
const std::uint8_t intakePort2 = 10;

//const std::uint8_t autonFlipoutPort = 'A';

const std::uint8_t cataMotorPort = 5;

//imu is 13

const std::uint8_t hangPort1 = 'A';
