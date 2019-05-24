#include "TitleState.h"
#include "GameObject.h"
#include "Game.h"
#include "Sprite.h"
#include "StageState.h"
#include "InputManager.h"
#include "CameraFollower.h"
#include "Text.h"
#include "Camera.h"
#include <memory>

using std::weak_ptr;
using std::shared_ptr;

TitleState::TitleState(){

    GameObject* go = new GameObject();
    weak_ptr<GameObject> weak_go = AddObject(go);
    shared_ptr<GameObject> shared_go = weak_go.lock();

    Sprite* title = new Sprite(*shared_go, TITLESTATEFILE);
    shared_go->AddComponent(title);

    CameraFollower* camFollow = new CameraFollower(*shared_go);

	shared_go->AddComponent(camFollow);
}


TitleState::~TitleState(){


}


void TitleState::LoadAssets(){

    GameObject* text_go = new GameObject();
    weak_ptr<GameObject> weak_go = AddObject(text_go);
    shared_ptr<GameObject> shared_go = weak_go.lock();

    Text* text = new Text(*shared_go, FONTFILE, FONTSIZE, Text::SOLID, "PRESS \"SPACE\" TO START", TEXTCOLOR, TEXTSHOWINTERVAL);
    
    shared_go->AddComponent(text);

    shared_go->box.CenterAt(SCREEN_WIDTH/2, SCREEN_HEIGHT - 2*FONTSIZE);
}


void TitleState::Update(float dt){
    InputManager& inputManager = InputManager::GetInstance();

    UpdateArray(dt);

    if(inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY))
        quitRequested = true;
    else if(inputManager.KeyPress(SPACE_KEY)){
        StageState* stage = new StageState();
        Game::GetInstance().Push(stage);
    }
}


void TitleState::Render(){

    RenderArray();
}


void TitleState::Start(){

    LoadAssets();

    StartArray();
}


void TitleState::Pause(){


}


void TitleState::Resume(){


}

