#ifndef _PLANE_H
#define _PLANE_H
#include "Ray.h"
#include "Vec3.h"
#include "Color.h"
#include "Object.h"
class Plane : public Object{
    private:
    Vec3 normal;
    float distanceFromCenter;
    Color color;
    float ka, kd, ks, alfa, krflx;
    bool reflection;

    public:
    Plane(Vec3, float, Color);//objeto simples
    Plane(Vec3, float, Color, float, float, float, float, float);

    Vec3 getPlaneNormal(){ return normal; }
    float getPlaneDistanceFromScene(){ return distanceFromCenter; }
    Color getColor(){ return color; }
    float getKa(){ return ka; }
    float getKd(){ return kd; }
    float getKs(){ return ks; }
    float getAlfa(){ return alfa;}
    float getKrflx(){ return krflx; }
    bool getReflection(){ return reflection; }
    void setReflection(bool r){ this->reflection = r; }
    
    Vec3 getNormalAt(Vec3 point){
        return normal.normalized();
    }

    float intersectionDistance(Ray ray){
        //explicacao na pasta
        Vec3 d = ray.getRayDirection();
        Vec3 n = normal;
        Vec3 pr = ray.getRayOrigin();
        Vec3 pp = normal*distanceFromCenter;

        if(d.dotProduct(n) == 0){ return -1; }

        float t = (n.dotProduct(pp) - n.dotProduct(pr))
                         / (n.dotProduct(d));
        return t - 0.0001;
        // se t for muito pequeno, exemplo um raio que parte do objeto
        // intersecta com ele mesmo, substraimos um pouquinho para que
        // isso nao ocorra
    }
};

Plane::Plane(Vec3 normal, float distanceFromCenter, Color color){
    this->normal = normal;
    this->distanceFromCenter = distanceFromCenter;
    this->color = color;
    this->ka = 1;
    this->kd = 1;
    this->ks = 0;
    this->alfa = 1;
    this->krflx = 0;
}

Plane::Plane(Vec3 normal, float distanceFromCenter, Color color, 
float ka, float kd, float ks, float alfa, float krflx){
    this->normal = normal;
    this->distanceFromCenter = distanceFromCenter;
    this->color = color;
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->alfa = alfa;
    this->krflx = krflx;
    if(krflx > 1){ krflx = 1; }
    if(krflx < 0){ krflx = 0; }
}

#endif