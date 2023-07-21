#include "main.h"

using namespace okapi;

extern Motor rightFront;
extern Motor rightBack;
extern Motor rightTop;

extern Motor leftFront;
extern Motor leftBack;
extern Motor leftTop;

extern okapi::MotorGroup left;
extern okapi::MotorGroup right;

static Controller controller;

extern std::shared_ptr<OdomChassisController> drive;

void updateDrive();