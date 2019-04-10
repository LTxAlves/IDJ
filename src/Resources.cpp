#include "Resources.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(string file){

    auto it = imageTable.find(file);

    if(it == imageTable.end()){

        auto rend = Game::GetInstance().GetRenderer(); //getting rederer for single instance of game
        auto texture = IMG_LoadTexture(rend, file.c_str());

        if(texture == nullptr){
            SDL_Log("Unable to load texture: %s", IMG_GetError());
            exit(1);
        }

        imageTable[file] = texture;
        return texture;
    }
    
    return it->second;
}

void Resources::ClearImages(){

    for(auto it = imageTable.begin(); it != imageTable.end(); it++){
        if(it->second != nullptr)
            SDL_DestroyTexture(it->second);
    }

    imageTable.clear();
}

Mix_Music* Resources::GetMusic(string file){

    Mix_Music* music;

    auto it = musicTable.find(file);

    if(it == musicTable.end()){
        music = Mix_LoadMUS(file.c_str());

        if(music == nullptr){
            SDL_Log("Error loading music: %s", SDL_GetError());
            exit(1);    
        }

        musicTable[file] = music;
        return music;
    }

    return it->second;
}

void Resources::ClearMusics(){

    for(auto it = musicTable.begin(); it != musicTable.end(); it++){
        if(it->second != nullptr)
            Mix_FreeMusic(it->second);
    }

    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(string file){

    Mix_Chunk* chunk;

    auto it = soundTable.find(file);

    if(it == soundTable.end()){
        chunk = Mix_LoadWAV(file.c_str());

        if(chunk == nullptr){
            SDL_Log("Error loading sound: %s", SDL_GetError());
            exit(1);
        }

        soundTable[file] = chunk;
        return chunk;
    }

    return it->second;
}

void Resources::ClearSounds(){

    for(auto it = soundTable.begin(); it != soundTable.end(); it++){
        if(it->second != nullptr)
            Mix_FreeChunk(it->second);
    }

    soundTable.clear();
}