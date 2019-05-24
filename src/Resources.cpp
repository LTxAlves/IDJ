#include "Resources.h"
#include "Game.h"

using std::to_string;

unordered_map<string, SDL_Texture*> Resources::imageTable;  //initializes static variable
unordered_map<string, Mix_Music*> Resources::musicTable;    //initializes static variable
unordered_map<string, Mix_Chunk*> Resources::soundTable;    //initializes static variable
unordered_map<string, TTF_Font*> Resources::fontTable;    //initializes static variable

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

    if(!imageTable.empty()){
        for(auto it = imageTable.begin(); it != imageTable.end(); it++){
            if(it->second != nullptr){
                // SDL_DestroyTexture(it->second);
                it = imageTable.erase(it);
                if(it == imageTable.end())
                    break;
            }
        }

        imageTable.clear();
    }
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

    if(!musicTable.empty()){
        for(auto it = musicTable.begin(); it != musicTable.end(); it++){
            if(it->second != nullptr)
                Mix_FreeMusic(it->second);
        }

        musicTable.clear();
    }
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

    if(!soundTable.empty()){
        for(auto it = soundTable.begin(); it != soundTable.end(); it++){
            if(it->second != nullptr)
                Mix_FreeChunk(it->second);
        }

        soundTable.clear();
    }
}

TTF_Font* Resources::GetFont(string file, int size){

    TTF_Font* font;

    auto key = file + to_string(size);
    auto it = fontTable.find(key);

    if(it == fontTable.end()){ //checks if file is in font table
        font = TTF_OpenFont(file.c_str(), size); //loads font if it doesn't exist

        if(font == nullptr){ //checks if file was opened correctly and exists
            SDL_Log("Error loading font: %s", SDL_GetError());
            exit(1);
        }

        fontTable[file] = font; //adds font to map
        return font; //returns font
    }

    return it->second; //returns font
}

void Resources::ClearFonts(){

    if(!fontTable.empty()){
        for(auto it = fontTable.begin(); it != fontTable.end(); it++){
            if(it->second != nullptr)
                TTF_CloseFont(it->second);
        }

        fontTable.clear();
    }
}

void Resources::ClearAll(){

    if(!imageTable.empty())
        ClearImages();
    
    if(!musicTable.empty())
        ClearMusics();

    if(!soundTable.empty())
        ClearSounds();
}