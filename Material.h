#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"
#include "Vector.h"
class Material{
    public:
        Vector color;
        Material(const Vector& _color): color(_color){};
        virtual Vector environment() const = 0;
        virtual Vector shading(const Vector& to_light, const Vector& normal, const Vector&v) const = 0;
        Vector getColor(){
            return color;
        }
        virtual bool scatter(const Ray& r, const Vector& normal, const Vector& intersec, Ray& scattered) const = 0;
};
#endif
