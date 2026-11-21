#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Material.h"
#include "Vector.h"
#include "Ray.h"
#include <algorithm>
#include <cmath>
#include <memory>

class Sphere : public Hittable{
    private:
        float ratio;
    public:
        Sphere(const Vector& _center, float _ratio, const Vector& _color, Mate material): Hittable(_center, _color, material){
            center = _center + Vector(0,_ratio,0);
            ratio = _ratio;
            color = _color;
        }
        Vector getCenter() const override{
            return center;
        }
        float getRatio() const {
            return ratio;
        }
        Vector getColor() const override{
            return color;
        }
        float hit(const Ray& ray) const override{
            auto a  = ray.getDirection().length_squared();
            auto b =  -2 * dot(ray.getDirection(),(center - ray.getOrigin()));
            auto c = (center - ray.getOrigin()).length_squared() - ratio * ratio;
            auto discri = b * b - (4.0 * a * c);
            if (discri < 0){
                return -10;
            }
            float r = std::sqrt(discri);
            float t2 = (-b - r)/ (2.0 * a);
            return t2;
        }
        Vector getNormal(const Vector& hit_point) const override{
            return (hit_point - center)/ratio;
        }
        Mate getMaterial() const override{
            return mater;
        }
};

#endif
