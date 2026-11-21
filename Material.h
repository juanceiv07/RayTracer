#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"
#include "Vector.h"
class Material{
    public:
    virtual Vector shading(const Ray& to_light, const Vector& intersec,  const Vector& _normal,const Vector& light_color, const Ray& camray) const = 0;
};
#endif
