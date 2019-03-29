#include "Game.h"
#include "State.h"

Game* Game::instance;

Game& Game::GetInstance(){

    if(instance == nullptr)
        instance = new Game("Leonardo_T_Alves-160012007", 1024, 600);
    return *(instance);
}

Game::Game(string title, int width, int height){

    auto SDL_flags = (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);    //flags for SDL_Init()
    auto Img_flags = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);          //flags for image formats in Img_Init()
    auto Mix_flags = (MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_FLAC);         //flags for audio formats in Mix_Init()

    if(instance != nullptr){ //check if a game instance already exists
        SDL_Log("Error! Instance already exists!\n");
    }
    else{
        instance = this;
    }

    if (SDL_Init(SDL_flags) != 0) {  //check if SDL initialized correctly
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }

    if(IMG_Init(Img_flags) == 0){ //check if SDL_Image initializedcorrectly
        SDL_Log("Function \"IMG_Init\" did not initialize any loader: %s", Mix_GetError());
        exit(1);
    }

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); //recquired due to glitch in SDL_mixer version 2.0.2

    if(Mix_Init(Mix_flags) == 0){ //check if SDL_mixer initialized correctly
        SDL_Log("Function \"Mix_Init\" did not initialize any loader: %s", SDL_GetError());
        exit(1);
    }


    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    if(window == nullptr){ //check errors in creating window
        SDL_Log("Error creating window: %s", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr){ //check errors in creating renderer
        SDL_Log("Error creating renderer: %s", SDL_GetError());
        exit(1);
    }

    state = new State();
}

Game::~Game(){

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_Quit();
    Mix_CloseAudio();

    IMG_Quit();

    SDL_Quit();

    delete state;
}

State& Game::GetState(){

    return *state;
}

SDL_Renderer* Game::GetRenderer(){

    return renderer;
}

void Game::Run(){

    while (!state->QuitRequested()){ //Run game until user quits
        state->Update(33);
        state->Render();
        SDL_RenderPresent(renderer);
    }

}
