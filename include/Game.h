#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

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

    private:
        Game(string, int, int);

        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

};

#include "Resources.h"
#include "State.h"

#endif // GAME_H
