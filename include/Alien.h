#ifndef ALIEN_H
#define ALIEN_H

#include <queue>
#include <memory>
#include "Component.h"
#include "Sprite.h"

#define ALIENFILE "assets/img/alien.png"
#define MINIONFILE "assets/img/minion.png"

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
        class Action;

        Vec2 speed;
        int hp;

        queue<Action> taskQueue;
        vector<weak_ptr<GameObject>> minionArray;

};

class Action{

    public:
        enum ActionType {MOVE, SHOOT};

        Action(ActionType, float, float);

        ActionType type;
        Vec2 pos;
};

#endif //ALIEN_H