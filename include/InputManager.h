#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define SPACE_KEY           SDLK_SPACE
#define ESCAPE_KEY          SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT

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

        int GetMouseX();
        int GetMouseY();

        bool QuitRequested();

        static InputManager& GetInstance();

    private:
        InputManager();
        ~InputManager();

        bool mouseState[6];
        int mouseUpdate[6];

        unordered_map<int, bool> keyState;
        unordered_map<int, int> keyUpdate;

        bool quitRequested;

        int updateCounter;

        int mouseX;
        int mouseY;
};

#endif //INPUT_MANAGER_H