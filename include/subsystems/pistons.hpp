#include "main.h"

using namespace okapi;


extern pros::ADIDigitalOut pistonPTO1;
//extern pros::ADIDigitalOut autonFlipout;
extern pros::ADIDigitalOut flapjack1;
extern pros::ADIDigitalOut flapjack2;
extern pros::ADIDigitalOut flapjack1V;
extern pros::ADIDigitalOut flapjack2V;
extern pros::ADIDigitalOut intakeFlipout;
extern pros::ADIDigitalOut balance;
extern pros::ADIDigitalOut awpFlipout;

extern pros::ADIDigitalOut flapjack2CAT;

extern pros::ADIDigitalOut lMech;

extern pros::ADIDigitalOut blocker;

extern pros::ADIDigitalOut blocker1;

void mech();

//extern pros::ADIDigitalOut pistonPTO1;


void pistonsInnit();
void updatePistons();


void updateIntakeFlipout();
void updateFlapjack();
void updateIntakeFlipout();
void updatelMech();
void updateBalance();
void updateBlocker();
//void PtoInit();
//void PtoMech();


void lMechInit ();
void balanceInit();
void balanceTrue();
void blockerInit();
void DarshyMech();
//void flipoutMech();

//void flapjackCode();
