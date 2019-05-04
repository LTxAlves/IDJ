#pragma once

#include <math.h>
#include "Vec2.h"

class Vec2;

class Rect{

    public:
        Rect();
        Rect(float, float, float, float);
        
        float x, y, w, h;

        float distance(Rect);

        bool Contains(float, float);

        Vec2 CenterPoint();
};