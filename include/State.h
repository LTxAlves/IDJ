#ifndef STATE_H
#define STATE_H

#include "Music.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Rect.h"

using std::vector;
using std::unique_ptr;

class State{

    public:
        State();
        ~State();

        bool QuitRequested();

        void LoadAssets();
        void Update(float);
        void Render();

    private:
        void Input();

        void AddObject(int, int);

        Sprite bg;
        Music music;
        bool quitRequested;

        vector<unique_ptr<GameObject>> objectArray;
};

#endif // STATE_H
