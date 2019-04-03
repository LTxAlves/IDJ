#ifndef FACE_H
#define FACE_H

#include "Component.h"
#include "GameObject.h"

using std::string;

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

#endif