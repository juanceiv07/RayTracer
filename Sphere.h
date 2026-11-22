#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Material.h"
#include "Utillities.h"
#include "Vector.h"
#include "Ray.h"
#include <algorithm>
#include <cmath>
#include <memory>

class Sphere : public Hittable{
    private:
        float ratio;
    public:
        Sphere(const Vector& _center, float _ratio, std::shared_ptr<Material> material): Hittable(_center + Vector(0, _ratio,0), material){
            ratio = _ratio;
        }
        float getRatio() const {
            return ratio;
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
        Vector randomPoint() const override{
            auto random_z = 2 * random_double(0,1) - 1;
            auto random_t = random_double(0, 2 * M_PI);
            auto r = std::sqrt(1 - random_z * random_z);
            auto x = r *  cos(random_t);
            auto y = r * sin(random_t);
            return center + ratio * Vector(x, y, random_z);
        }
};

#endif
