#pragma once

#include <iostream>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Component.h"

using std::string;

class Sprite : public Component{
    
    public:
        Sprite(GameObject&);
        Sprite(GameObject&, string);

        void Open(string);
        void SetClip(int, int, int, int);
        void Render(int, int);
        void Render();

        int GetWidth();
        int GetHeight();

        bool IsOpen();

        void Update(float);

        bool Is(string);

    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
};

#include "Resources.h"