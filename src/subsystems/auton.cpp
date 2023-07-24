#include "subsystems/drive.hpp"
#include "subsystems/auton.hpp"
#include "subsystems/odom.hpp"
#include "subsystems/path.hpp"

#include "globals.hpp"

using namespace okapi;

// path planning using 

//curve to side of goal (score pre load)
//intake in match load (prolly a curve back or we can jus go straight back)
//might be too far needa test 

void updateAuton(int side){
    if (side == 1){
        drivetrain(4); 
    }

    if (side == 2){
        drivetrain(-4);
    }
}