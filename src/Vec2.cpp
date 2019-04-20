#include "Vec2.h"

Vec2::Vec2(){ //initializes with 0 value

    x = 0;
    y = 0;
}

Vec2::Vec2(float x_in, float y_in){ //initializes with given values

    x = x_in;
    y = y_in;
}

void Vec2::Rotate(double theta){ //rotates a vec2

    float x_new, y_new;

    x_new = x*cos(theta) - y*sin(theta);
    y_new = y*cos(theta) - x*sin(theta);

    x = x_new;
    y = y_new;
}

Vec2 Vec2::GetRotated(double theta){ //returns rotated version of vec2

    this->Rotate(theta);
    return *this;
}

Vec2 Vec2::operator+(const Vec2& vec){ //overload of operator + to add vec2 together

    x += vec.x;
    y += vec.y;

    return *this;
}

Vec2 Vec2::operator-(const Vec2& vec){ //overload of operator - to subtract vec2

    x -= vec.x;
    y -= vec.y;

    return *this;
}

Vec2 Vec2::operator*(const float scalar){ //multiplies vec2 and scalar

    Vec2 newVec;

    newVec.x = x*scalar;
    newVec.y = y*scalar;

    return newVec;
}

float Vec2::Magnitude(Vec2 vec){ //returns magnitude of vec2

    return sqrt(vec.x*vec.x + vec.y*vec.y);
}

Vec2 Vec2::Normalized(Vec2 vec){ //returns normalized vec2

    Vec2 normal;

    normal.x = vec.x/Magnitude(vec);
    normal.y = vec.y/Magnitude(vec);

    return normal;
}

float Vec2::Distance(Vec2 vec){

    float del_x = x - vec.x;
    float del_y = y - vec.y;

    return sqrt(del_x*del_x + del_y*del_y);
}

float Vec2::Inclination(){

    return atan2(y, x) * 180 / PI;
}