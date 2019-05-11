#pragma once

#include <unordered_map>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN

#define W_KEY               SDLK_w
#define A_KEY               SDLK_a
#define S_KEY               SDLK_s
#define D_KEY               SDLK_d

#define SPACE_KEY           SDLK_SPACE
#define ESCAPE_KEY          SDLK_ESCAPE

#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT

#define DPAD_UP             SDL_CONTROLLER_BUTTON_DPAD_UP
#define DPAD_DOWN           SDL_CONTROLLER_BUTTON_DPAD_DOWN
#define DPAD_LEFT           SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define DPAD_RIGHT          SDL_CONTROLLER_BUTTON_DPAD_RIGHT

using std::unordered_map;

class InputManager{

    public:
        void Update();

        bool KeyPress(int);
        bool KeyRelease(int);
        bool IsKeyDown(int);

        bool MousePress(int);
        bool MouseRelease(int);
        bool IsMouseDown(int);

        bool ControllerPress(int);
        bool ControllerRelease(int);
        bool IsControllerDown(int);

        int GetMouseX();
        int GetMouseY();

        bool QuitRequested();

        static InputManager& GetInstance();

        SDL_GameController* controller;

    private:
        InputManager();
        ~InputManager();

        bool mouseState[6];
        int mouseUpdate[6];

        unordered_map<int, bool> keyState;
        unordered_map<int, int> keyUpdate;

        unordered_map<int, bool> controllerState;
        unordered_map<int, int> controllerUpdate;

        bool quitRequested;

        int updateCounter;

        int mouseX;
        int mouseY;
};