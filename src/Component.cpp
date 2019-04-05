#include "Component.h"

using std::string;

Component::Component(GameObject& associated) : associated(associated){


}

Component::~Component(){


}

void Component::Update(float dt){


}

void Component::Render(){


}

bool Component::Is(string type){

    return false;
}