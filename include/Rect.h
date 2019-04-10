#ifndef RECT_H
#define RECT_H

#include <math.h>

class Rect{
    public:
        Rect();
        Rect(float, float, float, float);
        
        float x, y, w, h;

        float distance(Rect, Rect);

        bool Contains(float, float);
};

#endif //RECT_H