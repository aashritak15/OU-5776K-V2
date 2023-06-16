#include "main.h"
#include "subsystems/drive.hpp"
#include "subsystems/ports.hpp"
#include "subsystems/odom.hpp"

using namespace okapi;

IntegratedEncoder leftEncoder(left);
IntegratedEncoder rightEncoder(right);

IMU imu1(imuPort1, IMUAxes::z);
IMU imu2(imuPort2, IMUAxes::z);

void resetImu(bool print = true) {
  imu1.reset();
  imu2.reset();
  int time = pros::millis();
  int iter = 0;
  while (imu1.isCalibrating()) {
    if (print) {
      printf("IMU Calibrating... %d [ms]\n", iter);
    }
    iter += 100;
    if (iter >= 2500) { // IMU should not take more than 2500 ms to calibrate
      if (print) {
        printf("IMU Calibration Failed!\n");
      }
      break;
    }
    pros::delay(100);
  }
  if (print) {
    printf("IMU Calibrated in %d [ms]\n", iter - time);
  }
}

void imuInnit() {
  //setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  resetImu();
}

void IEInnit() {
  //left
  pros::c::motor_set_encoder_units(imuPort1, pros::E_MOTOR_ENCODER_DEGREES);
 
  //right
  pros::c::motor_set_encoder_units(imuPort2, pros::E_MOTOR_ENCODER_DEGREES);
  
  leftEncoder.reset();
  rightEncoder.reset();
}

void movePID(float target, float maxV) {
  leftEncoder.reset();
  rightEncoder.reset();
  float kP = 0.6;
  float kI = 0;
  float kD = 0.085;

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
    drive->getModel()->tank(power * (maxV *0.75f) , power * maxV);
    pros::delay(100);
  }
drive->stop();
}



//turn PID
void turnPID(float degree , bool CW, int ms) {
 float taredRotation = (imu1.get() + imu2.get())/2;
 int timer = 0;
 float turnkP = 0.3;
 float turnkI = 0;
 float turnkD = 0.05;

  float power = 0;
  float prevError = 0;
  float totalError = 0;
  float currentVal = 0; // [deg]
  float targetVal = currentVal + degree;    // [deg]
  
 
  while (timer < ms){
    // Compute PID values from current wheel travel measurements
      currentVal = ((imu1.get() + imu2.get())/2) - taredRotation;
      float error = targetVal - currentVal;
       if (error < 1.5){break;}
      if(error != 0){
    	totalError += error;		
      }else{
      	totalError = 0;	
      }

    // Calculate power using PID
      power = (error * turnkP) + (totalError * turnkI) + ((error - prevError) * turnkD);
    prevError = error;
      if (CW){
      drive->getModel()->tank(power * 0.75f , -1.0f * power);
    } else {
      drive->getModel()->tank(-1.0f * power * 0.75f , power);
    }
    
     timer += 10;
      pros::delay(10);
}
drive->stop();
}

