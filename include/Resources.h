#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

using std::string;
using std::unordered_map;
using std::shared_ptr;

class Resources{

    public:
        static shared_ptr<SDL_Texture> GetImage(string);
        static void ClearImages();

        static Mix_Music* GetMusic(string);
        static void ClearMusics();

        static Mix_Chunk* GetSound(string);
        static void ClearSounds();

        static TTF_Font* GetFont(string, int);
        static void ClearFonts();

        static void ClearAll();

    private:
        static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;

        static unordered_map<string, Mix_Music*> musicTable;

        static unordered_map<string, Mix_Chunk*> soundTable;
        
        static unordered_map<string, TTF_Font*> fontTable;
};