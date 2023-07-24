#include "path.hpp"
#include <vector>
#include <math.h>
#include <cmath>

IntegratedEncoder leftEncoder(leftTopPort, true);
IntegratedEncoder rightEncoder(rightTopPort, false);

IMU imu1(imuPort1, IMUAxes::z);
IMU imu2(imuPort2, IMUAxes::z);
`

// Bezier curve 
waypoint calculateBezier( const waypoint& p0, const waypoint& p1, float t){
    float x = (1 - t) * p0.getX() + t * p1.getX();
    float y = (1 - t) * p0.getY() + t * p1.getY();

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

        waypoint vector = end_point - start_point;

        int num_points_that_fit = std::ceil(vector.magnitude() / spacing);

        vector = vector.normalize() * spacing;

        for(int j = 0; j < num_points_that_fit; j++){
            newPath.push_back(start + vector * j)
        }
    }
    newPath.push_back(followPath.back());

    return newPath;

}
