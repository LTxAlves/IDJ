#include "Music.h"

using std::string;

Music::Music(){

    music = nullptr;
}

Music::Music(string file){

    music = nullptr;
    Open(file);
}

void Music::Play(int times = -1){

    if(music != nullptr){
        Mix_PlayMusic(music, times);
    }
    else{
        SDL_Log("No music assigned: %s", SDL_GetError());
    }
}

void Music::Stop(int msToStop = 1500){

    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file){

    music = Mix_LoadMUS(file.c_str());

    if(music == nullptr){
        SDL_Log("Unable to load music: %s", SDL_GetError());
        exit(1);
    }
}

bool Music::IsOpen(){

    return (music != nullptr ? true : false);
}

Music::~Music(){

    Stop(0);
    Mix_FreeMusic(music);
}
