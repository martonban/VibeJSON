#ifndef CUBE_HPP
#define CUPE_HPP

#include "raylib.h"

class Cube {
    public:
        Cube(Vector3 pos, float width, float height)
            : mPos(pos), mWidth(width), mHeight(height) {}
        void Render();
    private:
        Vector3 mPos;
        float mWidth;
        float mHeight;
};


#endif