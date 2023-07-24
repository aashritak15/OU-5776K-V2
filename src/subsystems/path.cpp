#include "path.hpp"
#include <vector>
#include <math.h>
#include <cmath>


class waypoint {
private:
    float x;
    float y;
    float theta;
    float dist;
    float vel;
    float curv;

public:
    waypoint(float x1, float y1){
        this->x = x1;
        this->y = y1;
        this->theta = 0;
        this->dist = 0;
        this->vel = 0;
        this->curv = 0;
    }

    waypoint(float x1, float y1, float angle){
        this->x = x1;
        this->y = y1;
        this->theta = angle;
        this->dist = 0;
        this->vel = 0;
        this->curv = 0;
    }

    float getX() const {
        return this->x
    }

    float getY() const {
        return this->y
    }

    float getAngle() const{
        return this->theta;
    }

    float getDist() const {
        return this->dist;
    }

    float getVel() const {
        return this->vel;
    }

    float getCurv() const {
        return this->curv;
    }

    void setX(float newX) {
        this->x = newX;
    }

    void setY(float newY) {
        this->y = newY;
    }

    void setTheta(float newAngle) {
        this->theta = newAngle;
    }

    void setDist(float newDist) {
        this->dist = newDist;
    }

    void setVel(float newVel) {
        this->vel = newVel;
    }

    void setCurv(float newCurv) {
        this->curv = newCurv;
    }


};



