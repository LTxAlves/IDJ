#pragma once

#include "Component.h"

using std::string;
using std::weak_ptr;

const string MINIONFILE = "assets/img/minion.png"; //minion image file
const string MINIONBULLET1FILE = "assets/img/minionbullet1.png"; //minion bullet 1 file
const string MINIONBULLET2FILE = "assets/img/minionbullet2.png"; //minion bullet 2 file
const float MINIONANGVEL = 15.0 * PI/180; //default angular velocity for minion
const float BULLETSPEED = 500; //default speed for bullet
const float BULLETMAXDIST = 500; //default distance bullet can move  

class Sprite;
class Bullet;

class Minion : public Component{

    public:
        Minion(GameObject&, weak_ptr<GameObject>, float = 0);
        
        void Update(float);
        void Render();
        bool Is(string);
        void Shoot(Vec2);

    private:
        weak_ptr<GameObject> alienCenter;
        float arc;
};

#include "Sprite.h"
#include "Bullet.h"