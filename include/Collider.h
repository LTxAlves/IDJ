#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Rect.h"

class GameObject;

class Collider : public Component{

    public:
        Collider(GameObject&, Vec2 = {1, 1}, Vec2 = {0, 0});

        Rect box;

        void Update(float);
        void Render();
        bool Is(string);

        void SetScale(Vec2);
        void SetOffset(Vec2);

    private:
        Vec2 scale;
        Vec2 offset;
};
