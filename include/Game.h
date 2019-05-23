#pragma once

#include <iostream>
#include <cstdlib>
#include <memory>
#include <stack>
#include "Constants.h"
#include "State.h"

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

using std::string;
using std::stack;
using std::unique_ptr;

class Resources;

class Game{
    
    public:
        Game(string, int, int);
        ~Game();

        void Push(State*);

        void Run();
        
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();
        static Game& GetInstance();

        float GetDeltaTime();

    private:
        static Game* instance;

        SDL_Window* window;
        SDL_Renderer* renderer;
        State* storedState;

        stack<unique_ptr<State>> stateStack;

        float dt;
        int frameStart;

        void CalculateDeltaTime();
};