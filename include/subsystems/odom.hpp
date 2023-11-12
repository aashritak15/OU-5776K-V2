#include "main.h"
using namespace okapi;

//void encoderAvg();
//void movePID(float target, float maxV);

void turnClock(float degree, int ms);
void turnCounter(float degree, int ms);

void turnRIGHTONLY(float degree, int ms);

void turnLEFTONLY(float degree, int ms);

void turnRightTime(int ms, int Rvelocity, int Lvelocity);
void turnLeftTime(int ms, int Rvelocity, int Lvelocity);

//extern double displacement; 

//void drivetrain(double target);

void drivetrain(double target, int ms, double speed);

//void turnCounterclockwise(float degree, int ms);
//void turnClockwise(float degree, int ms);

void checkBalance();


void resetEncoders();
void imuInnit();

void IEInnit(); 





