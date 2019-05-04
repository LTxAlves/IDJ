#pragma once

#include <queue>
#include <memory>
#include "Component.h"
#include "Sprite.h"

#define ALIENFILE "assets/img/alien.png"
#define MINIONFILE "assets/img/minion.png"
#define ALIENSPEED 150

using std::queue;
using std::weak_ptr;

class Alien : public Component{

    public:
        Alien(GameObject&, int);
        ~Alien();

        void Start();
        void Update(float);
        void Render();
        bool Is(string);

    private:
        class Action{

            public:
                enum ActionType {MOVE, SHOOT};

                ActionType type;
                Vec2 pos;

                Action(ActionType, float, float);
        };

        Vec2 speed;
        int hp;
        int nMinions;

        queue<Action> taskQueue;
        vector<weak_ptr<GameObject>> minionArray;

};