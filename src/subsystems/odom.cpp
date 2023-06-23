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
  float kP = 0.45;
  float kI = 0;
  float kD = 0.09;

  float power = 0;
  float totalError = 0;
  float currentTravel = 0; // [in]
  float targetTravel = currentTravel + target;    // [in]
  float prevError = 0;
 
  while (true){
    // Compute PID values from current wheel travel measurements
    currentTravel = ((leftEncoder.get() + rightEncoder.get())/2);
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


/*
void movePID{
okapi::IterativePosPIDController pid = okapi::IterativeControllerFactory::posPID(0.45, 0.0, 0.09); //kP, kI, kD

okapi::MotorGroup driveLeft = okapi::MotorGroup({left});    
okapi::MotorGroup driveRight = okapi::MotorGroup({right});

bool isMoving(){
    return abs(driveLeft.getActualVelocity()) + abs(driveRight.getActualVelocity()) > 10; 
} 

okapi::Rate rate; 



void drive(double target){

    pid.setTarget(target);

    while( abs(displacement - target) > 0.1){
    

    double dX = drivetrain->getState().x.convert(okapi::foot);
    double dY = drivetrain->getState().x.convert(okapi::foot);

    double displacement = std::sqrt(powf(dX,2)) + powf(dY,2);

     if (target < 0){
        displacement = -1 * displacement; 
     }

     double pid_value = pid.step(displacement);

    drivetrain->getModel()->tank(pid_value, pid_value); 

    rate.delay(100_Hz);

    

}
    drivetrain->getModel()->tank(0,0);
   
}

}
*/

//turn PID
void turnPID(float degree , bool CW, int ms) {
 float taredRotation = (imu1.get() + imu2.get())/2;
 int timer = 0;
 float turnkP = 0.0125;
 float turnkI = 0;
 float turnkD = 0.01;

  float prevError = 0;
  //float totalError = 0;

    // [deg]

  float integral = 0;
 
  while (timer < ms){
    // Compute PID values from current wheel travel measurements
      float currentVal = (imu1.get() + imu2.get())/2 - taredRotation;
      //float targetVal = currentVal + degree;
      float error = degree - currentVal;
       if (error < 0.1){break;}
       float derivative = error - prevError;
       prevError = error;
       integral += error;
       

    // Calculate power using PID
    float power = (error * turnkP) + (integral * turnkI) + (derivative * turnkD);
    //prevError = error;
    if (CW){
      drive->getModel()->tank(power * 0.75f , (-1.0f * power));
    } else {
      drive->getModel()->tank((-1.0f * power * 0.75f) , power);
    }
    
    timer += 10;
    pros::delay(10);
}

drive->stop();
}

