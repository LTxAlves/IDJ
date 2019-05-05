#pragma once

#include <math.h>
#include "Rect.h"

const float PI = 3.14159265359; //value of constant pi

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

        void operator=(const Vec2&);

        Vec2 operator-();

        void operator-=(const Vec2&);
        void operator+=(const Vec2&);
        
        Vec2 operator*(const float);

        Rect operator+(const Rect&);
        Rect operator-(const Rect&);

        float Magnitude();

        Vec2 Normalized();

        float Distance(Vec2);
        float Inclination();
};