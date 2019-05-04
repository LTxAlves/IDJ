#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"

using std::string;
using std::rand;

class Face : public Component{

    public:
        Face(GameObject&);

        void Damage(int);

        void Update(float);
        void Render();
        bool Is(string);

    private:
        int hitpoints;
};