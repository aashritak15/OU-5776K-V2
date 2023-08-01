
#include "path.hpp"
#include "ports.hpp"
#include "drive.hpp"
#include <vector>
#include <math.h>
#include <cmath>

//Linear Motion 

/*
turnPID(45, false, 2000);
pros::delay(100);
drivetrain(3);
pros::delay(100);
turnPID(90, true, 3000);
pros::delay(200);
drivetrain(0.6)
//shoot 
pros::delay(100);
turnPID(180, true, 5000);
*/


// pure pursuit -  curve
/*
IntegratedEncoder leftEncoder(leftTopPort, true);
IntegratedEncoder rightEncoder(rightTopPort, false);

IMU imu1(imuPort1, IMUAxes::z);
IMU imu2(imuPort2, IMUAxes::z);

/* stuff left to do:
    velocities ~ aashrita 

    and then we can work on stuff to make the robot acc follow the path 
*/

/*
waypoint followPath(float x, float y){
    //closest point

    //lookahead point
    float a = d.Dot( d ) ;
    float b = 2*f.Dot( d ) ;
    float c = f.Dot( f ) - r*r ;

    float discriminant = b*b-4*a*c;
    if( discriminant < 0 )
    {
    // no intersection
    }
    else
    {

    discriminant = sqrt( discriminant );

    float t1 = (-b - discriminant)/(2*a);
    float t2 = (-b + discriminant)/(2*a);
    
    if( t1 >= 0 && t1 <= 1 )
    {
    
        return true ;

    }

    if( t2 >= 0 && t2 <= 1 )
    {
        return true ;
  }
  
    return false ;
 }
}

//curvature
float curvature(float x1, float y1, float x2, float y2, float x3, float y3){
    float k1 = (0.5 * (powf(x1, 2) + powf(y1, 2) - powf(x2, 2)- powf(y2, 2)))/(x1 - x2);
    float k2 = (y1-y2)/(x1 - x2);
    float b = 0.5 * (powf(x2, 2) - 2 * x2 * k1 + powf(y2, 2) - powf(x3, 2) + 2 * x3 * k1 - powf(y3, 2))/(x3 * k2 - y3 + y2 - x2 * k2);
    float a = k1 - k2 * b;
    float r = sqrt(powf(x1-a, 2) + powf(y1-b, 2));
    float curvature = 1/r;

    return curvature; 
}

//quintic spline to smoothen out the curve 
waypoint quinticSpline(const waypoint& p0, const waypoint& p1, float t){
    float x0= p0.getX();
    float y0 = p0.getY();
    
    float x1 = p1.getX();
    float y1 = p1.getY();

    float a = -6 * x0 + 6 * x1;
    float b = 15 * x0 - 15 * x1;
    float c = -10 * x0 + 10 * x1;
    float d = 0;
    float e = 0;
    float f = x0;

    float x = a * powf(t, 5) + b * powf(t, 4) + c * powf(t, 3) + d * powf(t, 2) + e * t + f;
    float y = a * powf(t, 5) + b * powf(t, 4) + c * powf (t, 3) + d * powf(t, 2) + e * t + f; 
    float z = a * powf(t, 5) + b * powf(t, 4) + c * powf(t, 3) //needa do the polynomial for this too 

    return waypoint(x, y);

}

//finding distance between the points 

float distance(const waypoint& p1, const waypoint& p2){
    float dX = p2.getX() - p1.getX();
    float dY = p2.getY() - p1.getY();

    return std::sqrt(powf(dX1,2)) + powf(dY1,2); //distance formula
}

float distance2(const waypoint& p3, const waypoint& p4){
    float dX = p3.getX() - p3.getX()
}


std::vector<waypoint> path(std::vector<waypoint> followPath, float maxVel, float maxA, float curv){
    // 1. injecting points 
    int spacing = 6;

    std::vector<waypoint> newPath; 

    float total_distance = 0.0f;

    

    for(int i = 0; i < followPath.size() - 1; i++){
        //points between the waypoint 
        waypoint start = followPath[i];
        waypoint end = followPath[i + 1];

        waypoint vector = end - start;


        int num_points_that_fit = std::ceil(abs(vector) / spacing);

        vector = vector.normalize() * spacing;

        for(int j = 0; j < num_points_that_fit; j++){
            
            waypoint newpoint = start + vector * j;
            newPath.push_back(newpoint);

            newPath.move(spacing + 2); //double check number 



            float dx1 = newpoint.getX() - newPath[j].getX();
            float dy1 = newpoint.getY() - newPath[j].getY();

            total_distance += std::sqrt(powf(dx1,2)) + powf(dy1,2);
        }
        newPath.setDistance(total_distance);
        newPath = std::sqrt(powf(dx1, 2) + powf(dx2, 2));
    }
    newPath.push_back(followPath.back());

    return newPath;

}


//velocities 

void targetVelocities(std::vector<waypoint>& path, float maxVelocity, float k){
    path.back().setVel(0);

    }

*/


