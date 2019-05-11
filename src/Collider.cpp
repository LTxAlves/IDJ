#include "Collider.h"
#include "GameObject.h"
#include "Constants.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) :   Component(associated),
                                                                        scale(scale),
                                                                        offset(offset){


}

void Collider::Update(float){

    box = associated.box * scale;
    box.CenterAt(associated.box.CenterPoint() + offset.GetRotated(associated.angleDeg * DEGTORAD));
}

void Collider::Render(){

    //does nothing
}

bool Collider::Is(string type){

    return !type.compare("Collider");
}

void Collider::SetScale(Vec2 scale){

    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset){

    this->offset = offset;
}