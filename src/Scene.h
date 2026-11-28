#ifndef SCENE_H
#define SCENE_H

#include "HitList.h"
#include "Light.h"
class Scene{
    HitList list;
    std::vector<std::shared_ptr<Light>> light_list;

};
#endif
