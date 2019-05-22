#pragma once

#include <iostream>
#include <unordered_map>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using std::string;
using std::unordered_map;

class Resources{

    public:
        static SDL_Texture* GetImage(string);
        static void ClearImages();

        static Mix_Music* GetMusic(string);
        static void ClearMusics();

        static Mix_Chunk* GetSound(string);
        static void ClearSounds();

        static void ClearAll();

    private:
        static unordered_map<string, SDL_Texture*> imageTable;

        static unordered_map<string, Mix_Music*> musicTable;

        static unordered_map<string, Mix_Chunk*> soundTable;

};