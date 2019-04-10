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

Vec2 Vec2::VectorTimesScalar(Vec2 vector, float scalar){ //multiplies vec2 and scalar

    Vec2 newVec;

    newVec.x = vector.x*scalar;
    newVec.y = vector.y*scalar;

    return newVec;
}

float Vec2::Magnitude(Vec2 vector){ //returns magnitude of vec2

    return sqrt(vector.x*vector.x + vector.y*vector.y);
}

Vec2 Vec2::Normalized(Vec2 vector){ //returns normalized vec2

    Vec2 normal;

    normal.x = vector.x/Magnitude(vector);
    normal.y = vector.y/Magnitude(vector);

    return normal;
}