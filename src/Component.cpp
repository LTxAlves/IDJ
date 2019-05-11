#include "Component.h"

Component::Component(GameObject& associated) : associated(associated){ //initializes Component::Associated

    //implemented in derived classes
}

Component::~Component(){

    //implemented in derived classes
}

void Component::Update(float dt){

    //implemented in derived classes
}

void Component::Render(){

    //implemented in derived classes
}

bool Component::Is(string type){

    return false; //default value; changes in derived classes
}

void Component::Start(){

    //implementedd di derived class
}

void Component::NotifyCollision(GameObject& other){

    //implemented in derived class
}