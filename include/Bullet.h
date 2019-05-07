#pragma once

#include "Component.h"
#include "Vec2.h"

class Sprite;

class Bullet : public Component{

    public:
        Bullet(GameObject&, float, float, int, float, string, int, float);

        void Update(float);
        void Render();
        bool Is(string);

        int GetDamage();

    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
};