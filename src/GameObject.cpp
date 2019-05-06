#include "GameObject.h"
#include "Component.h"
#include "Rect.h"

GameObject::GameObject() :  angleDeg(0),
                            isDead(false),
                            started(false){


}

GameObject::~GameObject(){

    for(int i = (int) components.size() - 1; i >= 0; i--){ //clears vector components
        components.erase(components.begin() + i);
    }

    components.clear(); //clears vector
}

void GameObject::Update(float dt){

    for(auto it = components.begin(); it != components.end(); it++){
        if(*(it) != nullptr)
            (*it)->Update(dt); //calls update() function of each component
    }

}

void GameObject::Render(){

    for(auto it = components.begin(); it != components.end(); it++){
        if(*it != nullptr)
            (*it)->Render(); //calls render() function of each component
    }
}

bool GameObject::IsDead(){

    return isDead;
}

void GameObject::RequestDelete(){

    isDead = true;
}

void GameObject::AddComponent(Component* cpt){

    if(cpt != nullptr)
        components.emplace_back(cpt); //adds component to vector end

    if(started)
        components.back()->Start(); //starts if component added after start of others
}

void GameObject::RemoveComponent(Component* cpt){

    for(unsigned int i = 0; i < components.size(); i++){
        if(components[i].get() == cpt){ //checks if component exists within vector
            components.erase(components.begin()+i);
            break;
        }
    }
    
}

Component* GameObject::GetComponent(string type){

    int size = components.size(), i;

        for(i = 0; i < size; i++){
            if(components[i]->Is(type)) //finds component
                return components[i].get(); //returns it
        }
        
    return nullptr;
}

void GameObject::Start(){

    for(auto it = components.begin(); it != components.end(); it++){ //calls start() function of each component
        (*it)->Start();
    }

    started = true; //sets started flag
}