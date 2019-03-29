#ifndef STATE_H
#define STATE_H

using namespace std;

#include "Music.h"
#include "Sprite.h"

class State{

    public:
        State();    //State constructor

        bool QuitRequested();   //Function to check if user closed game window

        void LoadAssets();  //Function to load music and image into ew state
        void Update(float); //Function to update current state
        void Render();      //Function to render new state

    private:
        Sprite bg;          //Background image
        Music music;        //State's music
        bool quitRequested; //Flag set to true when game window is closed
};

#endif // STATE_H
