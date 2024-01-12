#include "main.h"

using namespace okapi;

extern Motor cataMotor;
extern RotationSensor spin;

void cataInit();
void updateCata();
void onePunch();


enum class CataState{
    STOPPED = 0,
    HI = 1, 
    //MED = 2,
    LO = 3,
};

void setCataState(CataState CState);

CataState getCataState();




extern CataState getCataState();
extern void setCataState(CataState CState);

static CataState currentCataState = CataState::STOPPED;
static CataState previousCataState = CataState::STOPPED;



 void updateDriverSkills();

