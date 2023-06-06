#include "main.h"


using namespace okapi;

pros::Motor right;
pros::Motor left;

extern std::shared_ptr<OdomChassisController> drive;


void updateDrive();