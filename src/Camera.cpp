#include "Camera.h"

GameObject* Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed;

void Camera::Follow(GameObject* newFocus){

    focus = newFocus;
}

void Camera::Unfollow(){

    focus = nullptr;
}

void Camera::Update(float dt){

    InputManager& inputManager = InputManager::GetInstance(); //gets only instance of input manager

    if(focus != nullptr){ //checks existence of focus
        pos.x = focus->box.x + focus->box.w/2 - SCREEN_WIDTH/2;
        pos.y = focus->box.y + focus->box.h/2 - SCREEN_HEIGHT/2;
    }
    else{ //moves according to key press, no focus
        if(inputManager.IsKeyDown(LEFT_ARROW_KEY))
            speed.x = CAMERA_SPEED;
        else if(inputManager.IsKeyDown(RIGHT_ARROW_KEY))
            speed.x = -CAMERA_SPEED;
        else
            speed.x = 0;

        if(inputManager.IsKeyDown(UP_ARROW_KEY))
            speed.y = CAMERA_SPEED;
        else if(inputManager.IsKeyDown(DOWN_ARROW_KEY))
            speed.y = -CAMERA_SPEED;
        else
            speed.y = 0;

        pos.x += speed.x*dt;
        pos.y += speed.y*dt;
    }
}