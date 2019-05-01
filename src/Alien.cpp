#include "Alien.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated){

    auto alien = (new Sprite(associated, ALIENFILE));
    associated.AddComponent(alien);

    hp = 30;
    speed.x = 0;
    speed.y = 0;
}

Alien::~Alien(){

    minionArray.clear();
}

void Alien::Start(){


}

void Alien::Update(float){


}

void Alien::Render(){


}

bool Alien::Is(string){

    
}