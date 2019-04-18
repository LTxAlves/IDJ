#include "InputManager.h"

InputManager::InputManager() :  mouseState{false, false, false, false, false, false},
                                mouseUpdate{0, 0, 0, 0, 0, 0},
                                quitRequested(false),
                                updateCounter(0),
                                mouseX(0),
                                mouseY(0){

}

InputManager::~InputManager(){

    keyState.clear();
    keyUpdate.clear();
}

void InputManager::Update(){

    SDL_Event event;

    SDL_GetMouseState(&mouseX, &mouseY);

    quitRequested = false;

    updateCounter++;

    while(SDL_PollEvent(&event)){

        if(!event.key.repeat){
            switch(event.type){

                case SDL_QUIT:
                    quitRequested = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mouseState[event.button.button] = true;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;

                case SDL_MOUSEBUTTONUP:
                    mouseState[event.button.button] = false;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;

                case SDL_KEYDOWN:
                    keyState[event.key.keysym.sym] = true;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;

                case SDL_KEYUP:
                    keyState[event.key.keysym.sym] = false;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;
            }
        }
    }
}

bool InputManager::KeyPress(int key){

    return (keyState[key] && (keyUpdate[key] == updateCounter)) ? true : false;
}

bool InputManager::KeyRelease(int key){

    return (!keyState[key] && (keyUpdate[key] == updateCounter)) ? true : false;
}

bool InputManager::IsKeyDown(int key){

    return keyState[key];
}

bool InputManager::MousePress(int button){

    return (mouseState[button] && (mouseUpdate[button] == updateCounter)) ? true : false;
}

bool InputManager::MouseRelease(int button){

    return (!mouseState[button] && (mouseUpdate[button] == updateCounter)) ? true : false;
}

bool InputManager::IsMouseDown(int button){

    return mouseState[button];
}

int InputManager::GetMouseX(){

    return mouseX;
}

int InputManager::GetMouseY(){

    return mouseY;
}

bool InputManager::QuitRequested(){

    return quitRequested;
}

InputManager& InputManager::GetInstance(){

    static InputManager inputManager;

    return inputManager;
}