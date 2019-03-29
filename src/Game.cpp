#include "Game.h"
#include "State.h"

Game* Game::instance;

Game& Game::GetInstance(){

    if(instance == nullptr)
        instance = new Game("Leonardo_T_Alves-160012007", 1024, 600);
    return *(instance);
}

Game::Game(string title, int width, int height){

    auto SDL_flags = (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER); //flags para inicializar a SDL
    auto Img_flags = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF); //flags para escolher os formatos de imagem
    auto Mix_flags = (MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_FLAC); //flags para escolher os formatos de áudio

    if(instance != nullptr){ //checa existêcia de instância (padrão Singleton)
        SDL_Log("Error! Instance already exists!\n");
    }
    else{
        instance = this;
    }

    if (SDL_Init(SDL_flags) != 0) {  //checa inicialização da SDL
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }

    if(IMG_Init(Img_flags) == 0){ //checa inicialiazção do processador de imagens da SDL
        SDL_Log("Function \"IMG_Init\" did not initialize any loader: %s", Mix_GetError());
        exit(1);
    }

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); //necessário devido a um bug na versão 2.0.2 da SDL_Mixer

    if(Mix_Init(Mix_flags) == 0){ //checa inicialização do mixer da SDL
        SDL_Log("Function \"Mix_Init\" did not initialize any loader: %s", SDL_GetError());
        exit(1);
    }

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    if(window == nullptr){ //checa erro de criação da janela
        SDL_Log("Error creating window: %s", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr){ //checa erro de criação do renderer
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

    while (!state->QuitRequested()){
        state->Update(33);
        state->Render();
        SDL_RenderPresent(renderer);
    }

}
