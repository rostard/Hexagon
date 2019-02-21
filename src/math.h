//
// Created by rostard on 25.09.18.
//

#ifndef INC_2DPROJECT_MATH_H
#define INC_2DPROJECT_MATH_H

#include <math.h>
#include <iostream>


constexpr double degree_to_rad(float degree){
    return degree * 180.0 / M_PI;
};

struct vec2{
//    vec2(float x, float y);
//    vec2(const vec2& vec) = default;

    float x=0;
    float y=0;

    vec2 operator/(float f){
        return {x/f, y/f};
    }
    vec2 operator*(float f){
        return {x*f, y*f};
    }
    vec2 operator+(float f){
        return {x+f, y+f};
    }
    vec2 operator+(vec2 v){
        return {x+v.x, y+v.y};
    }
    vec2 operator-(float f){
        return {x-f, y-f};
    }
};

struct vec3{
//    vec3(float x, float y, float z);
//    vec3(const vec3& vec) = default;

    float x=0;
    float y=0;
    float z=0;

    vec3 operator/(float f){
        return {x/f, y/f, z/f};
    }
    vec3 operator*(float f){
        return {x*f, y*f, z*f};
    }
    vec3 operator+(float f){
        return {x+f, y+f, z+f};
    }
    vec3 operator-(float f){
        return {x-f, y-f, z-f};
    }
};

struct mat2{
    float m[4] = {0, 0, 0, 0};

    mat2 operator*(mat2 l){
        mat2 ret;
        ret.m[0] = m[0]*l.m[0] + m[1]*l.m[2];
        ret.m[1] = m[0]*l.m[1] + m[1]*l.m[3];
        ret.m[2] = m[2]*l.m[0] + m[3]*l.m[2];
        ret.m[3] = m[2]*l.m[1] + m[3]*l.m[3];
        return ret;
    }

    friend std::ostream &operator<<(std::ostream &os, const mat2 &mat21) {
        os << "m: [" << mat21.m[0] << " " << mat21.m[1] << std::endl << "    " << mat21.m[2] << ' ' << mat21.m[3] <<']'<<std::endl;
        return os;
    }
};

mat2 angleToMat(float angle);

#endif //INC_2DPROJECT_MATH_H
