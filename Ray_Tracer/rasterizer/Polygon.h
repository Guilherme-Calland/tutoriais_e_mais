#ifndef _POLYGON_H
#define _POLYGON_H
#include "Ray.h"
#include "Vec3.h"
#include "Color.h"
#include "Object.h"

class Polygon : public Object{
    private:
    Vec3 A, B, C, normal;//tem que estar em ordem horária
    Color color;            //no construtor (dependendo da posicao)
    float ka, kd, ks, alfa; // da camera

    public:
    Polygon();
    Polygon(Vec3, Vec3, Vec3, Color);
    Polygon(Vec3, Vec3, Vec3, Color, float, float, float, float);
    
    Vec3 getPolygonV1(){ return A; }
    Vec3 getPolygonV2(){ return B; }
    Vec3 getPolygonV3(){ return C; }
    Vec3 getPolygonNormal(){ return normal; }
    Color getColor(){ return color; }
    float getKa(){ return ka; }
    float getKd(){ return kd; }
    float getks(){ return ks; }
    float getAlfa(){ return alfa; }


    Vec3 getNormalAt(Vec3 point){
        return normal;
    }

    Vec3 getBaricenter(){
        return (A + B + C)/ 3;
    }

    float intersectionDistance(Ray ray){

        Vec3 d = ray.getRayDirection();
        Vec3 n = normal;
        Vec3 pr = ray.getRayOrigin();
        Vec3 pp = A;
        
        if(d.dotProduct(n) == 0){ return -1; }

        float t = (n.dotProduct(pp) - n.dotProduct(pr))
                        / (n.dotProduct(d));

        Vec3 Q = pr + d*t; 
        Vec3 CA = A - C;
        Vec3 QA = A - Q;
        Vec3 BC = C - B;
        Vec3 QC = C - Q;
        Vec3 AB = B - A;
        Vec3 QB = B - Q;

        if((CA.crossProduct(QA)).dotProduct(n) >= 0 &&
           (BC.crossProduct(QC)).dotProduct(n) >= 0 &&
           (AB.crossProduct(QB)).dotProduct(n) >= 0){
            return t - 0.0001;
        }
        else{
            return -1;
        }
    }

};

Polygon::Polygon(){
    A = Vec3(-1, 0, 0);
    B = Vec3(0, 1, 0);
    C = Vec3(1, 0, 0);
    color = Color(1, 1, 1);
    this->ka = 1;
    this->kd = 1;
    this->ks = 0;
    this->alfa = 1;
    
    Vec3 AB = B - A;
    Vec3 AC = C - A;
    normal = AC.crossProduct(AB).normalized();
}

Polygon::Polygon(Vec3 A, Vec3 B, Vec3 C, Color color){
    this->A = A;
    this->B = B;
    this->C = C;
    this->color = color;
    this->ka = 1;
    this->kd = 1;
    this->ks = 0;
    this->alfa = 1;
    
    Vec3 AB = B - A;
    Vec3 AC = C - A;
    normal = AC.crossProduct(AB).normalized();
}

Polygon::Polygon(Vec3 A, Vec3 B, Vec3 C, Color color, 
float ka, float kd, float ks, float alfa){
    this->A = A;
    this->B = B;
    this->C = C;
    this->color = color;
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->alfa = alfa;
    
    Vec3 AB = B - A;
    Vec3 AC = C - A;
    normal = AC.crossProduct(AB).normalized();
}



#endif