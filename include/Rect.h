#pragma once

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

        void operator+=(const Vec2&);
        void operator-=(const Vec2&);
        
        void operator=(const Rect&);

        Vec2 Position();
        Vec2 CenterPoint();

        void CenterAt(Vec2);
        void CenterAt(float, float);
};