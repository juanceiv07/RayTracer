#ifndef MATE_H
#define MATE_H

#include "Material.h"
#include "Vector.h"

class Mate: public Material {
    public:
        Vector color;
        float ka;
        Vector spec;
        float ks;
        float shiness;
    Mate(){};
    float shading(const Vector &light_dir, const Vector& intersec,  const Vector& _normal) const override{
        auto uni_ligth = unit_vector(light_dir - intersec);
        auto nl = dot(_normal, uni_ligth);
        return std::min(1.0, 90 * std::max(0.0, nl)/ (light_dir - intersec).length_squared());
    }
};

#endif
