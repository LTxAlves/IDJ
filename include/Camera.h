#pragma once

#include "Constants.h"
#include "Vec2.h"

class GameObject;

class Camera{

    public:
        static void Follow(GameObject*);
        static void Unfollow();
        static void Update(float);

        static Vec2 pos;
        static Vec2 speed;

    private:
        static GameObject* focus;

};