//
// Created by rostard on 25.09.18.
//

#include "math.h"

mat2 angleToMat(float angle) {
    return {cos(angle), -sin(angle),
            sin(angle), cos(angle)};
}

//vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}
//
//vec2::vec2(float x, float y) : x(x), y(y) {}
