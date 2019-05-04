#pragma once

#include "Component.h"
#include "Camera.h"

using std::string;

class CameraFollower : public Component {

    public:
        CameraFollower(GameObject&);

        void Update(float);
        void Render();
        bool Is(string);

};