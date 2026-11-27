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
        Vector randomPoint(const Vector& p) const override{
            Vector wc = unit_vector(center - p);
            Vector wcX,wcY;
            if (std::abs(wc.getX()) > std::abs(wc.getY()))
                    wcX= Vector(-wc.getZ(), 0, wc.getX()) /
                          std::sqrt(wc.getX()* wc.getX() + wc.getZ() * wc.getZ());
            else
                wcX = Vector(0, wc.getZ(), -wc.getY()) / std::sqrt(wc.getY() * wc.getY() + wc.getZ() * wc.getZ());
            wcY = cross(wc, wcX);
            float u = random_float(0,1);
            float v = random_float(0,1);
            float sinThetaMax = ratio * ratio / (center - p).length_squared();
            float cosThetaMax = std::sqrt(std::max(0.0, 1.0 - sinThetaMax));
            float cosTheta = (1.0 - u) + u * cosThetaMax;
            float sinTheta = std::sqrt(std::max(0.0, 1.0 - cosTheta * cosTheta));
            float phi = v * 2.0 * M_PI;
            float dc = (center - p).length();
            float ds = dc * cosTheta - std::sqrt(std::max(0.0f, ratio * ratio - dc * dc * sinTheta * sinTheta));
            float cosAplha = (dc * dc + ratio * ratio - ds * ds) / (2.0 * dc * ratio);
            float sinAlpha = std::sqrt(std::max(0.0, 1.0 - cosAplha * cosAplha));
            auto vfinal = sinAlpha * std::cos(phi) * (-wcX) + sinAlpha * std::sin(phi) * (-wcY) + cosAplha * (-wc);
            auto sampled_p = ratio * vfinal;
            return center + sampled_p;
        }
};

#endif
