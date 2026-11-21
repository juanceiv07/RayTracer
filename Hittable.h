#ifndef HITTABLE_H
#define HITTABLE_H

#include "Mate.h"
#include "Material.h"
#include "Vector.h"
#include "Ray.h"
#include <memory>


class Hittable{
    protected:
    Vector center;
    Vector color;
    Mate mater;
    public:
        Hittable(Vector _center, Vector _color, Mate _material): center(_center), color(_color), mater(_material){}
        virtual float hit(const Ray& r) const = 0;
        virtual Vector getCenter() const = 0;
        virtual Vector getColor() const = 0;
        virtual Vector getNormal(const Vector& hit_point) const = 0;
        virtual Mate getMaterial() const = 0;
};

#endif
