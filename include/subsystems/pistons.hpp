#include "main.h"

using namespace okapi;


extern pros::ADIDigitalOut pistonPTO1;
//extern pros::ADIDigitalOut autonFlipout;
extern pros::ADIDigitalOut flapjack1;
//extern pros::ADIDigitalOut flapjack2;

extern pros::ADIDigitalOut intakeFlipout;



void pistonsInnit();
void updatePistons();
void extendFlapjack();
void retractFlapjack();
void stopFlapjack();
void flapjackCode();
void updateIntakeFlipout();

void updateFlapjack();
void UpdateIntakeFlipout();

//void flipoutMech();

//void flapjackCode();
