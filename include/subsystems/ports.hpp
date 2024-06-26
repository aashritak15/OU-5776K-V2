#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"

using namespace okapi;

// orig
const std::uint8_t rightFrontPort = 12;
const std::uint8_t leftFrontPort =9; 

const std::uint8_t leftBackPort = 5;
const std::uint8_t rightBackPort = 14; 
 
const std::uint8_t leftTopPort = 4; 
const std::uint8_t rightTopPort = 13; 

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
const std::uint8_t flapjackPort1 = 'H';
const std::uint8_t flapjackPort2 = 'G';
const std::uint8_t flapjackPort3 = 'E';

const std::uint8_t flapjackPort1V = 'H';
const std::uint8_t flapjackPort2V = 'H';


//const std::uint8_t lMechPort = 'G';


const std::uint8_t blockerPort = 'C';
const std::uint8_t blockerPort1 = 'E';

const std::uint8_t balancePort = 'D';


const std::uint8_t intakePort1 = 20;
const std::uint8_t intakePort2 = 10;

//const std::uint8_t autonFlipoutPort = 'A';

const std::uint8_t cataMotorPort = 5;

//imu is 13

const std::uint8_t hangPort1 = 'A';
