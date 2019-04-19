#include "Resources.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;  //initializes static variable
unordered_map<string, Mix_Music*> Resources::musicTable;    //initializes static variable
unordered_map<string, Mix_Chunk*> Resources::soundTable;    //initializes static variable

SDL_Texture* Resources::GetImage(string file){

    auto it = imageTable.find(file);

    if(it == imageTable.end()){ //checks if file is in image table

        auto rend = Game::GetInstance().GetRenderer(); //getting rederer for single instance of game
        auto texture = IMG_LoadTexture(rend, file.c_str()); //loads image if it doesn't exist

        if(texture == nullptr){ //checks if it was loaded correctly
            SDL_Log("Unable to load texture: %s", IMG_GetError());
            exit(1);
        }

        imageTable[file] = texture; //asigns it
        return texture; //returns it
    }
    
    return it->second; //returns image
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

    if(it == musicTable.end()){ //checks if file is in music table
        music = Mix_LoadMUS(file.c_str()); //loads music if it doesn't exist

        if(music == nullptr){ //checks if file exists and was opened correctly
            SDL_Log("Error loading music: %s", SDL_GetError());
            exit(1);    
        }

        musicTable[file] = music; //adds music to map
        return music; //returns music
    }

    return it->second; //returns music
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

    if(it == soundTable.end()){ //checks if file is in sound table
        chunk = Mix_LoadWAV(file.c_str()); //loads sound if it doesn't exist

        if(chunk == nullptr){ //checks if file was opened correctly and exists
            SDL_Log("Error loading sound: %s", SDL_GetError());
            exit(1);
        }

        soundTable[file] = chunk; //adds sound to map
        return chunk; //returns sound
    }

    return it->second; //returns sound
}

void Resources::ClearSounds(){

    for(auto it = soundTable.begin(); it != soundTable.end(); it++){
        if(it->second != nullptr)
            Mix_FreeChunk(it->second);
    }

    soundTable.clear();
}