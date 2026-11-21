#ifndef LIGHT_H
#define LIGHT_H

#include "Mate.h"
#include "Sphere.h"
#include "Vector.h"
#include "Hittable.h"
#include <memory>
#include <iostream>
#include <string>


class Light{
    public:
        Vector pos;
        std::shared_ptr<Hittable> form;
    Light(const Vector& _pos):pos(_pos){};
    Light(const Vector& _pos, float radius):pos(_pos){
        form = std::make_shared<Sphere>(_pos, radius, Vector(1,1,1), std::make_shared<Mate>());
    };

    const Vector& getPos(){
        return pos;
    }
    std::shared_ptr<Hittable> getForm(){
        return form;
    }
};

#endif
