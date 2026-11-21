#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vector.h"
class Material{
    public:
    virtual float shading(const Vector &light_dir, const Vector& intersec,  const Vector& _normal) const = 0;
};
#endif
