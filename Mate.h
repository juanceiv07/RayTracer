#ifndef MATE_H
#define MATE_H

#include "Material.h"
#include "Ray.h"
#include "Vector.h"
#include <algorithm>
#include <cmath>

class Mate{
    public:
        float ka;
        Vector spec;
        float ks;
        float shiness;
    Mate(float _ka, const Vector& _spec, float _ks, float _shiness){
        ka = _ka;
        spec = _spec;
        ks = _ks;
        shiness= _shiness;
    };
    Vector shading(const Ray& camray, const Ray& to_light, const Vector& color, const Vector& intersec, const Vector& _normal, const Vector& light_color, float intensity) const{
        auto env = color * ka;
        auto d =  to_light.getDirection().length();
        auto uni_ligth = to_light.getDirection() / d;
        auto nl = dot(_normal, uni_ligth);
        auto lambert =  color * light_color * intensity * std::max(0.0, nl)/ (d*d);
        auto v = unit_vector(-camray.getDirection());
        auto h = unit_vector(uni_ligth + v);
        auto blinn = (spec * light_color * intensity* ks * pow(std::max(0.0, dot(h,_normal)),shiness))/(d*d);
        return  env + lambert + blinn;
    }
};
#endif
