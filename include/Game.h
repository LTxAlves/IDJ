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
        Game(string, int, int); //Game constructor private (singleton)
        static Game* instance;  //Game's only instance (singleton)
        SDL_Window* window;     //Game window
        SDL_Renderer* renderer; //Game renderer
        State* state;           //Game state

    public:
        ~Game();                        //Game destructor
        void Run();                     //Function to run game
        SDL_Renderer* GetRenderer();    //Funtion to get game's renderer
        State& GetState();              //Function to get a pointer to game's state
        static Game& GetInstance();     //Function to get a pointer to game's (only) instance

};

#endif // GAME_H
