#include "main.h"

using namespace okapi;


extern pros::ADIDigitalOut pistonPTO1;
extern pros::ADIDigitalOut autonFlipout;
extern pros::ADIDigitalOut flapjack1;
extern pros::ADIDigitalOut flapjack2;



void pistonsInnit();
void flipoutMechInnit();
void updatePistons();
void extendFlapjack();
void retractFlapjack();
void stopFlapjack();
void flapjackCode();
void flipoutMech();

//void flapjackCode();
