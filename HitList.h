#ifndef HIT_LIST_H
#define HIT_LIST_H

#include "Hittable.h"
#include "Ray.h"
#include "Vector.h"
#include <memory>
#include <vector>

class HitList{
  public:
      std::vector<std::shared_ptr<Hittable>> hittables;
      HitList(){};
      HitList(std::vector<std::shared_ptr<Hittable>> list): hittables(list){};
      void Clear(){
          hittables.clear();
      }
      void Add(std::shared_ptr<Hittable> object){
          hittables.push_back(object);
      }
      std::shared_ptr<Hittable> SendRay(const Ray& r){
          float t_min = std::numeric_limits<double>::infinity();
          std::shared_ptr<Hittable> nearest;
          for(size_t i = 0 ; i < hittables.size(); i++ ){
              float t = hittables[i]->hit(r);
              if(t_min > 0.001 && t > 0.001 && t < t_min){
                  t_min = t;
                  nearest = hittables.at(i);
              }
          }
          return nearest;
      }


};

#endif
