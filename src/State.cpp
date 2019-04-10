#include "State.h"

#define BGIMAGEFILE "assets/img/ocean.jpg"
#define MUSICFILE "assets/audio/stageState.ogg"
#define TILESETFILE "assets/img/tileset.png"
#define TILEMAPFILE "assets/map/tileMap.txt"
#define PENGUINFACEFILE "assets/img/penguinface.png"
#define BOOMAUDIOFILE "assets/audio/boom.wav"
#define TILEWIDTH 64
#define TILEHEIGHT 64
#define PI 3.14159265359 //value of constant pi

using std::move;
using std::shared_ptr;

State::State() : music(MUSICFILE){

    shared_ptr<GameObject> go = shared_ptr<GameObject> (new GameObject()); //GameObject required for Sprite

	Sprite* bg = new Sprite(*go, BGIMAGEFILE);

	go->box.x = 0;
	go->box.y = 0;

	go->AddComponent(bg);

	objectArray.emplace_back(move(go));

	shared_ptr<GameObject> go2 = shared_ptr<GameObject> (new GameObject());

    TileSet* ts = new TileSet(TILEWIDTH, TILEHEIGHT, TILESETFILE);
    TileMap* tm = new TileMap(*go2, TILEMAPFILE, ts);

	go2->box.w = 0;
	go2->box.h = 0;

	go2->AddComponent(tm);

	objectArray.emplace_back(move(go2));

    quitRequested = false;
    music.Play(-1);
}

State::~State(){

    objectArray.clear();
}

void State::LoadAssets(){

}

void State::Update(float dt){

    Input();

    for(unsigned int i = 0; i < objectArray.size(); i++){ //updates each object
        objectArray[i]->Update(dt);
    }

	for(unsigned int i = 0; i < objectArray.size(); i++){ //deletes dead object and play their sound
        if(objectArray[i]->IsDead()){
			Sound* soundPtr = static_cast<Sound*> (objectArray[i]->GetComponent("Sound"));
			if(soundPtr != nullptr){
				soundPtr->Play(1);
				while(Mix_Playing(soundPtr->GetChannel()));				
			}
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render(){

    for(unsigned int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

bool State::QuitRequested(){

    return quitRequested;
}

void State::Input(){
	SDL_Event event;
	int mouseX, mouseY, i;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				/*Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				ao usar get(), violamos esse princípio e estamos menos seguros.
				Esse código, assim como a classe Face, é provisório. Futuramente, para
				chamar funções de GameObjects, use objectArray[i]->função() direto.*/

				if(go->box.Contains((float)mouseX, (float)mouseY)) {
					Face* face = (Face*)go->GetComponent("Face");
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI*(rand() % 1001)/500.0) + Vec2(mouseX, mouseY);
				
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY){ //adds object to givn coordinates

	shared_ptr<GameObject> go = shared_ptr<GameObject> (new GameObject());
	Sprite* enemy = (new Sprite(*go, PENGUINFACEFILE));
	Sound* deathSound = (new Sound(*go, BOOMAUDIOFILE));
	Face* face = (new Face(*go));

	go->box.x = mouseX - enemy->GetWidth()/2;
	go->box.y = mouseY - enemy->GetHeight()/2;

	go->AddComponent(enemy);

	go->AddComponent(deathSound);

	go->AddComponent(face);

	objectArray.emplace_back(move(go));
}
