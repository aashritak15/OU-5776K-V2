#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include <chrono>

using namespace okapi;

// d-train ports

const std::uint8_t leftPort = 11;
const std::uint8_t rightPort = 12;
