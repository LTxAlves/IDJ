#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "Music.h"
#include "State.h"
#include "TileSet.h"

using std::move;
using std::vector;
using std::shared_ptr;
using std::weak_ptr;

class GameObject;

class StageState : public State{

    public:
        StageState();
        ~StageState();

        void LoadAssets();
        void Update(float);
        void Render();

        void Start();
        void Pause();
        void Resume();

    private:
        Music backgroundMusic;
        TileSet* tileSet;
};