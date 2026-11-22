#ifndef MATE_H
#define MATE_H

#include "Material.h"
#include "Ray.h"
#include "Vector.h"
#include <algorithm>
#include <cmath>

class Mate : public Material{
    public:
        float ka;
        Vector spec;
        float ks;
        float shiness;
    Mate(float _ka, const Vector& _spec, float _ks, float _shiness, Vector _color): Material(_color){
        ka = _ka;
        spec = _spec;
        ks = _ks;
        shiness= _shiness;
        color = _color;
    };
    Vector environment() const override{
        return color * ka;
    }
    bool scatter(const Ray& r, const Vector& normal, const Vector& intersec, Ray& scattered)const override{
        return false;
    }
    Vector shading(const Vector& to_light, const Vector& normal, const Vector&v) const override{
        auto d = to_light.length_squared();
        auto uni_light = unit_vector(to_light);
        auto nl = dot(normal, uni_light);
        auto lambert = color * std::max(0.0, nl) / d;
        auto h = unit_vector(uni_light + v);
        auto blinn = spec * ks * pow(std::max(0.0, dot(h,normal)),shiness)/d;
        return lambert + blinn;
    }
};
#endif
