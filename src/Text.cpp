#include "Text.h"
#include "Resources.h"
#include "Game.h"
#include "Camera.h"

SDL_Color black = {0, 0, 0, 225};

Text::Text(GameObject& associated, string fontFile, int fontSize, TextStyle style,  string text, SDL_Color color, float showTime) : Component(associated),
                                                                                                                                    text(text),
                                                                                                                                    style(style),
                                                                                                                                    fontFile(fontFile),
                                                                                                                                    fontSize(fontSize),
                                                                                                                                    color(color),
                                                                                                                                    showTime(showTime){

    font = nullptr;
    texture = nullptr;

    RemakeTexture();
}

Text::~Text(){

    if(texture != nullptr)
        SDL_DestroyTexture(texture);
}

void Text::Update(float dt){


    timer.Update(dt);
} 

void Text::Render(){

    if(texture == nullptr)
        return;

    if(timer.Get() >= showTime){
        SDL_Rect srcrect = {0, 0, (int) associated.box.w, (int) associated.box.h};
        SDL_Rect dstrect = {(int)(associated.box.x - Camera::pos.x), (int)(associated.box.y - Camera::pos.y), srcrect.w, srcrect.h};

        auto rend = Game::GetInstance().GetRenderer();

        SDL_RenderCopyEx(rend, texture, &srcrect, &dstrect, associated.angleDeg, nullptr, SDL_FLIP_NONE);

        if(timer.Get() >= 2*showTime)
            timer.Restart();
    }
}

bool Text::Is(string type){

    return !type.compare("Font");
}

void Text::SetText(string text){

    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color){

    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style){

    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(string fontFile){

    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize){

    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture(){

    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    font = Resources::GetFont(fontFile, fontSize);

    SDL_Surface* surface;

    switch (style){
        case SOLID:
            surface = TTF_RenderText_Solid(font, text.c_str(), color);
            break;
        
        case BLENDED:
            surface = TTF_RenderText_Blended(font, text.c_str(), color);
            break;

        case SHADED:
            surface = TTF_RenderText_Shaded(font, text.c_str(), color, black);
            break;
    }
    
    if(surface == NULL)
        SDL_Log("Error rendering text: %s", TTF_GetError());
    
    associated.box.w = surface->w;
    associated.box.h = surface->h;

    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    SDL_FreeSurface(surface);

    if(texture == nullptr)
        SDL_Log("Error creating texture from surface: %s", SDL_GetError());

}