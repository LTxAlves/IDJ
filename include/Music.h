#ifndef MUSIC_H
#define MUSIC_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>

using std::string;

class Music{
    
    public:
        Music();        //Music constructor
        Music(string);  //Music overloaded constructor
        ~Music();       //Music destructor

        void Play(int);     //Function to play a new song
        void Stop(int);     //Function to stop playing current song
        void Open(string);  //Function to open a music file
        bool IsOpen();      //Function to check if a music file is open

    private:
        Mix_Music* music;   //Pointer to game's music
};

#endif // MUSIC_H
