#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera{
    private:
        Vector pos;
        float image_width;
        float image_height;
        float focal_len;
        float vw_h;
        float vw_w;
        Vector viewport_u;
        Vector viewport_v;
        Vector px_delta_u;
        Vector px_delta_v;
        Vector px00;
        Vector cameraTarget;
    public:
        Camera(const Vector& _pos, float f_len, float vh, float vw, float imw, float imh, const Vector& target){
            pos = _pos;
            focal_len = f_len;
            vw_h = vh;
            vw_w = vw;
            image_height = imh;
            image_width = imw;
            cameraTarget = target;
            update();

        }
        void update(){
            auto cameraDirection = unit_vector(pos - cameraTarget);

            auto cameraRight = unit_vector(cross(Vector(0, 1, 0), cameraDirection));

            auto cameraUp = cross(cameraDirection, cameraRight);

            viewport_u = vw_w * cameraRight;
            viewport_v = vw_h * (-cameraUp);

            px_delta_u = viewport_u / image_width;
            px_delta_v = viewport_v / image_height;
            auto viewport_upper_left = pos -  focal_len * cameraDirection - viewport_u/2 - viewport_v/2;
            px00 = viewport_upper_left + 0.5 * (px_delta_u + px_delta_v);

        }
        Vector getTarget(){
            return cameraTarget;
        }
        Vector CamerCenter() const{
            return pos;
        }
        Vector pixel0() const{
            return px00;
        }
        Vector deltaU() const{
            return px_delta_u;
        }
        Vector deltaV() const{
            return px_delta_v;
        }
        void setX(float x){
            pos[0] = x;
        }
        void setY(float y){
            pos[1] = y;
        }
        void setZ(float z){
            pos[2] = z;
        }
};

#endif
