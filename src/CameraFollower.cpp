#include "CameraFollower.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go){

    //does nothing
}

void CameraFollower::Update(float dt){

    associated.box.x = -Camera::pos.x; //same coordinates
    associated.box.y = -Camera::pos.y; //same coordinates
}

void CameraFollower::Render(){

    //does nothing
}

bool CameraFollower::Is(string type){

    return type.compare("CameraFollower") == 0 ? true : false;
}