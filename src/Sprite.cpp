#include "Sprite.h"
#include "GameObject.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) :    Component(associated),
                                            scale(1, 1),
                                            frameCount(1),
                                            currentFrame(0),
                                            timeElapsed(0),
                                            frameTime(1){

    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file, int frameCount, float frameTime) :  Component(associated),
                                                                                        scale(1, 1),
                                                                                        frameCount(frameCount),
                                                                                        currentFrame(0),
                                                                                        timeElapsed(0),
                                                                                        frameTime(frameTime){

    texture = nullptr;
    Open(file);
}

void Sprite::Open(string file){

    SDL_DestroyTexture(texture);

    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);

    associated.box.w = width/frameCount;
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
    dst_rect.w = clipRect.w * scale.x;
    dst_rect.h = clipRect.h * scale.y;


    auto rend = Game::GetInstance().GetRenderer(); //getting rederer for only instance of game
    
    if(SDL_RenderCopyEx(rend, texture, &clipRect, &dst_rect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0)
        SDL_Log("Unable to render texture: %s", SDL_GetError());
}

void Sprite::Render(){ //general render function, no parameters

    Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

int Sprite::GetWidth(){

    return (width/frameCount) * scale.x;
}

int Sprite::GetHeight(){

    return height * scale.y;
}

bool Sprite::IsOpen(){

    return (texture != nullptr) ? true : false;
}

void Sprite::Update(float dt){

    if(frameCount == 1) //no need to update single frame sprites
        return;

    timeElapsed += dt; //counts time elapsed

    if(timeElapsed >= frameTime){

        timeElapsed = 0; //resets time elapsed
        currentFrame = (currentFrame + 1) % frameCount; //keeps current frame updated and within [0, framecount - 1]
    }

    SetClip((width/frameCount) * currentFrame, clipRect.y, width/frameCount, height); //sets new clip
}

bool Sprite::Is(string type){

    return !type.compare("Sprite");
}

void Sprite::SetScaleX(float scaleX, float scaleY){ //sets scale factor

    if(scaleX > 0 && scaleY > 0) //sets scale only if scale factor is positive
        scale = Vec2(scaleX, scaleY);
}

Vec2 Sprite::GetScale(){ //returns scale factor

    return scale;
}

void Sprite::SetFrame(int frame){ //selects different frame to show

    if(frame < 0 || frame >= frameCount) //data validation
        return;

    currentFrame = frame; //selects frame
    SetClip((width/frameCount) * currentFrame, clipRect.y, width/frameCount, height); //sets new clip
}

void Sprite::SetFrameCount(int frameCount){ //changes number of frames in image

    if(frameCount <= 0) //data validation
        return;
    
    this->frameCount = frameCount;

    associated.box.w = width/frameCount;
    SetClip((width/frameCount) * currentFrame, clipRect.y, width/frameCount, height); //sets new clip
}

void Sprite::SetFrameTime(float frameTime){ //changes time toshow each frame

    if(frameTime <= 0) //data validation
        return;

    this->frameTime = frameTime;
    timeElapsed = 0;
}