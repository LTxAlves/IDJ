#include "Game.h"
#include "TitleState.h"

int main(int argc, char* argv[]){

    Game& game = Game::GetInstance();

    TitleState* state = new TitleState();

    game.Push(state);
    game.Run();

    delete state;

    return 0;
}