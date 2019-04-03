#include "Face.h"
#include "Sound.h"

Face::Face(GameObject& associated) : Component(associated){

    hitpoints = 30;
}

void Face::Damage(int damage){

    hitpoints -= damage;

    if(hitpoints <= 0){
        hitpoints = 0;
        associated_obj.RequestDelete();
        if(associated_obj.GetComponent("Sound") != nullptr){
            associated_obj.Play();
        }
    }
}

bool Face::Is(string type){

    return (type.compare("Face") == 0 ? true : false);
}