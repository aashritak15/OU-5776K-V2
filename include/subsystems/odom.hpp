#include "main.h"

using namespace okapi;

void encoderAvg();
//void movePID(float target, float maxV);
void turnPID(float target, bool CW, int ms);

extern double displacement; 

void drive(double target);

bool isMoving();

void imuInnit();
void IEInnit(); 