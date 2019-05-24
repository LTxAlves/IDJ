#include "EndState.h"
#include "GameData.h"
#include "GameObject.h"
#include "Constants.h"
#include "CameraFollower.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Text.h"
#include "TitleState.h"
#include "Game.h"
#include "Camera.h"

EndState::EndState(){

    GameObject* go = new GameObject();
    weak_ptr<GameObject> weak_go = AddObject(go);
    shared_ptr<GameObject> shared_go = weak_go.lock();
    Sprite* state;

    Vec2 position;

    if(GameData::playerVictory)
        state = new Sprite(*shared_go, WINSTATEFILE);
    else
        state = new Sprite(*shared_go, LOSESTATEFILE);

    shared_go->AddComponent(state);

    CameraFollower* camFollow = new CameraFollower(*shared_go);

	shared_go->AddComponent(camFollow);

    go = new GameObject();
    weak_go = AddObject(go);
    shared_go = weak_go.lock();

    Text* text = new Text(*shared_go, FONTFILE, FONTSIZE, Text::SOLID, "PRESS \"ESC\" TO QUIT\n", TEXTCOLOR, TEXTSHOWINTERVAL);
    
    shared_go->AddComponent(text);

    position = {SCREEN_WIDTH/2, 10};

    shared_go->box.CenterAt(position);

    go = new GameObject();
    weak_go = AddObject(go);
    shared_go = weak_go.lock();

    text = new Text(*shared_go, FONTFILE, FONTSIZE, Text::SOLID, "OR \"SPACE\" TO RESTART", TEXTCOLOR, TEXTSHOWINTERVAL);
    
    shared_go->AddComponent(text);

    position = {SCREEN_WIDTH/2, 10+FONTSIZE};

    shared_go->box.CenterAt(position);
}

EndState::~EndState(){

    objectArray.clear();
}

void EndState::LoadAssets(){


}

void EndState::Update(float dt){

    UpdateArray(dt);

    InputManager& inputManager = InputManager::GetInstance();

    if(inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested()){
        quitRequested = true;
    }
    else if(inputManager.KeyPress(SPACE_KEY)){
        popRequested = true;
		Camera::Unfollow();
		Camera::pos = {0, 0};
        TitleState* title = new TitleState();
        Game::GetInstance().Push(title);
    }
}

void EndState::Render(){

    RenderArray();
}

void EndState::Start(){

    StartArray();
}

void EndState::Pause(){


}

void EndState::Resume(){


}

