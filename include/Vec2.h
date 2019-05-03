#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include "Rect.h"

#define PI 3.14159265359 //value of constant pi

class Rect;

class Vec2{

    public:
        Vec2();
        Vec2(float, float);

        float x, y;

        void Rotate(double);
        Vec2 GetRotated(double);

        Vec2 operator+(const Vec2&);
        Vec2 operator-(const Vec2&);
        Vec2& operator+=(const Vec2&);
        Vec2& operator-=(const Vec2&);
        Vec2 operator*(const float);

        float Magnitude();

        Vec2 Normalized();

        float Distance(Vec2);
        float Inclination();
};

#endif //VEC2_H