#pragma once

#include <iostream>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Component.h"
#include "Vec2.h"
#include "Timer.h"

using std::string;

class Resources;

class Sprite : public Component{
    
    public:
        Sprite(GameObject&);
        Sprite(GameObject&, string, int = 1, float = 1, float = 0);

        void Open(string);
        void SetClip(int, int, int, int);
        void Render(int, int);
        void Render();

        int GetWidth();
        int GetHeight();

        bool IsOpen();

        void Update(float);

        bool Is(string);

        void SetScaleX(float, float);
        Vec2 GetScale();

        void SetFrame(int);
        void SetFrameCount(int);
        void SetFrameTime(float);

    private:
        shared_ptr<SDL_Texture> texture;

        int width, height;

        SDL_Rect clipRect;

        Vec2 scale;

        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;

        Timer selfDestructCount;
        float secondsToSelfDestruct;
};