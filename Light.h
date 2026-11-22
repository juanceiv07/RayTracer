#ifndef LIGHT_H
#define LIGHT_H

#include "Mate.h"
#include "Wall.h"
#include "Sphere.h"
#include "Vector.h"
#include "Hittable.h"
#include <memory>
#include <iostream>
#include <random>
#include <string>


class Light{
    public:
        Vector pos;
        std::shared_ptr<Hittable> form;
        Vector color;
        float intensity;
    Light(const Vector& _pos, float _intensity):pos(_pos),intensity(_intensity){color = Vector(1,1,1);};
    Light(const Vector& _pos, float radius, const Vector& _color, float _intensity):pos(_pos),color(_color), intensity(_intensity){
        form = std::make_shared<Sphere>(_pos, radius, std::make_shared<Mate>(0.1,Vector(1,1,1), 0.05, 8, _color));
        };
    Light(const Vector& _pos, float w, float l, std::string direc, Vector _color, float _intensity):pos(_pos),color(_color), intensity(_intensity){
        form = std::make_shared<Wall>(w, l, _pos, direc, std::make_shared<Mate>(0.1,Vector(1,1,1), 0.05, 8, _color));
    }
    const Vector& getColor(){
        return color;
    }
    const Vector& getPos(){
        return pos;
    }
    float getIntensity(){
        return intensity;
    }
    std::shared_ptr<Hittable> getForm(){
        return form;
    }
    Vector randomPoint(){
        return form->randomPoint();
    }
};

#endif
