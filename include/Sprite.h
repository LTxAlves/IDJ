#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using std::string;

class Sprite{
    
    public:
        Sprite();
        Sprite(string);
        ~Sprite();

        void Open(string);
        void SetClip(int, int, int, int);
        void Render(int, int);

        int GetWidth();
        int GetHeight();

        bool IsOpen();

    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
};

#endif // SPRITE_H
