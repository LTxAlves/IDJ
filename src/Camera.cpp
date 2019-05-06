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
        pos.y -= SCREEN_HEIGHT/2; //corrects for screen size
    }
    else{ //moves according to key press, no focus
        if(inputManager.IsKeyDown(LEFT_ARROW_KEY) && inputManager.IsKeyDown(RIGHT_ARROW_KEY)) //heys cancel each other
            speed.x = 0;
        else if(inputManager.IsKeyDown(LEFT_ARROW_KEY)) //move left
            speed.x = CAMERA_SPEED;
        else if(inputManager.IsKeyDown(RIGHT_ARROW_KEY)) //move right
            speed.x = -CAMERA_SPEED;
        else //don't move in x axis
            speed.x = 0;

        if(inputManager.IsKeyDown(UP_ARROW_KEY) && inputManager.IsKeyDown(DOWN_ARROW_KEY)) //keys cancel each other
            speed.y = 0;
        else if(inputManager.IsKeyDown(UP_ARROW_KEY)) //move up
            speed.y = CAMERA_SPEED;
        else if(inputManager.IsKeyDown(DOWN_ARROW_KEY)) //move down
            speed.y = -CAMERA_SPEED;
        else //don't move in y axis
            speed.y = 0;

        pos += speed * dt;
    }
}