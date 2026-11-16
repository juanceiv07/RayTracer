#ifndef HITTABLE_H
#define HITTABLE_H

#include "Vector.h"
#include "Ray.h"


class Hittable{
    Vector center;
    Vector color;
    public:
        Hittable(Vector _center, Vector _color){
            center = _center;
            color = _color;
        }
        virtual float hit(const Ray& r) const = 0;
        virtual Vector getCenter() const = 0;
        virtual Vector getColor() const = 0;
        virtual Vector getNormal(const Vector& hit_point) const = 0;
};

#endif
