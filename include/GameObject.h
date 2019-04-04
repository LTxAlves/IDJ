#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <vector>
#include <memory>

#include "Component.h"
#include "Rect.h"

using std::string;
using std::vector;
using std::unique_ptr;

class Component;

class GameObject{

    public:
        GameObject();
        ~GameObject();

        void Update(float);
        void Render();

        bool IsDead();

        void RequestDelete();

        void AddComponent(Component*);
        void RemoveComponent(Component*);
        Component* GetComponent(string);

        Rect box;

    private:
        vector<Component*> components;
        bool isDead;
};

#endif //GAMEOBJECT_H