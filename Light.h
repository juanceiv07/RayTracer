#ifndef LIGHT_H
#define LIGHT_H

#include "Vector.h"

class Light{
    public:
        Vector pos;
    Light(const Vector& _pos):pos(_pos){};

    const Vector& getPos(){
        return pos;
    }
};

#endif
