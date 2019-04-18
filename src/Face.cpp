#include "Face.h"

Face::Face(GameObject& associated) : Component(associated){

    hitpoints = 30; //sets initial HP
}

void Face::Damage(int damage){

    hitpoints -= damage; //takes damage

    if(hitpoints <= 0){ //checks for death
        hitpoints = 0; //prevents negative values in case of showing HP
        associated.RequestDelete(); //kills Face

        Sound* SoundPtr = static_cast<Sound*> (associated.GetComponent("Sound"));
        if(SoundPtr != nullptr){ //checks if sound exists
            SoundPtr->Play(1);
        }
    }
}

void Face::Update(float dt){

    InputManager& inputManager = InputManager::GetInstance();

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON))
        if(associated.box.Contains(inputManager.GetMouseX() + Camera::pos.x, inputManager.GetMouseY() + Camera::pos.y))
            Damage(std::rand() % 10 + 10);
}

void Face::Render(){

    //does nothing
}

bool Face::Is(string type){

    return (type.compare("Face") == 0 ? true : false);
}