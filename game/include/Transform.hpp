#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "raymath.h"

struct Transform {
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
};

#endif