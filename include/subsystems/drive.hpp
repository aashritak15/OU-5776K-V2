#include "main.h"

using namespace okapi;

extern Motor right;
extern Motor left;

static Controller controller;

extern std::shared_ptr<OdomChassisController> drive;

void updateDrive();