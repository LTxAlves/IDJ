#include "GameObject.h"

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using std::vector;
using std::shared_ptr;
using std::move;

GameObject::GameObject(){       

    isDead = false;
}

GameObject::~GameObject(){

    int i, size = components.size();

    for(i = size - 1; i >= 0; i--){ //clears vector components
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
}

void GameObject::RemoveComponent(Component* cpt){

    int size = components.size(), i;

    for(i = 0; i < size; i++){
        if(components[i].get() == cpt){ //checks if component exists within vector
            components.erase(components.begin()+i);
            break;
        }
    }
    
}

Component* GameObject::GetComponent(string type){

    int size = components.size(), i;

        for(i = 0; i < size; i++){
            if(components[i]->Is(type))
                return components[i].get();
        }
        
    return nullptr;
}