#ifndef STATE_H
#define STATE_H

using namespace std;

#include "Music.h"
#include "Sprite.h"

class State{

    public:
        State();

        bool QuitRequested();

        void LoadAssets();
        void Update(float);
        void Render();

    private:
        Sprite bg;
        Music music;
        bool quitRequested;
};

#endif // STATE_H
