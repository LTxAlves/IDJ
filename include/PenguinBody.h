#pragma once

#include <iostream>
#include <memory>
#include "Component.h"
#include "Vec2.h"

using std::weak_ptr;

class PenguinBody : public Component{

    public:
        PenguinBody(GameObject&);
        ~PenguinBody();

        void Start();
        void Update(float);
        void Render();
        bool Is(string);

        static PenguinBody* player;

        void NotifyCollision(GameObject&);

        Vec2 Position();
    
    private:
        weak_ptr<GameObject> pcannon;

        Vec2 speed;
        float linearSpeed;
        float angle;

        int hp;
};