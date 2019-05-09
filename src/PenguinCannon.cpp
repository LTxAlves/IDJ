#include "PenguinCannon.h"
#include "Constants.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Bullet.h"

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody) :    Component(associated),
                                                                                            pbody(penguinBody),
                                                                                            angle(0){

    Sprite* gunner = new Sprite(associated, PENGUINCANNONFILE);
    associated.AddComponent(gunner);
}

void PenguinCannon::Update(float  dt){

    shared_ptr<GameObject> body = pbody.lock();

    if(body == nullptr){
        associated.RequestDelete();
        return;
    }

    associated.box.CenterAt(body->box.CenterPoint());

    InputManager& inputManager = InputManager::GetInstance();
    
    Vec2 dir(inputManager.GetMouseX() + Camera::pos.x, inputManager.GetMouseY() + Camera::pos.y);
    dir -= associated.box.CenterPoint();

    angle = dir.Inclination();
    associated.angleDeg = angle;

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON))
        Shoot();
}

void PenguinCannon::Render(){

    //does nothing
}

bool PenguinCannon::Is(string type){

    return !type.compare("PenguinCannon");
}

void PenguinCannon::Shoot(){

    GameObject* go = (new GameObject());
    weak_ptr<GameObject> weak_go = Game::GetInstance().GetState().AddObject(go);
    shared_ptr<GameObject> shared_go = weak_go.lock();

    int damage = rand()%6 + 10;

    Bullet* bullet = new Bullet(*shared_go, angle, BULLETSPEED, damage, BULLETMAXDIST, PENGUINBULLETFILE, PENGUINBULLETFRAMES, PENGUINBULLETFRAMETIME);

    Vec2 startOffset(associated.box.w/2.0, 0);
    startOffset.Rotate(-angle * DEGTORAD);
    shared_go->box.CenterAt(associated.box.CenterPoint() + startOffset);

    shared_go->AddComponent(bullet);
}