#include "main.h"
#include "subsystems/drive.hpp"
#include "subsystems/ports.hpp"
#include "subsystems/odom.hpp"
#include "globals.hpp"


using namespace okapi;




IntegratedEncoder leftEncoder(leftTopPort, true);
IntegratedEncoder rightEncoder(rightTopPort, false);

IMU imu1(imuPort1, IMUAxes::z);
IMU imu2(imuPort2, IMUAxes::z);


void resetEncoders(){
  leftEncoder.reset();
  rightEncoder.reset();
}


void resetImu(bool print = true) {
  imu1.reset();
  imu2.reset();
  int time = pros::millis();
  int iter = 0;
  while (imu1.isCalibrating()) {
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

void IEInnit() {
  //left
  pros::c::motor_set_encoder_units(leftTopPort, pros::E_MOTOR_ENCODER_DEGREES);
 
  //right
  pros::c::motor_set_encoder_units(rightTopPort, pros::E_MOTOR_ENCODER_DEGREES);
  
  leftEncoder.reset();
  rightEncoder.reset();
}



/*
void movePID(float target, float maxV) {
  leftEncoder.reset();
  rightEncoder.reset();
  float kP = 0.45;
  float kI = 0;
  float kD = 0.009;

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
    drive->getModel()->tank(power * maxV  , power * maxV);
    pros::delay(100);
  }
drive->stop();
}
*/

/*
void driveForward(double distance) {
    okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0.8, 0., 0.007); //create a new drive object with specified pid

    const double target = distance; //idk why not just use distance

    drivePID.setTarget(target); //tels PROS: to move the drive using pid to distance

    double orgPosX = drive->getState().x.convert(okapi::foot); //store the orginal position
    double orgPosY = drive->getState().y.convert(okapi::foot);

    double distTravelled = 0;

    while (abs(target-distTravelled) >= 0.2 || abs(left.getActualVelocity())>10) {//pid shit i think idk
    // condition :abs(target-distTravelled) >= 0.2
        double dx = drive->getState().x.convert(okapi::foot) - orgPosX;
        double dy = drive->getState().y.convert(okapi::foot) - orgPosY;

        distTravelled = sqrt(dx*dx + dy*dy);
        
        double vel = drivePID.step(distTravelled);

        drive -> getModel() -> tank(vel, vel);

        pros::delay(10);
         pros::lcd::set_text(1, std::to_string(drive->getState().x.convert(okapi::foot))); //displays the X coordinate on the LCD of the screen per tick
         pros::lcd::set_text(2, std::to_string(drive->getState().y.convert(okapi::foot))); //displays the X coordinate on the LCD of the screen per tick

    }
}

*/


okapi::IterativePosPIDController pid = okapi::IterativeControllerFactory::posPID(0.45, 0.0, 0.009); //kP, kI, kD              

okapi::MotorGroup driveLeft = okapi::MotorGroup({leftFront, leftBack, leftTop});    
okapi::MotorGroup driveRight = okapi::MotorGroup({rightFront, rightBack, rightTop});

bool isMoving(){
    return abs(driveLeft.getActualVelocity()) + abs(driveRight.getActualVelocity()) > 10; 
} 


void drivetrain(double target){

    pid.setTarget(target);

    double dX = drive->getState().x.convert(okapi::foot);
    double dY = drive->getState().x.convert(okapi::foot);

    double displacement = 0.0;

    //runs as long as displacement 
    while( abs(target - displacement) > 0.1 || abs(driveLeft.getActualVelocity()) + abs(driveRight.getActualVelocity()) > 10){
    
    //calculates change in position
    double dX1 = drive->getState().x.convert(okapi::foot) - dX;
    double dY1 = drive->getState().x.convert(okapi::foot) - dY;

   //pythagorean theorem to calculate displacement 
    displacement = std::sqrt(powf((dX1 * 3) / 5 ,2)) + powf((dY1 * 3) / 5 , 2);

  // negative target -> negative displacement 
     if (target < 0){
        displacement = -1 * displacement; 
     }

     double pid_value = pid.step(displacement);

    drive->getModel()->tank(pid_value, pid_value); 

    pros::delay(10);

}
    drive->getModel()->tank(0,0);
}





//turn PID
void turnPID(float degree , bool CW, int ms) {
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
    if (CW){
      drive->getModel()->tank(power * 0.75f , (-1.0f * power)); //goes clockwise 
    } else {
      drive->getModel()->tank((-1.0f * power * 0.75f) , power); //goes counterclockwise 
    }
    
    timer += 10;
    pros::delay(10);
}

drive->stop();
}


/*
//two seperate functions? 

void turnClockwise(float degree, int ms) {
    float taredRotation = (imu1.get() + imu2.get()) / 2;
    int timer = 0;
    float turnkP = 0.0125;
    float turnkI = 0;
    float turnkD = 0.01;

    float prevError = 0;
    float integral = 0;

    while (timer < ms) {
        float currentVal = (imu1.get() + imu2.get()) / 2 - taredRotation;
        float error = degree - currentVal;
        
        if (error < 0.1) {
            break;
        }

        float derivative = error - prevError;
        prevError = error;
        integral += error;

        float power = (error * turnkP) + (integral * turnkI) + (derivative * turnkD);

        drive->getModel()->tank(power * 0.75f, (-1.0f * power));

        timer += 10;
        pros::delay(10);
    }

    drive->stop();
}

void turnCounterclockwise(float degree, int ms) {
    degree -= 180.0f;  // Subtract 180 degrees from the target angle

    float taredRotation = (imu1.get() + imu2.get()) / 2;
    int timer = 0;
    float turnkP = 0.0125;
    float turnkI = 0;
    float turnkD = 0.01;

    float prevError = 0;
    float integral = 0;

    while (timer < ms) {
        float currentVal = (imu1.get() + imu2.get()) / 2 - taredRotation;
        float error = degree - currentVal;

        if (error < 0.1) {
            break;
        }

        float derivative = error - prevError;
        prevError = error;
        integral += error;

        float power = (error * turnkP) + (integral * turnkI) + (derivative * turnkD);

        power = std::min(std::max(power, -1.0f), 1.0f); // Overshooting control

        drive->getModel()->tank((-1.0f * power * 0.75f), power);

        timer += 10;
        pros::delay(10);
    }

    drive->stop();
}

*/




