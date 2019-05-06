#pragma once

#include <memory>
#include "Constants.h"
#include "Component.h"

using std::string;
using std::weak_ptr;

class Sprite;
class Bullet;

class Minion : public Component{

    public:
        Minion(GameObject&, weak_ptr<GameObject>, float = 0);
        
        void Update(float);
        void Render();
        bool Is(string);
        void Shoot(Vec2);

    private:
        weak_ptr<GameObject> alienCenter;
        float arc;
};