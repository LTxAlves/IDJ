#pragma once

#include <vector>
#include <memory>

using std::vector;
using std::weak_ptr;
using std::shared_ptr;

class GameObject;

class State{
    public:
        State();
        virtual ~State();

        virtual void LoadAssets();
        virtual void Update(float) = 0;
        virtual void Render() = 0;

        virtual void Start() = 0;
        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual weak_ptr<GameObject> AddObject(GameObject*);
        virtual weak_ptr<GameObject> GetObjectPtr(GameObject*);

        bool PopRequested();
        bool QuitRequested();

    protected:
        void StartArray();
        virtual void UpdateArray(float);
        virtual void RenderArray();

        bool popRequested;
        bool quitRequested;
        bool started;

        vector<shared_ptr<GameObject>> objectArray;
};