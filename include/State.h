#pragma once

#include "Game.h"
#include "Sprite.h"
#include "Music.h"
#include "Alien.h"
#include "Sound.h"
#include "GameObject.h"
#include "Vec2.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"

using std::move;
using std::vector;
using std::shared_ptr;
using std::weak_ptr;

const string BGIMAGEFILE = "assets/img/ocean.jpg"; //background image file
const string MUSICFILE = "assets/audio/stageState.ogg"; //background music file
const string TILESETFILE = "assets/img/tileset.png"; //tileset file
const string TILEMAPFILE = "assets/map/tileMap.txt"; //tilemap file
const string PENGUINFACEFILE = "assets/img/penguinface.png"; //penguin face file
const string BOOMAUDIOFILE = "assets/audio/boom.wav"; //explosion audio file
const int TILEWIDTH = 64; //tile width in pixels
const int TILEHEIGHT = 64; //tile height in pixels
const int NMINIONSSTD = 4; //standard number of minons

class Game;

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
