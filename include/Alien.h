#pragma once

#include <queue>
#include <memory>
#include "Constants.h"
#include "Component.h"
#include "Vec2.h"

using std::string;
using std::queue;
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