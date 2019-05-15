#include "Vec2.h"

Vec2::Vec2() :  x(0),
                y(0){ //initializes with 0 value

}

Vec2::Vec2(float x_in, float y_in){ //initializes with given values

    x = x_in;
    y = y_in;
}

void Vec2::Rotate(double theta){ //rotates a vec2

    float x_new, y_new;

    x_new = x*cos(theta) - y*sin(theta);
    y_new = y*cos(theta) + x*sin(theta);

    *this = {x_new, y_new};
}

Vec2 Vec2::GetRotated(double theta){ //returns rotated version of vec2

    Vec2 newVec = {x, y};
    newVec.Rotate(theta);
    return newVec;
}

Vec2 Vec2::operator+(const Vec2& vec){ //overload of operator + to add vec2 together

    return Vec2(this->x + vec.x, this->y + vec.y);
}

Vec2 Vec2::operator-(const Vec2& vec){ //overload of operator - to subtract vec2

    return Vec2(this->x - vec.x, this->y - vec.y);
}

void Vec2::operator=(const Vec2& vec){ //assigning operator

    this->x = vec.x;
    this->y = vec.y;
}

Vec2 Vec2::operator-(){ //bitwise unary operator of negation

    return(Vec2(-this->x, -this->y));
}


void Vec2::operator+=(const Vec2& vec){ //sums to vector and changes its value

    this->x += vec.x;
    this->y += vec.y;
}

void Vec2::operator-=(const Vec2& vec){ //subtracts from vector and changes its value

    this->x -= vec.x;
    this->y -= vec.y;
}

Vec2 Vec2::operator*(const float scalar){ //multiplies vec2 and scalar

    return Vec2(this->x * scalar, this->y * scalar);
}


float Vec2::operator*(const Vec2& vec){

    return this->x * vec.x + this->y * vec.y;
}

Rect Vec2::operator+(const Rect& rect){ //sums rect with vec2 (moves rect along ve2)

    return Rect(this->x + rect.x, this->y + rect.y, rect.w, rect.h);
}

Rect Vec2::operator-(const Rect& rect){ //subtracts vec2 from rect (moves rect along -vec2)
 
    return Rect(this->x - rect.x, this->y - rect.y, rect.w, rect.h);
}

float Vec2::Magnitude(){ //returns magnitude of vec2

    return sqrt(this->x*this->x + this->y*this->y);
}

Vec2 Vec2::Normalized(){ //returns normalized vec2

    return Vec2(this->x/this->Magnitude(), this->y/this->Magnitude());
}

float Vec2::Distance(Vec2 vec){ //distance between 2 points

    float del_x = x - vec.x;
    float del_y = y - vec.y;

    return sqrt(del_x*del_x + del_y*del_y);
}

float Vec2::Inclination(){ //angle between vector and +x axis

    return atan2(y, x) * RADTODEG;
}