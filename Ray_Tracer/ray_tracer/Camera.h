#ifndef _CAMERA_H
#define _CAMERA_H
#include "math.h"
#include "Vec3.h"
//
class Camera{
    private:
    Vec3 position, target, forward, right, up;
    float fov, aspectRatio, w, h;
    public:
    Camera(Vec3, Vec3);
    Camera(Vec3, Vec3, float, float);
    float getCameraAspectRatio(){ return aspectRatio; }
    Vec3 getCameraPosition(){ return position; }
    Vec3 getCameraForward(){ return forward; }
    Vec3 getCameraTarget(){ return target; }
    Vec3 getCameraRight(){ return right; }
    float getCameraFov(){ return fov; }
    Vec3 getCameraUp(){ return up; }
    float getCameraW(){ return w; }
    float getCameraH(){ return h; }
};

Camera::Camera(Vec3 position, Vec3 target){
    this->position = position;
    this->target = target;
    this->fov = 45;
    this->aspectRatio = 1.5;
    forward = (target - position).normalize();
    right = ((Vec3(0, 1, 0)).crossProduct(forward)).normalize();
    up = right.crossProduct(forward);

    h = tan(fov/ 57.295779);/*que na verdade é tan(fov/forward.magnitude())
    , como forward é normalizado, sua mag = 1*, obs: convertendo de radiano para grau */
    w = h*aspectRatio; 
    }
Camera::Camera(Vec3 position, Vec3 target, float fov, float aspectRatio){
    this->position = position;
    this->target = target;
    this->fov = fov;
    this->aspectRatio = aspectRatio;
    if(fov > 90){ fov = 90; }
    else if(fov < 0){ fov = 0; }
    forward = (target - position).normalize();
    right = ((Vec3(0, 1, 0)).crossProduct(forward)).normalize();
    up = right.crossProduct(forward);

    h = tan(fov /57.295779); // coverter de grau para radiano
    w = h*aspectRatio;
}

#endif