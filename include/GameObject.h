#pragma once

#include <iostream>
#include <vector>
#include <memory>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Component.h"
#include "Rect.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::move;

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

        void Start();

        Rect box;

    private:
        vector<shared_ptr<Component>> components;
        bool isDead;

        bool started;
};