#include "InputManager.h"
#include <iostream>

InputManager::InputManager() :  mouseState{false, false, false, false, false, false},
                                mouseUpdate{0, 0, 0, 0, 0, 0},
                                quitRequested(false),
                                updateCounter(0),
                                mouseX(0),
                                mouseY(0){ //initializes variables



    for(int i = 0; i < SDL_NumJoysticks(); i++){ //checks for game controllers activated
        if(SDL_IsGameController(i)) //cecks if iterator refers to controller
            controller = SDL_GameControllerOpen(0); //open game controller
        std::cout << controller << std::endl;
    }
}

InputManager::~InputManager(){

    // Close if opened
    if (controller != nullptr){
        SDL_GameControllerClose(controller);
        controller = nullptr;
    }
    
    keyState.clear();
    keyUpdate.clear();
}

void InputManager::Update(){

    SDL_Event event; //event variable

    SDL_GetMouseState(&mouseX, &mouseY); //updates mouse coordinates

    quitRequested = false; //resets quit request

    updateCounter++; //update counter increases

    while(SDL_PollEvent(&event)){

        if(!event.key.repeat){ //checks if event is repeated
            switch(event.type){ //checks which event happened

                case SDL_QUIT: //window close
                    quitRequested = true;
                    break;

                case SDL_MOUSEBUTTONDOWN: //mouse click
                    mouseState[event.button.button] = true;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;

                case SDL_MOUSEBUTTONUP: //mouse release
                    mouseState[event.button.button] = false;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;

                case SDL_KEYDOWN: //keyboard button press
                    keyState[event.key.keysym.sym] = true;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;

                case SDL_KEYUP: //keyboard button release
                    keyState[event.key.keysym.sym] = false;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;

                case SDL_CONTROLLERDEVICEADDED:
                    if(!controller){ //ifcontroller not alredy assigned
                        for(int i = 0; i < SDL_NumJoysticks(); i++){ //checks for game controllers activated
                            if(SDL_IsGameController(i)){ //cecks if iterator refers to controller
                                controller = SDL_GameControllerOpen(0); //open game controller
                                std::cout << "Device added: " << controller << std::endl;
                            }
                        }
                    }
                    break;

                case SDL_CONTROLLERDEVICEREMOVED:
                    if(controller != nullptr){
                        SDL_GameControllerClose(controller);
                        controller = nullptr;
                        std::cout << "Device removed: " << controller << std::endl;    
                    }
                    break;

                case SDL_CONTROLLERBUTTONUP:
                    std::cout << "button release: " << (int) event.cbutton.button << std::endl;
                    controllerState[event.cbutton.button] = false;
                    controllerUpdate[event.cbutton.button] = updateCounter;
                    break;

                case SDL_CONTROLLERBUTTONDOWN:
                    std::cout << "button press: " << (int) event.cbutton.button << std::endl;
                    controllerState[event.cbutton.button] = true;
                    controllerUpdate[event.cbutton.button] = updateCounter;
                    break;
            }
        }
    }
}

bool InputManager::KeyPress(int key){

    return (keyState[key] && (keyUpdate[key] == updateCounter)) ? true : false; //checks if key was pressed in last frame
}

bool InputManager::KeyRelease(int key){

    return (!keyState[key] && (keyUpdate[key] == updateCounter)) ? true : false; //checks if key was released in last frame
}

bool InputManager::IsKeyDown(int key){

    return keyState[key]; //checks if key is being held down
}

bool InputManager::MousePress(int button){

    return (mouseState[button] && (mouseUpdate[button] == updateCounter)) ? true : false; //ckecks if button was pressed in last frame
}

bool InputManager::MouseRelease(int button){

    return (!mouseState[button] && (mouseUpdate[button] == updateCounter)) ? true : false; //checks if button was released in last frame
}

bool InputManager::IsMouseDown(int button){

    return mouseState[button]; //checks if button is being held down
}

bool InputManager::ControllerPress(int button){

    return (controllerState[button] && (controllerUpdate[button] == updateCounter)) ? true : false; //checks if controller button was pressed in last frame
}

bool InputManager::ControllerRelease(int button){

    return (!controllerState[button] && (controllerUpdate[button] == updateCounter)) ? true : false; //checks if controller button was released in last frame
}

bool InputManager::IsControllerDown(int button){

    return  controllerState[button]; //checks if controller button is being held down
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

    static InputManager inputManager; //Meyer's singleton

    return inputManager;
}