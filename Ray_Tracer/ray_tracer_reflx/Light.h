#ifndef _LIGHT_H
#define _LIGHT_H
//
class Light{
    private:
    Vec3 position;
    Color color;
    Color id;   //coeficiente difuso
    Color is;   //coeficiente especular
    public:
    Light(Vec3, Color);//simples
    Light(Vec3, Color, Color, Color);
    Vec3 getLightPosition(){ return position; }
    Color getLightColor(){ return color; }
    Color getLightId(){ return id; }
    Color getLightIs(){ return is; }
};

Light::Light(Vec3 position, Color color){
    this->position = position;
    this->color = color;
    this->id = color;
    this->is = color;
}
Light::Light(Vec3 position, Color color, Color id, Color is){
    this->position = position;
    this->color = color;
    this->id = id;
    this->is = is;
}

#endif