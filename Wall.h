#ifndef WALL_H
#define WALL_H

#include "Hittable.h"
#include "Mate.h"
#include "Material.h"
#include "Ray.h"
#include "Vector.h"
#include "Utillities.h"
#include <cstdlib>
#include <memory>
#include <string>

class Wall : public Hittable{
    public:
    float width; //ray1
    float lenght; //ray2
    Ray ray1;
    Ray ray2;
    std::string type;
    Vector center;
    //Center --> vertex;
    Wall(float w, float l, Vector p, std::string pos, std::shared_ptr<Material> material): Hittable(p, material){
        width = w;
        lenght = l;
        center = p;
        if (pos == "floor"){
            ray1 = Ray(p,Vector(1,0,0));
            ray2 = Ray(p,Vector(0,0,-1));
        }
        if(pos == "side"){
            ray1 = Ray(p,Vector(0,1,0));
            ray2 = Ray(p,Vector(0,0,1));
        }
        if(pos == "front"){
            ray1 = Ray(p,Vector(1,0,0));
            ray2 = Ray(p,Vector(0,1,0));
        }
    }
    float hit(const Ray& r) const override{
        Vector plane_normal = cross(ray1.getDirection(), ray2.getDirection());
        float den = (dot(r.getDirection(), plane_normal));
        if (den == 0){
            return -1;
        }
        float d = dot((center - r.getOrigin()), plane_normal)/(den);
        Vector intersec = r.getOrigin() + d * r.getDirection();
        float dis1 = std::abs(dot((intersec - ray1.getOrigin()),ray1.getDirection()) / (ray1.getDirection().length()));
        float dis2 = std::abs(dot((intersec - ray2.getOrigin()),ray2.getDirection()) / (ray2.getDirection().length()));
        if(dis1 > lenght/2 || dis2 > width/2){
            return -1;
        }
        return d;
    }
    Vector getNormal(const Vector& hit_point) const override{
        return cross(ray1.getDirection(), ray2.getDirection());
    }
    Vector randomPoint() const override{
        auto rx = random_double(center.getX(), center.getX() + width);
        auto ry = random_double(center.getY(), center.getY() + width);
        auto rz = random_double(center.getZ(), center.getZ() + width);
        auto xf = random_double(rx, lenght);
        auto yf = random_double(ry, lenght);
        auto zf = random_double(rz, lenght);
        return Vector(xf, yf, zf);
    }
//color = ((dis1 + dis2) % 2 == 0) ? Vector(0.9, 0.9, 0.9) : Vector(0.2, 0.2, 0.2);
};


#endif
