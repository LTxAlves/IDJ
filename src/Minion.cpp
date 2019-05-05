#include "Minion.h"

Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) :  Component(associated),
                                                                                                    alienCenter(alienCenter){

    Sprite* minion = (new Sprite(associated, MINIONFILE)); //crestes new sprite for minion
    associated.AddComponent(minion); //adds component

    arc = arcOffsetDeg * (PI / 180); //degrees to radians

    this->alienCenter = alienCenter; //sets alien for minion to circle around

    shared_ptr<GameObject> alien = alienCenter.lock(); //makes shared_ptr from weak_ptr
    Vec2 dist(200, 0); //radius around alien
    
    if(alien != nullptr){ //checks if alien exists (isn't dead)
        dist.Rotate(arc); //rotates minion around
        
        dist.x += alien->box.x + (alien->box.w - associated.box.w)/2; //sets distance to move in x direction
        dist.y += alien->box.y + (alien->box.h - associated.box.h)/2; //sets distance to move in y direction

        associated.box += dist;
    }
    else
        associated.RequestDelete();
}

void Minion::Update(float dt){

    shared_ptr<GameObject> alien = alienCenter.lock();
    Vec2 dist(200, 0);
    
    if(alien != nullptr){
        dist.Rotate(arc);
        
        dist.x += alien->box.x + (alien->box.w - associated.box.w)/2;
        dist.y += alien->box.y + (alien->box.h - associated.box.h)/2;

        associated.box += dist;
       
        arc += MINIONANGVEL*dt;
    }
    else
        associated.RequestDelete();
}


void Minion::Render(){

    //does nothing
}

bool Minion::Is(string type){

    return !type.compare("Minion");
}

void Minion::Shoot(Vec2 pos){

    GameObject* go_bullet = (new GameObject());
    weak_ptr<GameObject> weak_go = Game::GetInstance().GetState().AddObject(go_bullet);
    shared_ptr<GameObject> shared_go = weak_go.lock();

    Vec2 dir;

    dir.x = pos.x - (associated.box.x + associated.box.w/2);
    dir.y = pos.y - (associated.box.y + associated.box.h/2);

    int damage = (rand()%6) + 5;

    Bullet* shot = (new Bullet(*shared_go, dir.Inclination(), BULLETSPEED, damage, BULLETMAXDIST, MINIONBULLET1FILE));

    shared_go->box.x = associated.box.x + (associated.box.w - shared_go->box.w)/2;
    shared_go->box.y = associated.box.y + (associated.box.h - shared_go->box.h)/2;

    shared_go->AddComponent(shot);
}