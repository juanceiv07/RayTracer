#include "HitList.h"
#include "Metal.h"
#include "Sphere.h"
#include "Vector.h"
#include "Camera.h"
#include "Ray.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include "Hittable.h"
#include "Light.h"
#include "Wall.h"
#include <float.h>
#include <memory>
#include "Mate.h"

Vector ray_color(const Ray& r, HitList list, Light& light, int depth) {
    if (depth <= 0){
        return Vector(0,0,0);
    }
    float t;
    std::shared_ptr<Hittable> result = list.SendRay(r, t);
    if(!(result)){
        Vector unit_direction = unit_vector(r.getDirection());
        auto a = 0.5*(-unit_direction.getY() + 1.0);
        return (1.0-a) * Vector(1.0, 1.0, 1.0) + a * Vector(0.1, 0.1, 1.0);
    }
    if(result == light.getForm()){
        return light.getColor();
    }
    Vector intersec = r.getOrigin() + t * r.getDirection();
    auto normal = result->getNormal(intersec);

    Ray shadow = Ray(intersec, light.randomPoint() - intersec);

    auto material = (result->getMaterial());
    auto final = light.getColor() * light.getIntensity() * material->shading(shadow.getDirection(), normal, -r.getDirection()) + material->environment();
    Ray scattered;
    if (material->scatter(r, normal, intersec, scattered)){
        return final *  ray_color(scattered, list, light, depth -1);
    }
    float shadow_t;
    auto block = list.SendRay(shadow, shadow_t);
    if(block && block != light.getForm()){
         return 0.2 * final;
    }
    return final;
}

int main(){

    auto aspect_ratio = 16.0 / 9.0;
    int width = 1080;
    int height = std::max(int(width/aspect_ratio),1);
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    auto viewport_height = 2.0;
    auto viewport_width  = viewport_height * (double(width) / height);
    Camera Cam = Camera(Vector(0,2,10), 2, viewport_height, viewport_width, width, height);

    Light light1 = Light(Vector(2,5,-10), 1, Vector(1,1,1), 100);
    Light light2 = Light(Vector(-2,10,-15), 10 ,10 , "floor", Vector(1,1,1), 100);

    HitList list = HitList();
    Vector p1 = Vector(0,-1,0);
    int a = std::numeric_limits<int>::max();

    auto mate1 = std::make_shared<Mate>(0.1,Vector(1,1,1), 0.05, 8, Vector(0.8,0.5,0));
    auto cera = std::make_shared<Mate>(0.1, Vector(1, 1, 1), 0.6,96, Vector(0,0,1));
    auto metal1 = std::make_shared<Metal>(2,Vector(0.5,0.5,0.5));
    auto mate2 = std::make_shared<Mate>(0.1,Vector(1,1,1), 0.1, 12, Vector(0.5,1,0.5));
    auto metal2 = std::make_shared<Metal>(4,Vector(0.2,0.2,0.6));


    auto ground = std::make_shared<Wall>(a, a, p1, "floor", mate1);
    auto ground_center = ground->getCenter();
    auto sphere1 = std::make_shared<Sphere>(Vector(5, ground_center.getY(), -10), 1, cera);
    auto sphere2 = std::make_shared<Sphere>(Vector(-10, ground_center.getY(), -20), 4, metal1);
    auto sphere3 = std::make_shared<Sphere>(Vector(-3, ground_center.getY(), -8), 1, mate2);
    auto wall1 =  std::make_shared<Wall>(10,20,Vector(-2,0,-30),"front",cera);

    list.Add(ground);
    list.Add(sphere1);
    list.Add(sphere2);
    list.Add(light1.getForm());
    list.Add(sphere3);
    list.Add(wall1);

    for (int  j = 0 ; j < height ; j++){
        for (int i = 0; i < width; i++){
            auto pixel_center = Cam.pixel0() + (i * Cam.deltaU()) + (j * Cam.deltaV());
            auto ray_direction = pixel_center - Cam.CamerCenter();
            Ray r(Cam.CamerCenter(), ray_direction);
            auto pixel_color = ray_color(r, list, light1, 5);            write_color(std::cout ,pixel_color);
        }
    }
}
