#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include "GameObject.h"
#include "Component.h"
#include "Resources.h"

using std::string;

class Sound : public Component{
    
    public:
        Sound(GameObject&);
        Sound(GameObject&, string);

        ~Sound();

        void Play(int);
        void Stop();
        void Open(string);
        bool IsOpen();

        int GetChannel();

        void Update(float);
        void Render();
        bool Is(string);

    private:
        Mix_Chunk* chunk;
        int channel;
};