#include "State.h"
#include "Game.h"

State::State() :    bg("assets/img/ocean.jpg"),
                    music("assets/audio/stageState.ogg"){

    quitRequested = false;
    LoadAssets();
    music.Play(-1);
}

void State::LoadAssets(){

}

void State::Update(float dt){

    quitRequested = (SDL_QuitRequested());

    SDL_Delay(dt);
}

void State::Render(){

    bg.Render(0, 0);
}

bool State::QuitRequested(){

    return quitRequested;
}
