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
    std::shared_ptr<Material> mater;
    public:
        Hittable(Vector _center, std::shared_ptr<Material> _material): center(_center), mater(_material){}
        virtual float hit(const Ray& r) const = 0;
        Vector getCenter(){
            return center;
        }
        virtual Vector getNormal(const Vector& hit_point) const = 0;
        std::shared_ptr<Material> getMaterial(){
            return mater;
        }
        virtual Vector randomPoint(const Vector& p) const = 0;
        virtual bool isEmissive() const {return false;}
};

#endif
