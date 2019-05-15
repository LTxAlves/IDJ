#include "Alien.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Minion.h"
#include "Game.h"
#include "Camera.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"
#include "PenguinBody.h"

int Alien::alienCount;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated){

    Sprite* alien = (new Sprite(associated, ALIENFILE)); //loads alien sprite
    Collider* alienCollider = (new Collider(associated)); //creates colider for alien
    associated.AddComponent(alien); //adds sprite to game object
    associated.AddComponent(alienCollider); //adds collider to game object

    hp = (rand() % 11) + 50; //random number of hitpoints between 30 and 40
    speed = Vec2(); //initially no speed

    this->nMinions = nMinions; //saves number of minions

    alienCount++;

    state = RESTING;
}

Alien::~Alien(){

    minionArray.clear(); //clears minion array
}

void Alien::Start(){

    for(int i = 0; i < nMinions; i++){ //adds nMinions minions to array
        GameObject* go = (new GameObject());

        weak_ptr<GameObject> weak_go = Game::GetInstance().GetState().AddObject(go); //adds object
        minionArray.emplace_back(weak_go); //adds to minion array
        shared_ptr<GameObject> shared_go = weak_go.lock(); //makes shared

        weak_go = Game::GetInstance().GetState().GetObjectPtr(&associated); //gets reference to associated object
        Minion* minion = (new Minion(*shared_go, weak_go, (360.0/nMinions)*i)); //creates minion
        
        shared_go->box.x = 0; //sets initial x coordinate
        shared_go->box.y = 0; //sets initial y coordinate
        shared_go->AddComponent(minion); //adds component minions
    }
}

void Alien::Update(float dt){

    associated.angleDeg += (ALIENANGVEL * RADTODEG) * dt; //rotates alien

    if(associated.angleDeg >= 359.6 && associated.angleDeg <= 360.5) //keep rotation in [0°, 360°)
        associated.angleDeg = 0;

    switch (state)
    {
    case RESTING:
        /* code */
        break;
    
    case MOVING:
        break;
    }
    if(state == RESTING){

        restTimer.Update(dt);
        if(restTimer.Get() > ALIENRESTCOOLDOWN)
            state = MOVING;
    }
    else if(state == MOVING){

        if(destination == Vec2(0,0) && PenguinBody::player != nullptr)
            destination = PenguinBody::player->Position();
            
        Vec2 dir = destination - associated.box.CenterPoint();
        speed = dir.Normalized() * ALIENSPEED; //speed vector (keeps magnitude constant)

        if( (dir.x > -(dt * abs(speed.x))) && (dir.x < (dt * abs(speed.x))) &&
            (dir.y > -(dt * abs(speed.y))) && (dir.y < (dt * abs(speed.y)))){ //checks bounds (if close enough to detination)

                speed = {0, 0}; //stop moving
                float smallestDist = FLT_MAX; //smallest distance found

                int closestMinion; //which minion is closest to target

                for(unsigned int i = 0; i < minionArray.size(); i++){ //goes thorugh minion array

                    Vec2 minionPos = minionArray[i].lock()->box.CenterPoint(); //gets minion center position
                    
                    if(minionPos.Distance(destination) < smallestDist){ //if smallerthan smallest distance found so far

                        smallestDist = minionPos.Distance(destination); //update smallest distance found
                        closestMinion = i; //saves minion position in array
                    }
                }

                if(minionArray[closestMinion].lock() != nullptr && PenguinBody::player != nullptr){ //checks for reference error (dead minion)

                    Minion* minon = static_cast<Minion*> (minionArray[closestMinion].lock()->GetComponent("Minion")); //get minion reference
                    minon->Shoot(PenguinBody::player->Position()); //minion shoots
                }

                restTimer.Restart();
                destination = {0, 0};
                state = RESTING;
        }
        else
            associated.box += speed * dt; //new position
    }

    if(hp <= 0){ //checks death
    
        hp = 0; //set hp to 0 to avoid showing negative values
        associated.RequestDelete();

        GameObject* go = (new GameObject());
        weak_ptr<GameObject> weak_go = Game::GetInstance().GetState().AddObject(go);
        shared_ptr<GameObject> shared_go = weak_go.lock();

        Sprite* pdeath = new Sprite(*shared_go, ALIENDEATHFILE, ENEMYDEATHFRAMES, DEATHFRAMETIME, ENEMYDEATHFRAMES * DEATHFRAMETIME);
        Sound* boom = new Sound(*shared_go, BOOMAUDIOFILE);

        shared_go->box = associated.box;
        shared_go->AddComponent(pdeath);
        shared_go->AddComponent(boom);

        boom->Play(1);
    }
}

void Alien::Render(){

    //does nothing
}

bool Alien::Is(string type){

    return !type.compare("Alien");
}

void Alien::NotifyCollision(GameObject& other){

    Bullet* bullet = static_cast<Bullet*> (other.GetComponent("Bullet"));

    if(bullet != nullptr && !bullet->targetsPlayer)
        hp -= bullet->GetDamage();
}