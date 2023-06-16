#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include <chrono>

using namespace okapi;

// d-train ports

const std::uint8_t leftPort = 11;
const std::uint8_t rightPort = 12;
const std::uint8_t imuPort1 = 10; // assign port val
const std::uint8_t imuPort2 = 9;
const std::uint8_t pistonPTO1Port = 8; 