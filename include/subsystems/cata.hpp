#include "main.h"

using namespace okapi;

extern Motor cataMotor;

void cataInnit();


enum class CataState{
    RUNNINGSLOW = 0,
    RUNNINGFAST = 1,
    STOPPED = 2,
};

void setCataState(CataState IState);

CataState getCataState();

  static CataState currentCataState = CataState::STOPPED;

void updateCata();