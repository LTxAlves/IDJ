#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"

Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) :  Component(associated),
                                                                                                alienCenter(alienCenter){

    Sprite* minion = (new Sprite(associated, MINIONFILE)); //crestes new sprite for minion
    
    float scale = (float(rand())/(float(RAND_MAX)/0.5)) + 1.0; //generates scale factor within [1, 1.5)
    minion->SetScaleX(scale, scale); //sets scale factor accordingly
    
    associated.AddComponent(minion); //adds component

    arc = arcOffsetDeg * (PI / 180); //degrees to radians

    this->alienCenter = alienCenter; //sets alien for minion to circle around

    shared_ptr<GameObject> alien = alienCenter.lock(); //makes shared_ptr from weak_ptr
    Vec2 dist(200, 0); //radius around alien
    
    if(alien != nullptr){ //checks if alien exists (isn't dead)
        dist.Rotate(arc); //rotates minion around

        dist += alien->box.CenterPoint(); //sets distance to move
        dist.x -= associated.box.w/2; //corrects to move center
        dist.y -= associated.box.h/2; //corrects to move center

        associated.box += dist; //moves said distance
    }
    else
        associated.RequestDelete();
}

void Minion::Update(float dt){

    shared_ptr<GameObject> alien = alienCenter.lock();
    Vec2 dist(200, 0);
    
    if(alien != nullptr){ //checks if alien exists (isn't dead)
        dist.Rotate(arc); //rotates minion around

        associated.angleDeg = -arc * (180/PI); //rotates to keep bottom pointing at alien

        dist += alien->box.CenterPoint(); //sets distance to move
        dist.x -= associated.box.w/2; //corrects to move center
        dist.y -= associated.box.h/2; //corrects to move center

        associated.box.x = dist.x; //moves said distance in x axis
        associated.box.y = dist.y; //moves said distance in y axis

        arc += MINIONANGVEL * dt; //updates arc to move in next frame
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

    GameObject* go_bullet = (new GameObject()); //creates go for bullet
    weak_ptr<GameObject> weak_go = Game::GetInstance().GetState().AddObject(go_bullet); //adds it to state
    shared_ptr<GameObject> shared_go = weak_go.lock(); //gets shared_ptr from weak_ptr

    Vec2 dir = pos - associated.box.CenterPoint(); //sets direction to move

    int damage = (rand()%6) + 5;  //sets random damage between 5 and 10

    Bullet* shot = (new Bullet(*shared_go, dir.Inclination(), BULLETSPEED, damage, BULLETMAXDIST, MINIONBULLET1FILE)); //creates bullet component

    shared_go->box += associated.box.CenterPoint(); //sets box starting point

    shared_go->box.x -= shared_go->box.w/2; //corrects to reference center
    shared_go->box.y -= shared_go->box.h/2; //corrects to reference center

    shared_go->AddComponent(shot); //adds bullet compoonent
}