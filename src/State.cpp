#include "State.h"
#include "Game.h"
#include "Face.h"
#include "Sound.h"

#define PI 3.14159265359

State::State() :    bg("assets/img/ocean.jpg"),
                    music("assets/audio/stageState.ogg"){

	unique_ptr<GameObject> GO = unique_ptr<GameObject> (new GameObject());

	GO->AddComponent(&bg);

	GO->box.x = 0;
	GO->box.y = 0;
	GO->box.w = bg.GetWidth();
	GO->box.h = bg.GetHeight();

	objectArray.emplace_back(std::move(GO));

    quitRequested = false;
    LoadAssets();
    music.Play(-1);
}

State::~State(){

    objectArray.clear();
}

void State::LoadAssets(){

}

void State::Update(float dt){

    int i, size = objectArray.size();

    Input();

    for(i = 0; i < size; i++){
        objectArray[i]->Update(1);
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
        }
    }

    SDL_Delay(dt);
}

void State::Render(){

    int i, size = objectArray.size();

    bg.Render(0, 0);

    for(i = 0; i < size; i++){
        objectArray[i]->Render();
    }
}

bool State::QuitRequested(){

    return quitRequested;
}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

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
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( (float)mouseX, (float)mouseY ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
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
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				std::cout << "mouseX = " << mouseX << " mouseY = " << mouseY << " objPos.x = " << objPos.x << " objPos.y = " << objPos.y << std::endl << std::endl;
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY){

	unique_ptr<GameObject> GO = unique_ptr<GameObject> (new GameObject());
	Sprite* enemy = (new Sprite("assets/img/penguinface.png"));
	Sound* deathSound = (new Sound(*GO, "assets/audio/boom.wav"));
	Face* face = (new Face(*GO));

	GO->AddComponent(enemy);

	GO->box.x = mouseX;
	GO->box.y = mouseY;
	GO->box.w = enemy->GetWidth();
	GO->box.h = enemy->GetHeight();

	enemy->SetClip(GO->box.x, GO->box.y, GO->box.w, GO->box.h);
	enemy->Render(mouseX, mouseY);

	std::cout << "X = " << GO->box.x << " Y = " << GO->box.y << " width = " << GO->box.w << " height = " << GO->box.h << std::endl << std::endl;

	GO->AddComponent(deathSound);

	GO->AddComponent(face);

	objectArray.emplace_back(std::move(GO));
}
