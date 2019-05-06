#include "Camera.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Game.h"

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
        pos = focus->box.CenterPoint(); //positions on center of focus
        pos.x -= SCREEN_WIDTH/2; //corrects for screen size
        pos.y -= SCREEN_HEIGHT/2; //corrects forscreen size
    }
    else{ //moves according to key press, no focus
        if(inputManager.IsKeyDown(LEFT_ARROW_KEY) && inputManager.IsKeyDown(RIGHT_ARROW_KEY))
            speed.x = 0;
        else if(inputManager.IsKeyDown(LEFT_ARROW_KEY))
            speed.x = CAMERA_SPEED;
        else if(inputManager.IsKeyDown(RIGHT_ARROW_KEY))
            speed.x = -CAMERA_SPEED;
        else
            speed.x = 0;

        if(inputManager.IsKeyDown(UP_ARROW_KEY) && inputManager.IsKeyDown(DOWN_ARROW_KEY))
            speed.y = 0;
        else if(inputManager.IsKeyDown(UP_ARROW_KEY))
            speed.y = CAMERA_SPEED;
        else if(inputManager.IsKeyDown(DOWN_ARROW_KEY))
            speed.y = -CAMERA_SPEED;
        else
            speed.y = 0;

        pos += speed * dt;
    }
}