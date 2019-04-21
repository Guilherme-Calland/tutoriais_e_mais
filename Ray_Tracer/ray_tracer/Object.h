#ifndef _OBJECT_H
#define _OBJECT_H
#include "Ray.h"
#include "Vec3.h"
#include "Color.h"
//
class Object{
    
    public:
    /*funcoes virtuais podem ser sobreescritas
    por funções de classes herdeiras de mesmo nome*/
    virtual Color getColor(){ return Color(0, 0, 0); }
    virtual Vec3 getNormalAt(Vec3 position){ return Vec3(0, 0, 0); }
    virtual float intersectionDistance(Ray ray){ return 0; }
    
    virtual float getKa(){ return 0; }
    virtual float getKd(){ return 0; }
    virtual float getKs(){ return 0; }
    virtual float getAlfa(){ return 0; }
};


#endif