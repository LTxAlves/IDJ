#include "Vec2.h"
#include <math.h>

Vec2::Vec2(){

    x = 0;
    y = 0;
}

Vec2::Vec2(float x_in, float y_in){

    x = x_in;
    y = y_in;
}

void Vec2::Rotate(double theta){

    float x_new, y_new;

    x_new = x*cos(theta) - y*sin(theta);
    y_new = y*cos(theta) - x*sin(theta);

    x = x_new;
    y = y_new;
}

Vec2 Vec2::GetRotated(double theta){

    this->Rotate(theta);
    return *this;
}

Vec2 Vec2::operator+(const Vec2& vec){

    x += vec.x;
    y += vec.y;

    return *this;
}

Vec2 Vec2::VectorTimesScalar(Vec2 vector, float scalar){

    Vec2 newVec;

    newVec.x = vector.x*scalar;
    newVec.y = vector.y*scalar;

    return newVec;
}

float Vec2::Magnitude(Vec2 vector){

    return sqrt(vector.x*vector.x + vector.y*vector.y);
}

Vec2 Vec2::Normalized(Vec2 vector){

    Vec2 normal;

    normal.x = vector.x/Magnitude(vector);
    normal.y = vector.y/Magnitude(vector);

    return normal;
}