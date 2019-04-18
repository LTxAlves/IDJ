#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

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

#endif //CAMERA_FOLLOWER_H