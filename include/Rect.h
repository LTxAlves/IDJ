#pragma once

#include <iostream>

class Vec2;

class Rect{

    public:
        Rect();
        Rect(float, float, float, float);
        
        float x, y, w, h;

        float Distance(Rect);

        bool Contains(float, float);

        Rect operator+(const Vec2&);
        Rect operator-(const Vec2&);

        Rect operator*(const Vec2&);

        void operator+=(const Vec2&);
        void operator-=(const Vec2&);

        void operator*=(const Vec2&);
        
        void operator=(const Rect&);

        Vec2 Position();
        Vec2 CenterPoint();

        void CenterAt(Vec2);
        void CenterAt(float, float);

        friend std::ostream& operator<<(std::ostream& out, const Rect& rect){
            out << "(" << rect.x << ", " << rect.y << ")";
            out << ", (" << rect.x + rect.w << ", " << rect.y << ")";
            out << ", (" << rect.x << ", " << rect.y + rect.h << ")";
            out << ", (" << rect.x + rect.w << ", " << rect.y + rect.h << ")";
            return out;
        }
};