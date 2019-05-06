#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "Music.h"

using std::move;
using std::vector;
using std::shared_ptr;
using std::weak_ptr;

class GameObject;

class State{

    public:
        State();
        ~State();

        bool QuitRequested();

        void LoadAssets();
        void Update(float);
        void Render();

        void Start();

        weak_ptr<GameObject> AddObject(GameObject*);
        weak_ptr<GameObject> GetObjectPtr(GameObject*);

        void AddObject(int, int);

    private:
        Music music;
        bool quitRequested;

        vector<shared_ptr<GameObject>> objectArray;

        bool started;
};