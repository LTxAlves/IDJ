#pragma once

#include "Component.h"
#include "Sprite.h"

class Bullet : public Component{

    public:
        Bullet(GameObject&, float, float, int, float, string);

        void Update(float);
        void Render();
        bool Is(string);

        int GetDamage();

    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
};