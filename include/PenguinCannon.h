#pragma once

#include <memory>
#include "Component.h"

using std::weak_ptr;

class PenguinCannon : public Component{

    public:
        PenguinCannon(GameObject&, weak_ptr<GameObject>);

        void Update(float);
        void Render();
        bool Is(string);

        void Shoot();

    private:
        weak_ptr<GameObject> pbody;

        float angle;
};