#include "Sound.h"

Sound::Sound(GameObject& associated) : Component(associated){

    chunk = nullptr;

    channel = -2; //arbitrary value (not recognized by SDL_PlayChannel) to check if channel exists
}

Sound::Sound(GameObject& associated, string file) : Sound(associated){

    Open(file);
}

Sound::~Sound(){

    if(IsOpen()){
        Mix_HaltChannel(channel);
    }
    else
        SDL_Log("Error! No chunk allocated!\n");
}

void Sound::Play(int times = 1){

    if(chunk != nullptr && times > 0)
        channel = Mix_PlayChannel(-1, chunk, times-1);
    else
        SDL_Log("Error playing Sound\n");
}

void Sound::Stop(){

    if(chunk != nullptr)
        Mix_HaltChannel(channel);
}

void Sound::Open(string file){

    chunk = Resources::GetSound(file);
}

bool Sound::IsOpen(){

    if(chunk != nullptr && channel != -2)
        return true;

    return false;
}

int Sound::GetChannel(){

    return channel;
}

void Sound::Update(float dt){

 //does nothing
}

void Sound::Render(){

 //does nothing
}

bool Sound::Is(string type){

    return (type.compare("Sound") == 0 ? true : false);
}