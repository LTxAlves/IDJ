#ifndef RECT_H
#define RECT_H

class Rect{
    public:
        Rect();
        Rect(float, float, float, float);
        
        float x, y, w, h;

        float distance(Rect, Rect);

};

#endif //RECT_H