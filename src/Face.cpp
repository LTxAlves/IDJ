#include "Face.h"
#include "Sound.h"

Face::Face(GameObject& associated) : Component(associated){

    hitpoints = 30;
}

void Face::Damage(int damage){

    Sound* SoundPtr;

    hitpoints -= damage;

    if(hitpoints <= 0){
        hitpoints = 0;
        associated_obj.RequestDelete();
        SoundPtr = (Sound*) associated_obj.GetComponent("Sound");
        if(SoundPtr != nullptr){
            //PLAY SOUND
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