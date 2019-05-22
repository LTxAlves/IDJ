#include "StageState.h"
#include "Sprite.h"
#include "Alien.h"
#include "Sound.h"
#include "GameObject.h"
#include "Vec2.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.h"

GameObject* go_background	= (new GameObject()); //Game Object required for background Sprite
GameObject* go_tiles		= (new GameObject()); //Game Object required for TileMap & TileSets
GameObject* go_alien		= (new GameObject()); //Game Object required for Alien
GameObject* go_penguin		= (new GameObject()); //Game Object required for Penguin

StageState::StageState() :	backgroundMusic(MUSICFILE){

	tileSet = nullptr;
    quitRequested = false; //initializes quit request variable
	started = false; //initializes started variable
    backgroundMusic.Play(-1); //plays music
}

StageState::~StageState(){

    objectArray.clear();
	
	delete go_penguin;
	delete go_alien;
	delete go_tiles;
	delete go_background;
}

void StageState::LoadAssets(){

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

void StageState::Update(float dt){

	InputManager& inputManager = InputManager::GetInstance(); //gets only instance of input manager

	Camera::Update(dt); //updates camera to new frame

	if(inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY)) //checks if player quit game
		quitRequested = true;

	for(unsigned int i = 0; i < objectArray.size(); i++){ //deletes dead object and plays their death sound
        if(objectArray[i]->IsDead()){
			Sound* soundPtr = static_cast<Sound*> (objectArray[i]->GetComponent("Sound"));
			if(soundPtr != nullptr)
				soundPtr->Play(1);
            objectArray.erase(objectArray.begin() + i);
        }
    }

    for(unsigned int i = 0; i < objectArray.size(); i++){ //updates each object
        objectArray[i]->Update(dt);
	}

	for(unsigned int i = 0; i < objectArray.size(); i++){ //updates each collider
		Collider* colliderPtr = static_cast<Collider*> (objectArray[i]->GetComponent("Collider"));
		if(colliderPtr != nullptr)
        	colliderPtr->Update(dt);
	}

	for(unsigned int i = 0; i <objectArray.size(); i++){
		Collider* iColliderPtr = static_cast<Collider*> (objectArray[i]->GetComponent("Collider"));
		if(iColliderPtr != nullptr){
			for(unsigned int j = (i + 1); j < objectArray.size(); j++){
				Collider* jColliderPtr = static_cast<Collider*> (objectArray[j]->GetComponent("Collider"));
				if(jColliderPtr != nullptr && Collision::IsColliding(iColliderPtr->box, jColliderPtr->box, objectArray[i]->angleDeg * DEGTORAD, objectArray[i]->angleDeg * DEGTORAD)){
					objectArray[i]->NotifyCollision(*(objectArray[j]));
					objectArray[j]->NotifyCollision(*(objectArray[i]));
				}
			}
		}
	}
}

void StageState::Render(){

	TileMap* tileMap;

    for(unsigned int i = 0; i < objectArray.size(); i++){ //renders each object
        objectArray[i]->Render();
		if(objectArray[i]->GetComponent("TileMap") != nullptr)
			tileMap = static_cast<TileMap*> (objectArray[i]->GetComponent("TileMap"));
    }

	if(tileMap != nullptr)
		for(int i = 1; i < tileMap->GetDepth(); i++)
        	tileMap->RenderLayer(i, Camera::pos.x * (1 + i * PARALLAX_FACTOR), Camera::pos.y * (1 + i * PARALLAX_FACTOR));
}

void StageState::Start(){ //Starts stage

	LoadAssets();

	for(unsigned int i = 0; i < objectArray.size(); i++){ //starts each object
        objectArray[i]->Start();
    }

	started = true;
}

void StageState::Pause(){

}

void StageState::Resume(){


}