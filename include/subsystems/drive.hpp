#include "main.h"


using namespace okapi;

extern lemlib::Chassis Chassis;



extern Motor rightFront;
extern Motor rightBack;
extern Motor rightTop;

extern Motor leftFront;
extern Motor leftBack;
extern Motor leftTop;

extern okapi::MotorGroup left;
extern okapi::MotorGroup right;

// reverse

extern Motor RVrightFront;
extern Motor RVrightBack;
extern Motor RVrightTop;

extern Motor RVleftFront;
extern Motor RVleftBack;
extern Motor RVleftTop;


extern okapi::MotorGroup RVleft;
extern okapi::MotorGroup RVright;


extern std::shared_ptr<OdomChassisController> drive1;
extern std::shared_ptr<OdomChassisController> RVdrive;
extern std::shared_ptr<OdomChassisController> driveTemp;

//okapi::IntegratedEncoder leftEncoder;

void updateDrive();
void updateRVDrive();