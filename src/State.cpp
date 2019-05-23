#include "State.h"
#include "GameObject.h"
#include "Sound.h"

State::State() :    popRequested(false),
                    quitRequested(false),
                    started(false){


}

State::~State(){

    objectArray.clear();
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

void State::Start(){


}

void State::Pause(){


}

void State::Resume(){


}

void State::LoadAssets(){


}

void State::Update(float dt){


}

void State::Render(){


}

bool State::PopRequested(){

	return popRequested;
}

bool State::QuitRequested(){

	return quitRequested;
}

void State::StartArray(){

	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Start();
	}

	started = true;
}

void State::UpdateArray(float dt){

	for(unsigned int i = 0; i < objectArray.size(); i++){ //renders each object
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

void State::RenderArray(){

	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Render();
	}
}
