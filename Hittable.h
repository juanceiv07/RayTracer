#ifndef HITTABLE_H
#define HITTABLE_H

#include "Material.h"
#include "Vector.h"
#include "Ray.h"
#include <memory>


class Hittable{
    protected:
    Vector center;
    Vector color;
    std::shared_ptr<Material> material;
    public:
        Hittable(Vector _center, Vector _color, std::shared_ptr<Material> _material){
            center = _center;
            color = _color;
            material = _material;
        }
        virtual float hit(const Ray& r) const = 0;
        virtual Vector getCenter() const = 0;
        virtual Vector getColor() const = 0;
        virtual Vector getNormal(const Vector& hit_point) const = 0;
        virtual std::shared_ptr<Material> getMaterial() const = 0;
};

#endif
