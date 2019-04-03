#ifndef VEC2_H
#define VEC2_h

class Vec2{

    public:
        Vec2();
        Vec2(float, float);

        float x, y;

        Vec2 GetRotated(double);

        Vec2 operator+(const Vec2&);

        Vec2 VectorTimesScalar(Vec2, float);
        float Magnitude(Vec2);

        Vec2 Normalized(Vec2);
};

#endif //VEC2_H