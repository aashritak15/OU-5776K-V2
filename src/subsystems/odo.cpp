#include "main.h"
#include "subsystems/drive.hpp"
#include "subsystems/ports.hpp"
#include "subsystems/odo.hpp"
#include "globals.hpp"




using namespace okapi;

/*
  ______________________________________________________________________________________________

  lem drivetrain + pids 

  https://lemlib.github.io/LemLib/md_docs_tutorials_3_tuning_and_moving.html

  ______________________________________________________________________________________________

*/


/*
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

/*

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


/*

bool isMoving(){
  return abs(right.getActualVelocity()) + abs(left.getActualVelocity()) > 10; 
}

void drivetrain(double target, double speed){
  leftTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftBack.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightBack.setBrakeMode(AbstractMotor::brakeMode::brake);


    okapi::IterativePosPIDController pid = okapi::IterativeControllerFactory::posPID(0.9, 0.6, 0.1); //kP, kI, kD              

    pid.setTarget(target);

    double dX = drive->getState().x.convert(okapi::foot);
    double dY = drive->getState().y.convert(okapi::foot);

    double displacement = 0.0;

    //runs as long as displacement 
    while( abs(target - displacement) > 1 || isMoving()){
    
      //calculates change in position
      double dX1 = drive->getState().x.convert(okapi::foot) - dX;
      double dY1 = drive->getState().y.convert(okapi::foot) - dY;

    //pythagorean theorem to calculate displacement 
      displacement = std::sqrt(powf(dX1, 2) + powf(dY1 , 2));

    // negative target -> negative displacement 
      if (target < 0){
          displacement = -1 * displacement; 
      }

      double pid_value = pid.step((displacement * 3) / 6);

      drive->getModel()->tank(pid_value * speed  , pid_value * speed); 

      

      pros::delay(20);
      

}

  pid.reset(); 
  drive->getModel()->tank(0, 0);
}

*/

/*
void drive_dis(double target, double scale) {                                          //init 0.85
    if (abs(target) <= 0.01)
        return;
// .88
    okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0.848, 0.1, 0.0000);
    //okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0.75, 0.01, 0.01); 


    drivePID.setTarget(target);

    double orgPosX = drive->getState().x.convert(okapi::foot);
    double orgPosY = drive->getState().y.convert(okapi::foot);


    double displacement = 0;
                                                        //at 0.8
    while (abs(target-displacement) >=  1  || abs(left.getActualVelocity()) >  8 ) { 
    //while (true) {                  //tuning
        double state_x = drive->getState().x.convert(okapi::foot);
        double state_y = drive->getState().y.convert(okapi::foot);

        double dx = state_x - orgPosX;
        double dy = state_y - orgPosY;

        //printf("IMU: %lf\n", inertial.controllerGet());

        displacement = sqrt(dx * dx + dy * dy);

        if (target < 0)
            displacement = - displacement;
        

        double vel = drivePID.step(( displacement * 3) / 6);

        //printf("distTravelled: %lf, cur_x: %lf, cur_y:%lf\n",
        //   distTravelled, drive->getState().y.convert(okapi::foot), drive->getState().x.convert(okapi::foot));

        drive->getModel()->tank(vel * scale * 0.9  , vel * scale);
        pros::delay(16);   //A1
    }

    drivePID.reset(); 
  
    drive->getModel()->tank(0, 0); 

   
    
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
  float turnkP = 0.01;
  float turnkI = 0;
  float turnkD = 0.027;

  float prevError = 0;
  //float totalError = 0;

    // [deg]

  float integral = 0;
 
  while (timer < ms){
    // Compute PID values from current wheel travel measurements
      float currentVal = (imu1.get() + imu2.get()) / 2 - taredRotation;
      float error = degree - currentVal;

      //float targetVal = currentVal + degree;

      //float error = degree - abs(currentVal);
       
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

    printf("currentVal: %f, error: %f, power: %f\n", currentVal, error, integral, derivative, power);

}

drive->getModel()->tank(0,0);
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
  float turnkP = 0.01;
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

drive->getModel()->tank(0,0);
}




void turnRIGHTONLY(float degree, int ms) {
  resetImu();
  leftTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftBack.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightBack.setBrakeMode(AbstractMotor::brakeMode::brake);
 float taredRotation = (imu1.get() + imu2.get()) / 2;
 int timer = 0;
 float turnkP = 0.01;
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
      drive->getModel()->tank(0, power); //goes counterclockwise 
    
    timer += 10;
    pros::delay(10);
}

drive->stop();
}




void turnLEFTONLY(float degree, int ms) {
  resetImu();
  leftTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  leftBack.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightTop.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightFront.setBrakeMode(AbstractMotor::brakeMode::brake);
  rightBack.setBrakeMode(AbstractMotor::brakeMode::brake);
 float taredRotation = (imu1.get() + imu2.get()) / 2;
 int timer = 0;
 float turnkP = 0.01;
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
       if (abs(error) < 0.1){
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


void turnONLYLF(float degree, int ms){
  resetImu();

  float taredRotation = (imu1.get() + imu2.get()) / 2;

  int timer = 0;
  float turnkP = 0.01;
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
       if (abs(error) < 0.1){
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

*/