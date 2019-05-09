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

    return Rect(this->x + vec.x, this->y + vec.y, this->w, this->h);
}

Rect Rect::operator-(const Vec2& vec){ //subtracts rect with vec2 (moves rect along - vec) and returns a new rect

    return Rect(this->x - vec.x, this->y - vec.y, this->w, this->h);
}

void Rect::operator+=(const Vec2& vec){ //sums rect with vec2 (moves rect along vec), moving it

    this->x += vec.x;
    this->y += vec.y;
}

void Rect::operator-=(const Vec2& vec){ //subtracts rect with vec2 (moves rect along - vec), movint it

    this->x -= vec.x;
    this->y -= vec.y;
}

void Rect::operator=(const Rect& rec){ //assigns this rect to a given rect

    this->x = rec.x;
    this->y = rec.y;
    this->w = rec.w;
    this->h = rec.h;
}

Vec2 Rect::Position(){ //returns position of rect

    return Vec2(this->x, this->y);
}

Vec2 Rect::CenterPoint(){ //calculates coordinates of center point of rectangle

    Vec2 vec(x + w/2.0, y + h/2.0);

    return vec;
}

void Rect::CenterAt(Vec2 centerPos){

    this->x = centerPos.x - this->w/2;
    this->y = centerPos.y - this->h/2;
}

void Rect::CenterAt(float xCenter, float yCenter){

    this->x = xCenter - this->w/2;
    this->y = yCenter - this->h/2;
}