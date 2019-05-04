#pragma once

#include <iostream>
#include "GameObject.h"

using std::string;

class GameObject;

class Component{

    public:
        Component(GameObject&);
        virtual ~Component();

        virtual void Update(float) = 0;
        virtual void Render() = 0;
        virtual bool Is(string) = 0;

        virtual void Start();

    protected:
        GameObject& associated;
};