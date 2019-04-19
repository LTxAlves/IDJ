#include "State.h"

State::State() : music(MUSICFILE){

    shared_ptr<GameObject> go = shared_ptr<GameObject> (new GameObject()); //GameObject required for Sprite

	Sprite* bg = new Sprite(*go, BGIMAGEFILE); //assigns image to background

	go->box.x = 0; //sets x coordinate to 0
	go->box.y = 0; //sets y coordinate to 0

	go->AddComponent(bg); //adds background

	CameraFollower* camFollow = new CameraFollower(*go);

	go->AddComponent(camFollow); //make background follow camera (not move)

	objectArray.emplace_back(move(go));

	shared_ptr<GameObject> go2 = shared_ptr<GameObject> (new GameObject());

    TileSet* ts = new TileSet(TILEWIDTH, TILEHEIGHT, TILESETFILE);
    TileMap* tm = new TileMap(*go2, TILEMAPFILE, ts);

	go2->box.w = 0;
	go2->box.h = 0;

	go2->AddComponent(tm);

	objectArray.emplace_back(move(go2));

    quitRequested = false; //initializes quit request variable
    music.Play(-1); //plays music
}

State::~State(){

    objectArray.clear();
}

void State::LoadAssets(){

	//does nothing
}

void State::Update(float dt){

	InputManager& inputManager = InputManager::GetInstance(); //gets only instance of input manager

	Camera::Update(dt); //updates camera to new frame

	if(inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY)) //checks if player quit game
		quitRequested = true;

	if(inputManager.KeyPress(SPACE_KEY)){ //checks if space key was pressed (add penguin)
		Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI*(rand() % 1001)/500.0) + Vec2(inputManager.GetMouseX(), inputManager.GetMouseY());
		AddObject((int)objPos.x, (int)objPos.y);
	}

    for(unsigned int i = 0; i < objectArray.size(); i++){ //updates each object
        objectArray[i]->Update(dt);
	}

	for(unsigned int i = 0; i < objectArray.size(); i++){ //deletes dead object and plays their sound
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

void State::AddObject(int mouseX, int mouseY){ //adds object to given coordinates

	shared_ptr<GameObject> go = shared_ptr<GameObject> (new GameObject());
	Sprite* enemy = (new Sprite(*go, PENGUINFACEFILE));
	Sound* deathSound = (new Sound(*go, BOOMAUDIOFILE));
	Face* face = (new Face(*go));

	go->box.x = -Camera::pos.x + mouseX - enemy->GetWidth()/2;
	go->box.y = -Camera::pos.y + mouseY - enemy->GetHeight()/2;

	go->AddComponent(enemy);

	go->AddComponent(deathSound);

	go->AddComponent(face);

	objectArray.emplace_back(move(go));
}
