#include "Game.h"
#include "StageState.h"

int main(int argc, char* argv[]){

    Game& game = Game::GetInstance();

    StageState* state = new StageState();

    game.Push(state);
    game.Run();

    delete state;

    return 0;
}
