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

#define BGIMAGEFILE "assets/img/ocean.jpg" //background image file
#define MUSICFILE "assets/audio/stageState.ogg" //background music file
#define TILESETFILE "assets/img/tileset.png" //tileset file
#define TILEMAPFILE "assets/map/tileMap.txt" //tilemap file
#define PENGUINFACEFILE "assets/img/penguinface.png" //penguin face file
#define BOOMAUDIOFILE "assets/audio/boom.wav" //explosion audiio file
#define TILEWIDTH 64 //tile width in pixels
#define TILEHEIGHT 64 //tile height in pixels
#define PI 3.14159265359 //value of constant pi

using std::move;
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
