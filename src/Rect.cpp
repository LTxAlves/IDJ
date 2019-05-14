#include "Rect.h"
#include "Vec2.h"

#include <math.h>

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

float Rect::Distance(Rect rect){ //calculates distance between 2 rects centerpoints

    return CenterPoint().Distance(rect.CenterPoint());
}

bool Rect::Contains(float x_coord, float y_coord){ //checks if rect contains coordinates given

    if(x_coord >= x && x_coord <= x+w && y_coord >= y && y_coord <= y+h)
        return true;

    return false;
}

Rect Rect::operator+(const Vec2& vec){ //sums rect with vec2 (moves rect along vec) and returns a new rect

    return Rect(x + vec.x, y + vec.y, w, h);
}

Rect Rect::operator-(const Vec2& vec){ //subtracts rect with vec2 (moves rect along - vec) and returns a new rect

    return Rect(x - vec.x, y - vec.y, w, h);
}

Rect Rect::operator*(const Vec2& scale){

    Rect result = *this;
    result.w *= scale.x;
    result.h *= scale.y;

    return result;
}

void Rect::operator+=(const Vec2& vec){ //sums rect with vec2 (moves rect along vec), moving it

    x += vec.x;
    y += vec.y;
}

void Rect::operator-=(const Vec2& vec){ //subtracts rect with vec2 (moves rect along - vec), movint it

    x -= vec.x;
    y -= vec.y;
}

void Rect::operator*=(const Vec2& scale){

    w *= scale.x;
    h *= scale.y;
}

void Rect::operator=(const Rect& rec){ //assigns this rect to a given rect

    x = rec.x;
    y = rec.y;
    w = rec.w;
    h = rec.h;
}

Vec2 Rect::Position(){ //returns position of rect

    return Vec2(x, y);
}

Vec2 Rect::CenterPoint(){ //calculates coordinates of center point of rectangle

    Vec2 vec(x + w/2.0, y + h/2.0);

    return vec;
}

void Rect::CenterAt(Vec2 centerPos){

    x = centerPos.x - (w)/2;
    y = centerPos.y - (h)/2;
}

void Rect::CenterAt(float xCenter, float yCenter){

    x = xCenter - w/2;
    y = yCenter - h/2;
}