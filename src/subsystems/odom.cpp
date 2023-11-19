#include "main.h"
#include "subsystems/drive.hpp"
#include "subsystems/ports.hpp"
#include "subsystems/odom.hpp"
#include "globals.hpp"


using namespace okapi;




// IntegratedEncoder leftEncoder(leftTopPort, true);
// IntegratedEncoder rightEncoder(rightTopPort, false);

IMU imu1(imuPort1, IMUAxes::z);
IMU imu2(imuPort2, IMUAxes::z);

IMU imuA(imuPort1, IMUAxes::y);
IMU imuB(imuPort2, IMUAxes::y);




/*
void checkBalance(){


  while(true){

    left.moveVoltage(12000);
    right.moveVoltage(12000);

    if(((imuA.get() + imuB.get()) / 2) > 0.1){
      break;
    }

  }

  drive->stop(); 

  pros::delay(10);

}

*/

void resetImu(bool print = true) {
  imu1.reset();
  imu2.reset();
  int time = pros::millis();
  int iter = 0;
  while (imu1.isCalibrating() && imu2.isCalibrating()) {
    if (print) {
      printf("IMU Calibrating... %d [ms]\n", iter);
    }
    iter += 200;
    if (iter >= 2500) { // IMU should not take more than 2500 ms to calibrate
      if (print) {
        printf("IMU Calibration Failed!\n");
      }
      break;
    }
    pros::delay(10);
  }
  if (print) {
    printf("IMU Calibrated in %d [ms]\n", iter - time);
  }
}

void imuInnit() {
  resetImu();
}

// void IEInnit() {
//   //left
//   pros::c::motor_set_encoder_units(leftTopPort, pros::E_MOTOR_ENCODER_DEGREES);
 
//   //right
//   pros::c::motor_set_encoder_units(rightTopPort, pros::E_MOTOR_ENCODER_DEGREES);
  
//   leftEncoder.reset();
//   rightEncoder.reset();

// }


//motor groups
okapi::MotorGroup driveLeft = okapi::MotorGroup({leftFront, leftBack, leftTop});    
okapi::MotorGroup driveRight = okapi::MotorGroup({rightFront, rightBack, rightTop});





void drivetrain(double target, int ms, double speed){
  leftTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftBack.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightBack.setBrakeMode(AbstractMotor::brakeMode::brake);


    okapi::IterativePosPIDController pid = okapi::IterativeControllerFactory::posPID(1.15, 0, 0.099); //kP, kI, kD              

    pid.setTarget(target);

    double dX = drive->getState().x.convert(okapi::foot);
    double dY = drive->getState().y.convert(okapi::foot);

    double displacement = 0.0;

    int timer = 0;

    //runs as long as displacement 
    while( abs(target - displacement) > 0.1 /*|| abs(driveLeft.getActualVelocity()) + abs(driveRight.getActualVelocity()) > 10 */ && timer < ms){
    
      //calculates change in position
      double dX1 = drive->getState().x.convert(okapi::foot) - dX;
      double dY1 = drive->getState().y.convert(okapi::foot) - dY;

    //pythagorean theorem to calculate displacement 
      displacement = std::sqrt(powf(dX1, 2) + powf(dY1 , 2));

    // negative target -> negative displacement 
      if (target < 0){
          displacement = -1 * displacement; 
      }

      double pid_value = pid.step((displacement * 3) / 5 );

      drive->getModel()->tank(pid_value * speed  , pid_value * speed); 

      pros::delay(10);
      timer += 10;

}
    drive->getModel()->tank(0,0);
}


//turn PID
void turnClock(float degree, int ms) {
  resetImu();
  leftTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftBack.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightBack.setBrakeMode(AbstractMotor::brakeMode::brake);
 float taredRotation = (imu1.get() + imu2.get()) / 2;
 int timer = 0;
 float turnkP = 0.0095;
 float turnkI = 0;
 float turnkD = 0.027;

  float prevError = 0;
  //float totalError = 0;

    // [deg]

  float integral = 0;
 
  while (timer < ms){
    // Compute PID values from current wheel travel measurements
      float currentVal = (imu1.get() + imu2.get())/2 - taredRotation;

      //float targetVal = currentVal + degree;

      float error = degree - abs(currentVal);
       if (error < 0.1){
        break;
        }

       float derivative = error - prevError;
       prevError = error;
       integral += error;


       

    // Calculate power using PID
    float power = (error * turnkP) + (integral * turnkI) + (derivative * turnkD);
    //prevError = error;
    
    drive->getModel()->tank((power * 0.9f * -1.0f) , power); 
     //goes clockwise 
    
    timer += 10;
    pros::delay(10);
}

drive->stop();
}


void turnCounter(float degree, int ms) {
  resetImu();
  leftTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftBack.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightBack.setBrakeMode(AbstractMotor::brakeMode::brake);
  
 float taredRotation = (imu1.get() + imu2.get()) / 2;
 int timer = 0;
  float turnkP = 0.0095;
 float turnkI = 0;
 float turnkD = 0.027;

  float prevError = 0;
  float integral = 0;
 
  while (timer < ms){
    // Compute PID values from current wheel travel measurements
      float currentVal = (imu1.get() + imu2.get())/2 - taredRotation;
      float error = degree - abs(currentVal);
       if (error < 0.1){
        break;
        }

       float derivative = error - prevError;
       prevError = error;
       integral += error;
       
    float power = (error * turnkP) + (integral * turnkI) + (derivative * turnkD);
    //prevError = error;

      
      drive->getModel()->tank(power * 0.9f , (-1.0f * power));
 
    
    
    timer += 10;
    pros::delay(10);
}

drive->stop();
}

void turnRightTime(int ms, int Rvelocity, int Lvelocity){
  right.moveVelocity(Rvelocity);
  left.moveVelocity(Lvelocity);

  pros::delay(ms);

  right.moveVelocity(0);
  left.moveVelocity(0);

}

void turnLeftTime(int ms, int Rvelocity, int Lvelocity){
  left.moveVelocity(Lvelocity);
  right.moveVelocity(Rvelocity);

  pros::delay(ms);

  right.moveVelocity(0);
  left.moveVelocity(0);
  
}



void turnRIGHTONLY(float degree, int ms) {
  leftTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftBack.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightBack.setBrakeMode(AbstractMotor::brakeMode::brake);
 float taredRotation = (imu1.get() + imu2.get()) / 2;
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

      float error = degree - abs(currentVal);
       if (error < 0.1){
        break;
        }

       float derivative = error - prevError;
       prevError = error;
       integral += error;


       

    // Calculate power using PID
    float power = (error * turnkP) + (integral * turnkI) + (derivative * turnkD);
    //prevError = error;
      drive->getModel()->tank(power, 0); //goes counterclockwise 
    
    timer += 10;
    pros::delay(10);
}

drive->stop();
}




void turnLEFTONLY(float degree, int ms) {
  leftTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftBack.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightBack.setBrakeMode(AbstractMotor::brakeMode::brake);
 float taredRotation = (imu1.get() + imu2.get()) / 2;
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

      float error = degree - abs(currentVal);
       if (error < 0.1){
        break;
        }

       float derivative = error - prevError;
       prevError = error;
       integral += error;


       

    // Calculate power using PID
    float power = (error * turnkP) + (integral * turnkI) + (derivative * turnkD);
    //prevError = error;
      drive->getModel()->tank( power, 0); //goes clockwise 
    
    timer += 10;
    pros::delay(10);
}

drive->stop();
}
