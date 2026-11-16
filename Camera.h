#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"

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

    public:
        Camera(const Vector& _pos, float f_len, float vh, float vw, float imw, float imh){
            pos = _pos;
            focal_len = f_len;
            vw_h = vh;
            vw_w = vw;
            image_height = imh;
            image_width = imw;
            viewport_u = Vector(vw_w, 0, 0);
            viewport_v = Vector(0, -vw_h, 0);
            px_delta_u = viewport_u / image_width;
            px_delta_v = viewport_v / image_height;
            auto viewport_upper_left = pos - Vector(0, 0, focal_len) - viewport_u/2 - viewport_v/2;
            px00 = viewport_upper_left + 0.5 * (px_delta_u + px_delta_v);
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
};
#endif
