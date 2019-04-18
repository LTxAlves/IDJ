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

    if(focus != nullptr){
        pos.x = focus->box.x + focus->box.w/2 - SCREEN_WIDTH/2;
        pos.y = focus->box.y + focus->box.h/2 - SCREEN_HEIGHT/2;
    }
    else{
        
    }
}