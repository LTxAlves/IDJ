#ifndef SOUND_H
#define SOUND_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include "GameObject.h"
#include "Component.h"

using std::string;

class Sound : public Component{
    
    public:
        Sound();
        Sound(GameObject&);
        Sound(GameObject&, string);

        ~Sound();

        void Play(int);
        void Stop();
        void Open(string);
        bool IsOpen();

        void Update(float);
        void Render();
        bool Is(string);

    private:
        Mix_Chunk* chunk;
        int channel;
};

#endif //SOUND_H