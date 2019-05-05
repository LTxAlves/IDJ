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

Rect Rect::operator+(const Vec2& vec){

    Rect newRect;

    newRect.x = this->x + vec.x;
    newRect.y = this->y + vec.y;
    newRect.w = this->w;
    newRect.h = this->h;

    return newRect;
}

Rect Rect::operator-(const Vec2& vec){

    Rect newRect;

    newRect.x = this->x - vec.x;
    newRect.y = this->y - vec.y;
    newRect.w = this->w;
    newRect.h = this->h;

    return newRect;
}

void Rect::operator+=(const Vec2& vec){

    this->x += vec.x;
    this->y += vec.y;
}

void Rect::operator-=(const Vec2& vec){

    this->x -= vec.x;
    this->y -= vec.y;
}

void Rect::operator=(const Rect& rec){

    this->x = rec.x;
    this->y = rec.y;
    this->w = rec.w;
    this->h = rec.h;
}