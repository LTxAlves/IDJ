#pragma once

#include <iostream>
#include "Component.h"
#include "Timer.h"

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

using std::string;

class Text : public Component{
    public:
        enum TextStyle {SOLID, SHADED, BLENDED};

        Text(GameObject&, string, int, TextStyle,  string, SDL_Color, float = 0);
        ~Text();

        void Update(float); 
        void Render();
        bool Is(string);

        void SetText(string);
        void SetColor(SDL_Color);
        void SetStyle(TextStyle);
        void SetFontFile(string);
        void SetFontSize(int);

    private:
        
        void RemakeTexture();

        TTF_Font* font;
        SDL_Texture* texture;

        string text;
        TextStyle style;
        string fontFile;
        int fontSize;
        SDL_Color color;

        float showTime;

        Timer timer;
};
