#include "math.h"
#include "Vec3.h"
#ifndef _COLOR_H
 #define _COLOR_H
//
class Color{
    private:
    float red, green, blue;
    public:
    Color();
    Color(float, float, float);
    float getColorRed(){ return red; }
    float getColorGreen(){ return green; }
    float getColorBlue(){ return blue; }
    void setColorRed(float red){ this->red = red; }
    void setColorGreen(float green){ this->green = green; }
    void setColorBlue(float blue){ this->blue = blue; }

    Color clip(){
        if(red > 1) { red = 1; }
		if(green > 1) { green = 1; }
		if(blue > 1) { blue = 1; }
		if(red < 0) { red = 0; }
		if(green < 0) { green = 0; }
		if(blue < 0) { blue = 0; }
        return Color(
            red, green, blue);
    }

   

    void operator = (Color c){
        red = c.getColorRed();
        green = c.getColorGreen();
        blue = c.getColorBlue(); 
    }
    Color operator - (){
        return Color(-red, -green, -blue);
    }
    void operator += (Color c){
        red += c.getColorRed();
        green += c.getColorGreen();
        blue += c.getColorBlue();
    }
    void operator -= (Color c){
        red -= c.getColorRed();
        green -= c.getColorGreen();
        blue -= c.getColorBlue();
    }
    void operator *= (float k){
        red *= red*k;
        green *= green*k;
        blue *= blue*k;
    }
    void operator /= (float k){
        red /= red/k;
        green /= green/k;
        blue /= blue*k;
    }
    Color operator + (Color c){
        return Color(red + c.getColorRed(),
                     green + c.getColorGreen(),
                     blue + c.getColorBlue());
    }
    Color operator - (Color c){
        return Color(red - c.getColorRed(),
                     green - c.getColorGreen(),
                     blue - c.getColorBlue());
    }
    Color operator * (float k){
        return Color(red * k,
                     green * k,
                     blue * k);
    }
    Color operator / (float k){
        return Color(red / k,
                     green / k,
                     blue / k);
    }
    Color operator * (Color c){
        return Color(red*c.getColorRed(), 
                     green*c.getColorGreen(),
                     blue*c.getColorBlue());
    }
};

Color::Color(){
    red, green, blue = 0;
}

Color::Color(float red, float green, float blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

#endif