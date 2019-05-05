#pragma once

#include <math.h>
#include "Vec2.h"

class Vec2;

class Rect{

    public:
        Rect();
        Rect(float, float, float, float);
        
        float x, y, w, h;

        float Distance(Rect);

        bool Contains(float, float);

        Rect operator+(const Vec2&);
        Rect operator-(const Vec2&);

        void operator+=(const Vec2&);
        void operator-=(const Vec2&);
        
        void operator=(const Rect&);

        Vec2 Position();
        Vec2 CenterPoint();
};