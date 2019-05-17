#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"
#include "Collider.h"
#include "Sound.h"

Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) :  Component(associated),
                                                                                                alienCenter(alienCenter){

    Sprite* minion = (new Sprite(associated, MINIONFILE)); //creates new sprite for minion
    
    float scale = (float(rand())/(float(RAND_MAX)/0.5)) + 1.0; //generates scale factor within [1, 1.5)
    minion->SetScaleX(scale, scale); //sets scale factor accordingly

    hp = 20 * scale + 10; //bigger minions have more life
    
    associated.AddComponent(minion); //adds minion sprite

    Collider* minionCollider = (new Collider(associated, {scale, scale})); //creates minion collider
    associated.AddComponent(minionCollider); //adds minion collider

    arc = arcOffsetDeg * (DEGTORAD); //degrees to radians

    shared_ptr<GameObject> alien = alienCenter.lock(); //makes shared_ptr from weak_ptr
    Vec2 dist(200, 0); //radius around alien
    
    if(alien != nullptr){ //checks if alien exists (isn't dead)
        dist.Rotate(-arc); //rotates minion around

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
        dist.Rotate(-arc); //rotates minion around

        associated.angleDeg = -arc * (RADTODEG); //rotates to keep bottom pointing at alien

        dist += alien->box.CenterPoint(); //sets distance to move
        dist.x -= associated.box.w/2; //corrects to move center
        dist.y -= associated.box.h/2; //corrects to move center

        associated.box.x = dist.x; //moves said distance in x axis
        associated.box.y = dist.y; //moves said distance in y axis

        arc += MINIONANGVEL * dt; //updates arc to move in next frame
    }
    else
        associated.RequestDelete();

    if(hp <= 0){
        hp = 0;
        associated.RequestDelete();

        GameObject* go = (new GameObject());
        weak_ptr<GameObject> weak_go = Game::GetInstance().GetState().AddObject(go);
        shared_ptr<GameObject> shared_go = weak_go.lock();

        Sprite* pdeath = new Sprite(*shared_go, MINIONDEATHFILE, ENEMYDEATHFRAMES, DEATHFRAMETIME, ENEMYDEATHFRAMES * DEATHFRAMETIME);
        Sound* boom = new Sound(*shared_go, BOOMAUDIOFILE);

        shared_go->box = associated.box;
        shared_go->AddComponent(pdeath);
        shared_go->AddComponent(boom);

        boom->Play(1);
    }
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

    Bullet* shot = (new Bullet(*shared_go, dir.Inclination(), BULLETSPEED, damage, BULLETMAXDIST, MINIONBULLET2FILE, MINIONBULLETFRAMES, MINIONBULLETFRAMETIME, true)); //creates bullet component

    shared_go->box.CenterAt(associated.box.CenterPoint()); //sets box starting point

    shared_go->AddComponent(shot); //adds bullet compoonent
}

void Minion::NotifyCollision(GameObject& other){

    Bullet* bullet = static_cast<Bullet*> (other.GetComponent("Bullet"));

    if(bullet != nullptr && !bullet->targetsPlayer)
        hp -= bullet->GetDamage();
}