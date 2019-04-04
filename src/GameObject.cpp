#include "GameObject.h"

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using std::vector;
using std::unique_ptr;

GameObject::GameObject(){

    isDead = false;
}

GameObject::~GameObject(){

    int i, size = components.size();

    for(i = size - 1; i >= 0; i--){
        components.erase(components.begin() + i);
    }

    components.clear();    
}

void GameObject::Update(float dt){

    vector<unique_ptr<Component>>::iterator it;

    for(it = components.begin(); it != components.end(); it++){
        (*it)->Update(dt);
    }

}

void GameObject::Render(){

    vector<unique_ptr<Component>>::iterator it;

    for(it = components.begin(); it != components.end(); it++){
        (*it)->Render();
    }
}

bool GameObject::IsDead(){

    return isDead;
}

void GameObject::RequestDelete(){

    isDead = true;
}

void GameObject::AddComponent(unique_ptr<Component> cpt){

    if(cpt != nullptr)
        components.emplace_back(cpt);
}

void GameObject::RemoveComponent(unique_ptr<Component> cpt){

    int size = components.size(), i;
    bool found = false;

    for(i = 0; i < size; i++){
        if(components[i] == cpt){
            components.erase(components.begin()+i);
            found = true;
            break;
        }
    }

    if (!found)
        SDL_Log("RemoveComponent could not find pointer in vector of components");
    
}

unique_ptr<Component> GameObject::GetComponent(string type){

    int size = components.size(), i;

        for(i = 0; i < size; i++){
            if(components[i]->Is(type))
                return components[i];
        }

    SDL_Log("GetComponent could not find %s in vector of components", type.c_str());
    return nullptr;
}