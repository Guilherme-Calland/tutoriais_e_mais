#include "math.h"
#include "Vec3.h"
#ifndef _RAY_H
#define _RAY_H

class Ray{
    private:
    Vec3 origin, direction;
    public:
    Ray();
    Ray(Vec3, Vec3);
    Vec3 getRayOrigin(){ return origin; }
    Vec3 getRayDirection(){ return direction; }
};

Ray::Ray(){
    origin = Vec3(0, 0, 0);
    direction = Vec3(1, 0, 0);
}

Ray::Ray(Vec3 origin, Vec3 direction){
    this->origin = origin;
    this->direction = direction;
}

#endif