#include "path.hpp"
#include "ports.hpp"
#include "drive.hpp"
#include <vector>
#include <math.h>
#include <cmath>

IntegratedEncoder leftEncoder(leftTopPort, true);
IntegratedEncoder rightEncoder(rightTopPort, false);

IMU imu1(imuPort1, IMUAxes::z);
IMU imu2(imuPort2, IMUAxes::z);

/* stuff left to do:
    finding distance between points 
    curvature
    velocities 
    and then we can work on stuff to make the robot acc follow the path 
*/


//quintic spline to smoothen out the curve 
waypoint quinticSpline(const waypoint& p0, const waypoint& p1, float t){
    float x0 = p0.getX();
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
    float y = 0 //needa do the polynomial for this too 

    return waypoint(x, y);

}


std::vector<waypoint> path(std::vector<waypoint> followPath, float maxVel, float maxA, float curv){
    // 1. injecting points 
    int spacing = 6;

    std::vector<waypoint> newPath; 

    for(int i = 0; i < followPath.size() - 1; i++){
        //points between the waypoint 
        waypoint start = followPath[i];
        waypoint end = followPath[i + 1];

        waypoint vector = end - start;

        int num_points_that_fit = std::ceil(abs(vector) / spacing);

        vector = vector.normalize() * spacing;

        for(int j = 0; j < num_points_that_fit; j++){
            newPath.push_back(start + vector * j)
        }
    }
    newPath.push_back(followPath.back());

    return newPath;

}
