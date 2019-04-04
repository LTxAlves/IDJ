#include "Face.h"
#include "Sound.h"

Face::Face(GameObject& associated) : Component(associated){

    hitpoints = 30;
}

void Face::Damage(int damage){

    unique_ptr<Component> soundPtr;

    hitpoints -= damage;

    if(hitpoints <= 0){
        hitpoints = 0;
        associated_obj.RequestDelete();
        soundPtr = associated_obj.GetComponent("Sound");
        if(soundPtr != nullptr){
            //((Sound*)soundPtr)->Play(1);
        }
    }
}

void Face::Update(float dt){


}

void Face::Render(){

    
}

bool Face::Is(string type){

    return (type.compare("Face") == 0 ? true : false);
}