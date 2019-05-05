#pragma once

#include <iostream>
#include <cstdlib>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH  = 1024;

using std::string;

class State;
class Resources;

class Game{
    
    public:
        ~Game();

        void Run();
        
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();

        float GetDeltaTime();

    private:
        Game(string, int, int);

        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

        float dt;
        int frameStart;

        void CalculateDeltaTime();
};

#include "Resources.h"
#include "State.h"
#include "InputManager.h"
