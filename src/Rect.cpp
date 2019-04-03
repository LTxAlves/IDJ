#include "Rect.h"
#include <math.h>

Rect::Rect(){

    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rect::Rect(float x_in, float y_in, float w_in, float h_in){

    x = x_in;
    y = y_in;
    w = w_in;
    h = h_in;
}

float Rect::distance(Rect rect1, Rect rect2){

    float center1[2], center2[2], del_x, del_y;

    center1[0] = rect1.x + (rect1.w/2);
    center1[1] = rect1.y + (rect1.h/2);

    center2[0] = rect2.x + (rect2.w/2);
    center2[1] = rect2.y + (rect2.h/2);

    del_x = center1[0] - center2[0];
    del_y = center1[1] - center2[1];

    return (sqrt((del_x*del_x) + (del_y*del_y)));
}

bool Rect::Contains(float x_coord, float y_coord){

    if(x_coord >= x && x_coord <= x+w && y_coord >= y && y_coord <= y+h)
        return true;

    return false;
}