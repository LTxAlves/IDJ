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

Vec2 Vec2::GetRotated(double theta){

    Vec2 newVec;

    newVec.x = x*cos(theta) - y*sin(theta);
    newVec.y = y*cos(theta) - x*sin(theta);

    x = newVec.x;
    y = newVec.y;

    return newVec;
}

Vec2 Vec2::operator+(const Vec2& vec){

    Vec2 newVec2;

    newVec2.x = this->x + vec.x;
    newVec2.y = this->y + vec.y;

    return newVec2;
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