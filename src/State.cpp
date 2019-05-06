#include "State.h"
#include "Game.h"
#include "Sprite.h"
#include "Alien.h"
#include "Sound.h"
#include "GameObject.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"

GameObject* go_background = (new GameObject()); //Game Object required for background Sprite
GameObject* go_tiles = (new GameObject()); //Game Object required for TileMap & TileSets
GameObject* go_alien = (new GameObject()); //Game Object required for Alien

State::State() : music(MUSICFILE){

	weak_ptr<GameObject> weak_go = AddObject(go_background);
	shared_ptr<GameObject> shared_go = weak_go.lock();

	shared_go->box.x = 0; //sets x coordinate to 0
	shared_go->box.y = 0; //sets y coordinate to 0

	Sprite* bg = new Sprite(*shared_go, BGIMAGEFILE); //assigns image to background

	shared_go->AddComponent(bg); //adds background

	CameraFollower* camFollow = new CameraFollower(*shared_go);

	shared_go->AddComponent(camFollow); //makes background follow camera (not move)

    weak_go = AddObject(go_tiles); 
	shared_go = weak_go.lock();
	
	TileSet* ts = new TileSet(TILEWIDTH, TILEHEIGHT, TILESETFILE); //assigns tileset
    TileMap* tm = new TileMap(*shared_go, TILEMAPFILE, ts); //assigns tilemap

	shared_go->box.w = 0; //sets width to 0
	shared_go->box.h = 0; //sets height to 0

	shared_go->AddComponent(tm);

	weak_go = AddObject(go_alien);
	shared_go = weak_go.lock();

	Alien* alien = new Alien(*shared_go, NMINIONSSTD); //assigns alien

	shared_go->box.x = 512 - go_alien->box.w/2; //places Alien center in x = 512
	shared_go->box.y = 300 - go_alien->box.h/2; //places Alien center in y = 300

	shared_go->AddComponent(alien);

    quitRequested = false; //initializes quit request variable
	started = false; //initializes started variable
    music.Play(-1); //plays music
}

State::~State(){

    objectArray.clear();
	
	delete go_alien;
	delete go_tiles;
	delete go_background;
}

void State::LoadAssets(){

	//does nothing
}

void State::Update(float dt){

	InputManager& inputManager = InputManager::GetInstance(); //gets only instance of input manager

	Camera::Update(dt); //updates camera to new frame

	if(inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY)) //checks if player quit game
		quitRequested = true;

    for(unsigned int i = 0; i < objectArray.size(); i++){ //updates each object
        objectArray[i]->Update(dt);
	}

	for(unsigned int i = 0; i < objectArray.size(); i++){ //deletes dead object and plays their death sound
        if(objectArray[i]->IsDead()){
			Sound* soundPtr = static_cast<Sound*> (objectArray[i]->GetComponent("Sound"));
			if(soundPtr != nullptr)
				soundPtr->Play(1);
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render(){

    for(unsigned int i = 0; i < objectArray.size(); i++){ //renders each object
        objectArray[i]->Render();
    }
}

bool State::QuitRequested(){

    return quitRequested;
}

weak_ptr<GameObject> State::AddObject(GameObject* go){

	shared_ptr<GameObject> shared_go(go);

	objectArray.emplace_back(shared_go);

	if(started)
		objectArray.back()->Start();

	weak_ptr<GameObject> weak_go = weak_ptr<GameObject> (objectArray.back());

	return weak_go;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){

	weak_ptr<GameObject> weak_go;

	for(auto it = objectArray.begin(); it != objectArray.end(); it++){
		if((*it).get() == go)
			weak_go = weak_ptr<GameObject> (*it);
	}
	
	return weak_go;
}

void State::Start(){

	LoadAssets();

	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Start();
	}

	started = true;
}