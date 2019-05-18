#ifndef _SPHERE_H
#define _SPHERE_H
#include "Ray.h"
#include "Vec3.h"
#include "Color.h"
#include "Object.h"
//

class Sphere : public Object{
    private:
    Vec3 center;
    float radius;
    Color color;
    float ka, kd, ks, alfa, krflx;
    bool reflection;
    public:
    Sphere(Vec3, float, Color);
    Sphere(Vec3, float, Color, float, float, float, float, float);
    Vec3 getSphereCenter(){ return center; }
    float getSphereRadius(){ return radius; }
    Color getColor(){ return color; }
    float getKa(){ return ka; }
    float getKd(){ return kd; }
    float getKs(){ return ks; }
    float getAlfa(){ return alfa; }
    float getKrflx(){ return krflx; }
    bool getReflection(){ return reflection; }
    void setReflection(bool r){ this->reflection = r; }


    //explicacao na pasta
    float intersectionDistance(Ray ray){
        Vec3 p = ray.getRayOrigin() - center;
        Vec3 d = ray.getRayDirection();
        float r = radius;
        
        float a = pow(d.magnitude(), 2);
        float b = 2*(p.dotProduct(d));
        float c = pow(p.magnitude(), 2) - pow(r, 2);

        float delta = b*b - 4*a*c; 
        if(delta < 0){ return -1; }

        float root1 = (-b - sqrt(delta))/ (2*a) ;
        float root2 = (-b + sqrt(delta))/ (2*a)  /*- 0.00001 */  ;  
        // 0.00001 é para dar acurácia, ex: se o posicao do pixel
        // estiver no lugar errado por milésimos
        float t;
        if(root1 < 0){
            if(root2 < 0){
                return -1;
            }
            else{
                t = root2 ;
            }
        }
        else{
            t = root1 ;
        }

        return t - 0.0001;
    }

    Vec3 getNormalAt(Vec3 point){
        Vec3 n = point - center;
        return n.normalized();
    }

};

Sphere::Sphere(Vec3 center, float radius, Color color){
    this->center = center;
    this-> radius = radius;
    this->color = color;
    this->ka = 1;
    this->kd = 1;
    this->ks = 0;
    this->alfa = 1;
    this->reflection = false;
    this->krflx = 0;
}
Sphere::Sphere(Vec3 center, float radius, Color color,
float ka, float kd, float ks, float alfa, float krflx){
    this->center = center;
    this-> radius = radius;
    this->color = color;
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->alfa = alfa;
    this->reflection = false;
    this->krflx = krflx;
    if(krflx > 1){ krflx = 1; }
    if(krflx < 0){ krflx = 0; }
}

#endif