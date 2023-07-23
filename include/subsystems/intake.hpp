#include "main.h"

using namespace okapi;

extern Motor intakeMotor1;
extern Motor intakeMotor2;

void intakeInnit();
void updateIntake();

enum class IntakeState{
    STOPPED = 0,
    INTAKING = 1, 
    OUTTAKING = 2,
};

extern IntakeState getIntakeState();
extern void setIntakeState(IntakeState IState);

static IntakeState currentIntakeState = IntakeState::STOPPED;
static IntakeState previousIntakeState = IntakeState::STOPPED;

void intakeInit();
void updateIntake();