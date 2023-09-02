#include "main.h"

using namespace okapi;


extern pros::ADIDigitalOut pistonPTO1;
//extern pros::ADIDigitalOut autonFlipout;
extern pros::ADIDigitalOut flapjack1;
//extern pros::ADIDigitalOut flapjack2;

extern pros::ADIDigitalOut intakeFlipout;

extern pros::ADIDigitalOut awpFlipout;


void pistonsInnit();
void updatePistons();
void extendFlapjack();
void retractFlapjack();
void stopFlapjack();
void flapjackCode();
void updateIntakeFlipout();

void updateFlapjack();
void updateIntakeFlipout();
void updatelMech();
void updateBalance();
//void updateBlocker();

//void flipoutMech();

//void flapjackCode();
