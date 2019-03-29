#ifndef MUSIC_H
#define MUSIC_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>

using std::string;

class Music{
    
    public:
        Music();
        Music(string);
        ~Music();

        void Play(int);
        void Stop(int);
        void Open(string);
        bool IsOpen();

    private:
        Mix_Music* music;
};

#endif // MUSIC_H
