#include "Component.h"

using std::string;

Component::Component(GameObject& associated) : associated_obj(associated){

    associated_obj = associated;
}

Component::~Component(){


}

void Component::Update(float dt){


}

void Component::Render(){


}

bool Component::Is(string type){


}