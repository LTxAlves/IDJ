#pragma once

#include "Component.h"

using std::string;

class CameraFollower : public Component {

    public:
        CameraFollower(GameObject&);

        void Update(float);
        void Render();
        bool Is(string);

};