#ifndef STATE_H
#define STATE_H

#include "Game.h"
#include "Sprite.h"
#include "Music.h"
#include "Face.h"
#include "Sound.h"
#include "GameObject.h"
#include "Vec2.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"

using std::vector;
using std::shared_ptr;

class Game;

class State{

    public:
        State();
        ~State();

        bool QuitRequested();

        void LoadAssets();
        void Update(float);
        void Render();

    private:
        void AddObject(int, int);

        Music music;
        bool quitRequested;

        vector<shared_ptr<GameObject>> objectArray;
};

#endif // STATE_H
