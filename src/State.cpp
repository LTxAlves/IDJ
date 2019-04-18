#include "State.h"

#define BGIMAGEFILE "assets/img/ocean.jpg"
#define MUSICFILE "assets/audio/stageState.ogg"
#define TILESETFILE "assets/img/tileset.png"
#define TILEMAPFILE "assets/map/tileMap.txt"
#define PENGUINFACEFILE "assets/img/penguinface.png"
#define BOOMAUDIOFILE "assets/audio/boom.wav"
#define TILEWIDTH 64
#define TILEHEIGHT 64
#define PI 3.14159265359 //value of constant pi

using std::move;
using std::shared_ptr;

State::State() : music(MUSICFILE){

    shared_ptr<GameObject> go = shared_ptr<GameObject> (new GameObject()); //GameObject required for Sprite

	Sprite* bg = new Sprite(*go, BGIMAGEFILE);

	go->box.x = 0;
	go->box.y = 0;

	go->AddComponent(bg);

	objectArray.emplace_back(move(go));

	shared_ptr<GameObject> go2 = shared_ptr<GameObject> (new GameObject());

    TileSet* ts = new TileSet(TILEWIDTH, TILEHEIGHT, TILESETFILE);
    TileMap* tm = new TileMap(*go2, TILEMAPFILE, ts);

	go2->box.w = 0;
	go2->box.h = 0;

	go2->AddComponent(tm);

	objectArray.emplace_back(move(go2));

    quitRequested = false;
    music.Play(-1);
}

State::~State(){

    objectArray.clear();
}

void State::LoadAssets(){

}

void State::Update(float dt){

	InputManager& inputManager = InputManager::GetInstance();

	if(inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY))
		quitRequested = true;

	if(inputManager.KeyPress(SPACE_KEY)){
		Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI*(rand() % 1001)/500.0) + Vec2(inputManager.GetMouseX(), inputManager.GetMouseY());
		AddObject((int)objPos.x, (int)objPos.y);
	}

    for(unsigned int i = 0; i < objectArray.size(); i++){ //updates each object
        objectArray[i]->Update(dt);
	}

	for(unsigned int i = 0; i < objectArray.size(); i++){ //deletes dead object and play their sound
        if(objectArray[i]->IsDead()){
			Sound* soundPtr = static_cast<Sound*> (objectArray[i]->GetComponent("Sound"));
			if(soundPtr != nullptr)
				soundPtr->Play(1);
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render(){

    for(unsigned int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

bool State::QuitRequested(){

    return quitRequested;
}

void State::AddObject(int mouseX, int mouseY){ //adds object to givn coordinates

	shared_ptr<GameObject> go = shared_ptr<GameObject> (new GameObject());
	Sprite* enemy = (new Sprite(*go, PENGUINFACEFILE));
	Sound* deathSound = (new Sound(*go, BOOMAUDIOFILE));
	Face* face = (new Face(*go));

	go->box.x = mouseX - enemy->GetWidth()/2;
	go->box.y = mouseY - enemy->GetHeight()/2;

	go->AddComponent(enemy);

	go->AddComponent(deathSound);

	go->AddComponent(face);

	objectArray.emplace_back(move(go));
}
