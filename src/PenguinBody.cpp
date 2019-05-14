#include "PenguinBody.h"
#include "Constants.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sound.h"
#include "Collider.h"
#include "Bullet.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) :  Component(associated),
                                                    speed(0, 0),
                                                    linearSpeed(0),
                                                    angle(0){

    hp = (rand() % 11) + 20;
    
    player = this;

    Sprite* peng = new Sprite(associated, PENGUINBODYFILE); //creates sprite for penguin body
    associated.AddComponent(peng); //adds sprtie to Game Object

    Collider* penguinCollider = (new Collider(associated)); //creates collider for penguin
    associated.AddComponent(penguinCollider); //adds collder to Game Object
}

PenguinBody::~PenguinBody(){

    player = nullptr;
}

void PenguinBody::Start(){

    GameObject* go = (new GameObject());
    pcannon = Game::GetInstance().GetState().AddObject(go);
    shared_ptr<GameObject> shared_go = pcannon.lock();

    PenguinCannon* cannon = new PenguinCannon(*shared_go, Game::GetInstance().GetState().GetObjectPtr(&associated));
    
    shared_go->box.x = associated.box.x;
    shared_go->box.y = associated.box.y;
    
    shared_go->AddComponent(cannon);
}

void PenguinBody::Update(float dt){

    InputManager& inputManager = InputManager::GetInstance();

    if((inputManager.IsKeyDown(W_KEY) && !inputManager.IsKeyDown(S_KEY)) || (inputManager.IsControllerDown(DPAD_UP) && !inputManager.IsControllerDown(DPAD_DOWN)))
        linearSpeed = (linearSpeed + PLAYERACCEL*dt <= PLAYERSPEEDCAP) ? linearSpeed + PLAYERACCEL*dt : PLAYERSPEEDCAP;
    if((inputManager.IsKeyDown(S_KEY) && !inputManager.IsKeyDown(W_KEY)) || (inputManager.IsControllerDown(DPAD_DOWN) && !inputManager.IsControllerDown(DPAD_UP)))
        linearSpeed = (linearSpeed - PLAYERACCEL*dt >= -PLAYERSPEEDCAP) ? linearSpeed - PLAYERACCEL*dt : - PLAYERSPEEDCAP;
    if((!inputManager.IsKeyDown(W_KEY) && !inputManager.IsKeyDown(S_KEY)) && (!inputManager.IsControllerDown(DPAD_DOWN) && !inputManager.IsControllerDown(DPAD_UP))){
        if(linearSpeed > 0)
            linearSpeed = (linearSpeed - PLAYERACCEL*dt >= 0) ? linearSpeed - PLAYERACCEL*dt : 0;
        else
            linearSpeed = (linearSpeed + PLAYERACCEL*dt <= 0) ? linearSpeed + PLAYERACCEL*dt : 0;
    }

    if((inputManager.IsKeyDown(A_KEY) && !inputManager.IsKeyDown(S_KEY)) || (inputManager.IsControllerDown(DPAD_LEFT) && !inputManager.IsControllerDown(DPAD_RIGHT)))
        angle -= PLAYERANGVEL*dt;
    if((inputManager.IsKeyDown(D_KEY) && !inputManager.IsKeyDown(A_KEY)) || (inputManager.IsControllerDown(DPAD_RIGHT) && !inputManager.IsControllerDown(DPAD_LEFT)))
        angle += PLAYERANGVEL*dt;

    if((angle >= 359*DEGTORAD) || (-angle >= 359*DEGTORAD))
        angle = 0;

    speed = Vec2(linearSpeed, 0);
    speed.Rotate(-angle);

    associated.box += speed*dt;
    associated.angleDeg = angle * RADTODEG;

    if(hp <= 0){
        hp = 0;
        associated.RequestDelete();

        shared_ptr<GameObject> shared_cannon = pcannon.lock();
        
        if(shared_cannon != nullptr)
            shared_cannon->RequestDelete();

        Camera::Unfollow();

        GameObject* go = (new GameObject());
        weak_ptr<GameObject> weak_go = Game::GetInstance().GetState().AddObject(go);
        shared_ptr<GameObject> shared_go = weak_go.lock();

        Sprite* pdeath = new Sprite(*shared_go, PENGUINDEATHFILE, PENGUINDEATHFRAMES, DEATHFRAMETIME);
        Sound* boom = new Sound(*shared_go, BOOMAUDIOFILE);

        shared_go->box = associated.box;
        shared_go->AddComponent(pdeath);
        shared_go->AddComponent(boom);

        boom->Play(1);
    }
}

void PenguinBody::Render(){

    //does nothing
}

bool PenguinBody::Is(string type){

    return !type.compare("PenguinBody");
}

void PenguinBody::NotifyCollision(GameObject& other){

    Bullet* bullet = static_cast<Bullet*>(other.GetComponent("Bullet"));

    if(bullet != nullptr && bullet->targetsPlayer){
        hp -= bullet->GetDamage();
    }
}