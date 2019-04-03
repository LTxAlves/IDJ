#include "Sound.h"

using std::string;

Sound::Sound(GameObject& associated) : Component(associated){

    chunk = nullptr;

    channel = -2;
 
    associated_obj = associated;
}

Sound::Sound(GameObject& associated, string file) : Component(associated){

    Sound(associated);
    Open(file);
}

Sound::~Sound(){

    if(IsOpen()){
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
    }
    else
        SDL_Log("Error! No chunk allocated!\n");
}

void Sound::Play(int times = 1){

    channel = Mix_PlayChannel(-1, chunk, times-1);
}

void Sound::Stop(){

    if(chunk != nullptr)
        Mix_HaltChannel(channel);
}

void Sound::Open(string file){

    if(Mix_LoadWAV(file.c_str()) == nullptr){
        SDL_Log("Error opening file: %s", SDL_GetError());
        exit(1);
    }
}

bool Sound::IsOpen(){

    if(chunk != nullptr && channel != -2)
        return true;

    return false;
}

void Sound::Update(float dt){


}

void Sound::Render(){


}

bool Sound::Is(string type){

    return true;
}