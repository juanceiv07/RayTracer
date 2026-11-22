#ifndef METAL_H
#define METAL_H

#include "Material.h"
#include "Ray.h"
#include "Vector.h"

class Metal: public Material{
    public:
    float fuzz;
    float ks = 0.4f;
    float shiness = 64;
    float ka = 0.001;
    Metal(float _fuzz,  const Vector& _color): Material(_color), fuzz(_fuzz){}
    Vector environment() const override{
        return color * ka;
    }
    bool scatter(const Ray& r, const Vector& normal, const Vector& intersec, Ray& scattered) const override{
        auto reflected = reflect(r.getDirection(), normal);
        scattered = Ray(intersec, reflected);
        return true;
    }
    Vector shading(const Vector& to_light, const Vector& normal, const Vector&v) const override{
        auto d = to_light.length_squared();
        auto uni_light = unit_vector(to_light);
        auto nl = dot(normal, uni_light);
        auto lambert = color * std::max(0.0, nl) / d;
        auto h = unit_vector(uni_light + v);
        auto blinn = color * ks * pow(std::max(0.0, dot(h,normal)),shiness)/d;
        return lambert + blinn;
    }

};

#endif
