#include <iostream>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Game.h"
#include "Music.h"
#include "Sprite.h"
#include "State.h"

int main(int argc, char* argv[]){   //argc and argv required by SDL  

    Game::GetInstance().Run();  //Run game

    return 0;
}
