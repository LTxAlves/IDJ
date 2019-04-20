#include "Rect.h"

Rect::Rect():   x(0),
                y(0),
                w(0),
                h(0){ //initializes with 0 value


}

Rect::Rect(float x_in, float y_in, float w_in, float h_in) :    x(x_in),
                                                                y(y_in),
                                                                w(w_in),
                                                                h(h_in){ //initializes with given values


}

float Rect::distance(Rect rect){ //calculates distance between 2 rects centerpoints

    return CenterPoint().Distance(rect.CenterPoint());
}

bool Rect::Contains(float x_coord, float y_coord){ //checks if rect contains coordinates given

    if(x_coord >= x && x_coord <= x+w && y_coord >= y && y_coord <= y+h)
        return true;

    return false;
}

Vec2 Rect::CenterPoint(){ //calculates coordinates of center point of rectangle

    Vec2 vec(x + w/2.0, y + h/2.0);

    return vec;
}