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
#include "PenguinBody.h"

GameObject* go_background	= (new GameObject()); //Game Object required for background Sprite
GameObject* go_tiles		= (new GameObject()); //Game Object required for TileMap & TileSets
GameObject* go_alien		= (new GameObject()); //Game Object required for Alien
GameObject* go_penguin		= (new GameObject()); //Game Object required for Penguin

State::State() : music(MUSICFILE){

    quitRequested = false; //initializes quit request variable
	started = false; //initializes started variable
    music.Play(-1); //plays music
}

State::~State(){

    objectArray.clear();
	
	delete go_penguin;
	delete go_alien;
	delete go_tiles;
	delete go_background;
}

void State::LoadAssets(){

	weak_ptr<GameObject> weak_go = AddObject(go_background);
	shared_ptr<GameObject> shared_go = weak_go.lock();

	shared_go->box.CenterAt(0, 0); //sets coordinates to (0, 0)

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

	shared_go->box.CenterAt(512, 300); //places Alien center in (512, 300)

	shared_go->AddComponent(alien);

	weak_go = AddObject(go_penguin);
	shared_go = weak_go.lock();

	shared_go->box.CenterAt(704, 640);
	Camera::Follow(shared_go.get());

	PenguinBody* penguin = (new PenguinBody(*shared_go));

	shared_go->AddComponent(penguin);
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

weak_ptr<GameObject> State::AddObject(GameObject* go){ //Adds object to object array

	shared_ptr<GameObject> shared_go(go); //creates shared_ptr from regular ptr

	objectArray.emplace_back(shared_go); //adds it to array

	if(started)
		objectArray.back()->Start(); //calls functointo start id added after start of others

	weak_ptr<GameObject> weak_go = weak_ptr<GameObject> (objectArray.back()); //gets weak_ptr from array

	return weak_go; //adds it
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){ //Gets weak_ptr from a given GO

	weak_ptr<GameObject> weak_go;

	for(auto it = objectArray.begin(); it != objectArray.end(); it++){ //goes through array
		if((*it).get() == go) //checksif addresses match
			weak_go = weak_ptr<GameObject> (*it); //saves weak_ptr
	}
	
	return weak_go; //returns weak_ptr
}

void State::Start(){ //Starts all objects

	LoadAssets();

	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Start();
	}

	started = true;
}