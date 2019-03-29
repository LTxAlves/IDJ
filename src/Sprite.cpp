#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(){

    texture = nullptr;
}

Sprite::Sprite(string file){

    texture = nullptr;
    Open(file);
}

Sprite::~Sprite(){

    if(texture != nullptr)
        SDL_DestroyTexture(texture);
}

void Sprite::Open(string file){

    if(texture != nullptr)
        SDL_DestroyTexture(texture);

    auto rend = Game::GetInstance().GetRenderer(); //getting rederer for single instance of game
    texture = IMG_LoadTexture(rend, file.c_str());

    if(texture == nullptr){
        SDL_Log("Unable to load texture: %s", IMG_GetError());
        exit(1);
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0,0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h){

    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y){

    SDL_Rect dst_rect;

    dst_rect.x = x;
    dst_rect.y = y;
    dst_rect.w = GetWidth();
    dst_rect.h = GetHeight();

    auto rend = Game::GetInstance().GetRenderer(); //getting rederer for only instance of game

    if(SDL_RenderCopy(rend, texture, &clipRect, &dst_rect) != 0){
        SDL_Log("Unable to render texture: %s", SDL_GetError());
        exit(1);
    }

}

int Sprite::GetWidth(){

    return width;
}

int Sprite::GetHeight(){

    return height;
}

bool Sprite::IsOpen(){

    return (texture != nullptr) ? true : false;
}
