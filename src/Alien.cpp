#include "Alien.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Minion.h"
#include "Game.h"
#include "Camera.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated){

    Sprite* alien = (new Sprite(associated, ALIENFILE)); //loads alien sprite
    associated.AddComponent(alien); //adds it to game object

    hp = (rand() % 11) + 30; //random number of hitpoints between 30 and 40
    speed = Vec2(); //initially no speed

    this->nMinions = nMinions; //saves number of minions
}

Alien::~Alien(){

    minionArray.clear(); //clears minion array
}

Alien::Action::Action(Action::ActionType type, float x, float y){

    this->type = type; //sets type of action
    pos = Vec2(x, y); //sets coordinates
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

    InputManager& inputManager = InputManager::GetInstance(); //gets only instance of input manager

    associated.angleDeg += (ALIENANGVEL * 180/PI) * dt; //rotates alien

    if(associated.angleDeg >= 359.6 && associated.angleDeg <= 360.5) //keep rotation in [0°, 360°)
        associated.angleDeg = 0;

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)) //left mouse click shoots
        taskQueue.emplace(Action(Action::SHOOT, inputManager.GetMouseX() - Camera::pos.x, inputManager.GetMouseY() - Camera::pos.y)); //shoot with left click

    if(inputManager.MousePress(RIGHT_MOUSE_BUTTON)) //right mouse click moves
        taskQueue.emplace(Action(Action::MOVE, inputManager.GetMouseX() - Camera::pos.x - (associated.box.w/2), inputManager.GetMouseY() - Camera::pos.y - (associated.box.h/2))); //move (center) with right click

    if(!taskQueue.empty()){ //checks if there's any action in queue
        if((taskQueue.front()).type == Action::MOVE){ //if action is to move

            Vec2 dir = taskQueue.front().pos - associated.box.Position(); //direction of movement vector 
            speed = dir.Normalized() * ALIENSPEED; //speed vector (keeps magnitude constant)

            if( (dir.x > -(dt * abs(speed.x))) && (dir.x < (dt * abs(speed.x))) &&
                (dir.y > -(dt * abs(speed.y))) && (dir.y < (dt * abs(speed.y)))){ //checks bounds (if close enough to detination)

                    speed = Vec2(); //stop moving
                    taskQueue.pop(); //remove action from queue
            }
            else
                associated.box += speed * dt; //new position
        }
        else if((taskQueue.front()).type == Action::SHOOT){ //if action is to shoot

            float smallestDist = FLT_MAX; //smallest distance found
            int closestMinion; //which minion is closest to target

            for(unsigned int i = 0; i < minionArray.size(); i++){ //goes thorugh minion array

                Vec2 minionPos = minionArray[i].lock()->box.CenterPoint(); //gets minion center position
                
                if(minionPos.Distance(taskQueue.front().pos) < smallestDist){ //if smallerthan smallest distance found so far

                    smallestDist = minionPos.Distance(taskQueue.front().pos); //update smallest distance found
                    closestMinion = i; //saves minion position in array
                }
            }

            if(minionArray[closestMinion].lock() != nullptr){ //checks for reference error (dead minion)

                Minion* minon = static_cast<Minion*> (minionArray[closestMinion].lock()->GetComponent("Minion")); //get minion reference
                minon->Shoot(taskQueue.front().pos); //minion shoots
            }
            
            taskQueue.pop(); //remove action from queue
        }
    }

    if(hp <= 0){ //checks death
    
        hp = 0; //set hp to 0 to avoid showing negative values
        associated.RequestDelete();
    }
}

void Alien::Render(){

    //does nothing
}

bool Alien::Is(string type){

    return !type.compare("Alien");
}