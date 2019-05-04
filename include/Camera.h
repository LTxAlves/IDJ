#pragma once

#include "GameObject.h"
#include "Vec2.h"

#define CAMERA_SPEED 300

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

#include "Game.h"