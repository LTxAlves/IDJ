#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using std::string;

class Sprite{
    
    public:
        Sprite();       //Sprite constructor
        Sprite(string); //Sprite overloaded constructor
        ~Sprite();      //Sprite destructor

        void Open(string);                  //Function to open an image file
        void SetClip(int, int, int, int);   //Function to set clipping ofimage file
        void Render(int, int);              //Function to reder image

        int GetWidth();     //Function to get image width
        int GetHeight();    //Function to get image height

        bool IsOpen();  //Function to check if image file is open

    private:
        SDL_Texture* texture;   //Image texture
        int width;              //Image width
        int height;             //Image height
        SDL_Rect clipRect;      //Rectagular clipping of image
};

#endif // SPRITE_H
