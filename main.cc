#include "Sphere.h"
#include "Vector.h"
#include "Camera.h"
#include "Ray.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include "Hittable.h"

Vector ray_color(const Ray& r, Hittable* const arr[], int num) {
    float t_min = std::numeric_limits<double>::infinity();
    Hittable* nearest = nullptr;
    for(int i = 0 ; i < num; i++ ){
        float t = arr[i]->hit(r);
        if(t_min > 0.001 && t > 0 && t < t_min){
            t_min = t;
            nearest = arr[i];
        }
    }
    if (nearest){
        Vector hit_point = r.getOrigin() + t_min * r.getDirection();
        Vector normal = unit_vector(nearest->getNormal(hit_point));
        return 0.5*Vector(normal.getY()+1, normal.getY()+1, normal.getZ()+1);
        //return nearest->getColor();
    }
    Vector unit_direction = unit_vector(r.getDirection());
    auto a = 0.5*(-unit_direction.getY() + 1.0);
    return (1.0-a) * Vector(1.0, 1.0, 1.0) + a * Vector(0.1, 0.1, 1.0);
}

int main(){
    auto aspect_ratio = 16.0 / 9.0;
    int width = 1000;
    int height = std::max(int(width/aspect_ratio),1);
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    auto viewport_height = 2.0;
    auto viewport_width  = viewport_height * (double(width) / height);
    Hittable* hittables[2];
    auto sphere1 = Sphere(Vector(0,0,-10),1,Vector(1,0,0));
    auto sphere2 = Sphere(Vector(-10,0,-20),3,Vector(0,1,0));
    hittables[0] = &sphere1;
    hittables[1] = &sphere2;
    Camera Cam = Camera(Vector(0,0,0), 2.0, viewport_height, viewport_width, width, height);
    for (int  j = 0 ; j < height ; j++){
        for (int i = 0; i < width; i++){
            auto pixel_center = Cam.pixel0() + (i * Cam.deltaU()) + (j * Cam.deltaV());
            auto ray_direction = pixel_center - Cam.CamerCenter();
            Ray r(Cam.CamerCenter(), ray_direction);
            auto pixel_color = ray_color(r, hittables, 2);
            //r.printing(std::clog);
            write_color(std::cout ,pixel_color);
        }
    }
}
