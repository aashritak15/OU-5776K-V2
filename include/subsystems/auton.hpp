#include "main.h"

using namespace okapi;

void updateAuton(int side);

void intakeAuton(IntakeState currentIntakeState);

enum class CataState{
    STOPPED = 0,
    CONTINUE = 1;
};


void cataAuton(CataState currentCataState);

void cataAuton();
