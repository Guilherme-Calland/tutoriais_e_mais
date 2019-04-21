#include "math.h"
#ifndef _VEC3_H
#define _VEC3_H
//
class Vec3{

    private:
    float x, y, z;

    public:
    Vec3();
    Vec3(float, float, float);

    float getVec3X(){ return x; }
    float getVec3Y(){ return y; }
    float getVec3Z(){ return z; }

    float dotProduct(Vec3 v){
        return x*v.getVec3X() + y*v.getVec3Y() + z*v.getVec3Z(); 
    }

    Vec3 crossProduct(Vec3 v){
        return Vec3(y*v.getVec3Z() - z*v.getVec3Y(),
					z*v.getVec3X() - x*v.getVec3Z(),
					x*v.getVec3Y() - y*v.getVec3X());
    }

    float magnitude(){
		return sqrt((x*x) + (y*y) + (z*z));
	}

    Vec3 normalize(){
        float mag = sqrt((x*x) + (y*y) + (z*z));
        x = x/mag;
        y = y/mag;
        z = z/mag;

        return Vec3(x, y, z);
    }

	Vec3 normalized(){
		float mag = sqrt((x*x) + (y*y) + (z*z));
		return Vec3(x/mag, y/mag, z/mag);
	}


    void operator =(Vec3 v){
        this->x = v.getVec3X();
        this->y = v.getVec3Y();
        this->z = v.getVec3Z();
    };
    void operator +=(Vec3 v){
         this->x += v.getVec3X();
         this->y += v.getVec3Y();
         this->z += v.getVec3Z();
    };
    void operator -=(Vec3 v){
        this->x -= v.getVec3X();
        this->y -= v.getVec3Y();
        this->z -= v.getVec3Z();
    };
    void operator *=(float k){
        this->x *= this->x*k;
        this->y *= this->y*k;
        this->z *= this->z*k;
    };
    void operator /=(float k){
        this->x /= this->x/k;
        this->y /= this->y/k;
        this->z /= this->z/k;
    };
    Vec3 operator +(Vec3 v){
        return Vec3(this->x + v.getVec3X(),
                    this->y + v.getVec3Y(),
                    this->z + v.getVec3Z());
    }
    Vec3 operator -(Vec3 v){
        return Vec3(this->x - v.getVec3X(),
                    this->y - v.getVec3Y(),
                    this->z - v.getVec3Z());
    }
    Vec3 operator *(float k){
        return Vec3(this->x * k,
                    this->y * k,
                    this->z * k);
    }
    Vec3 operator /(float k){
        return Vec3(this->x / k,
                    this->y / k,
                    this->z / k);
    }
    Vec3 operator -(){
        return Vec3(-x, -y, -z);
    };

};

Vec3::Vec3(){
    x, y, z = 0;
}

Vec3::Vec3(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
#endif