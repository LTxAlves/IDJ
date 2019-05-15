#pragma once

#include <memory>
#include "Constants.h"
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"

using std::string;
using std::weak_ptr;
using std::vector;

class GameObject;
class Sprite;
class Minion;

class Alien : public Component{

    public:
        Alien(GameObject&, int);
        ~Alien();

        void Start();
        void Update(float);
        void Render();
        bool Is(string);

        void NotifyCollision(GameObject&);

        static int alienCount;

    private:
        Vec2 speed;
        int hp;
        int nMinions;

        vector<weak_ptr<GameObject>> minionArray;

        enum AlienState {MOVING, RESTING};

        AlienState state;
        Timer restTimer;
        
        Vec2 destination;
};