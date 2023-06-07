#include "main.h"
#include "subsystems/drive.hpp"

using namespace okapi;

IntegratedEncoder leftEncoder(left);
IntegratedEncoder rightEncoder(right);

void movePID(float target, float maxV) {
  leftEncoder.reset();
  rightEncoder.reset();
  float kP = 0.75;
  float kI = 0;
  float kD = 0;

  float power = 0;
  float totalError = 0;
  float currentTravel = 0; // [in]
  float targetTravel = currentTravel + target;    // [in]
  float prevError = 0;

 
  while (true){
    // Compute PID values from current wheel travel measurements
    currentTravel = ((leftEncoder.get() + rightEncoder.get())/2 * (4 * M_PI)) /840.0f;
       float error = targetTravel - currentTravel;
      if(error != 0){
    	totalError += error;		
      }else{
      	totalError = 0;	
      }

    // Calculate power using PID
    power = (error * kP) + (totalError * kI) + ((error - prevError) * kD);
    prevError = error;
    drive->getModel()->tank(power * maxV -.13f , power * maxV);
    pros::delay(100);
}

drive->stop();
}



