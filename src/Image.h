#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <vector>

class Image{
    public:
    int width;
    int height;
    std::vector<uint8_t> px_;
    Image(int _width, int _height): width(_width), height(_height), px_(size_t(width) * height * 4, 255){}
    int getWidth(){return width;}
    int getHeight(){return height;}
    void set(uint8_t r, uint8_t g, uint8_t b, int x, int y){
        size_t i = x * y;
        px_[i] = r;
        px_[i+1] = g;
        px_[i+2] = b;

    }
    const uint8_t* data(){ return px_.data(); }

};
#endif
