#pragma once

#include <math.h>
#include "Rect.h"
#include "Constants.h"

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
        float operator*(const Vec2&);

        Rect operator+(const Rect&);
        Rect operator-(const Rect&);

        bool operator==(const Vec2&);
        bool operator>(const Vec2&);
        bool operator<(const Vec2&);
        bool operator!=(const Vec2&);
        bool operator>=(const Vec2&);
        bool operator<=(const Vec2&);

        float Magnitude();

        Vec2 Normalized();

        float Distance(Vec2);
        float Inclination();
};