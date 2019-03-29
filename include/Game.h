#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Music.h"
#include "Sprite.h"
#include "State.h"

using namespace std;

class Game{
    
    private:
        Game(string, int, int);
        /* data */
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();

};

#endif // GAME_H
