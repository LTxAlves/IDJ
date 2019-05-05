#include "Sprite.h"

Sprite::Sprite(GameObject& associated) : Component(associated){

    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file) : Component(associated){

    texture = nullptr;
    Open(file);
}

void Sprite::Open(string file){

    SDL_DestroyTexture(texture);

    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0,0, width, height);

    associated.box.w = width;
    associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h){ //sets clip with given values

    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y){ //renders with given values

    SDL_Rect dst_rect;

    dst_rect.x = x;
    dst_rect.y = y;
    dst_rect.w = clipRect.w;
    dst_rect.h = clipRect.h;


    auto rend = Game::GetInstance().GetRenderer(); //getting rederer for only instance of game
    
    if(SDL_RenderCopy(rend, texture, &clipRect, &dst_rect) != 0)
        SDL_Log("Unable to render texture: %s", SDL_GetError());
}

void Sprite::Render(){ //general render function, no parameters

    Render(associated.box.x + Camera::pos.x, associated.box.y + Camera::pos.y);
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

void Sprite::Update(float dt){

 //does nothing
}

bool Sprite::Is(string type){

    return !type.compare("Sprite");
}