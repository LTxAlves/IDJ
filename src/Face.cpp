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
        associated_obj.Play();
    }
}