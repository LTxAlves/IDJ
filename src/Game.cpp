#include "Game.h"

Game* Game::instance;

Game::Game(string title, int width, int height) :   dt(0),
                                                    frameStart(0){

    auto SDL_flags = (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER); //flags for SDL_Init()
    auto Img_flags = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF); //flags for IMG_Init()
    auto Mix_flags = (MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_FLAC); //flags for Mix_Init()

    srand(time(NULL));

    if(instance != nullptr){ //checks if instance exists (Singleton)
        SDL_Log("Error! Instance already exists!\n");
        exit(1);
    }
    else{
        instance = this;
    }

    if(SDL_Init(SDL_flags) != 0)  //checks if SDL initialized
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());

    if(IMG_Init(Img_flags) == 0) //checks if IMG initialized
        SDL_Log("Function \"IMG_Init\" did not initialize any loader: %s", Mix_GetError());

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); //Needed due to bug in SDL_Mixer version 2.0.2

    if(Mix_Init(Mix_flags) == 0) //checks if MIX initialized
        SDL_Log("Function \"Mix_Init\" did not initialize any loader: %s", SDL_GetError());

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    if(window == nullptr) //checks if window was created
        SDL_Log("Error creating window: %s", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr) //checks if renderer was created
        SDL_Log("Error creating renderer: %s", SDL_GetError());

    state = new State();
}

Game::~Game(){  //destroys everything in reverse order of creation

    delete state;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_Quit();
}

Game& Game::GetInstance(){

    if(instance == nullptr) //checks existence of instance
        instance = new Game("Leonardo_T_Alves-160012007", SCREEN_WIDTH, SCREEN_HEIGHT); //creates instance if it doesn't exist
    return *(instance);
}

State& Game::GetState(){

    return *state;
}

SDL_Renderer* Game::GetRenderer(){

    return renderer;
}

void Game::Run(){

    state->Start();

    while(!state->QuitRequested()){
        InputManager::GetInstance().Update(); //gets inputs
        CalculateDeltaTime(); //changes dt
        state->Update(dt); //updates state
        state->Render(); //renders images
        SDL_RenderPresent(renderer); //changes renderization to present
        SDL_Delay(33); //delays 33ms for approximately a 30fps framerate
    }

    Resources::ClearImages(); //clear all images for clean exit
    Resources::ClearMusics(); //clear all music for clean exit
    Resources::ClearSounds(); //clear all sound for clean exit
}

float Game::GetDeltaTime(){

    return dt;
}

void Game::CalculateDeltaTime(){

    int newFrame = SDL_GetTicks(); //new frame time

    dt = (newFrame - frameStart)/1000.0; //difference in time in seconds

    frameStart = newFrame; //changes frame time
}