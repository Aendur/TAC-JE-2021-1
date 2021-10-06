#include "State.h"

#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "TileSet.h"
#include "TileMap.h"


State::State (void) {
	std::unique_ptr<GameObject> bg = std::make_unique<GameObject>();
	bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
	bg->box.x = 0;
	bg->box.y = 0;
	this->objectArray.push_back(std::move(bg));

	music.Open("assets/audio/stageState.ogg");
	music.Play();

	std::unique_ptr<GameObject> tiles = std::make_unique<GameObject>();
	TileSet * tileset = new TileSet(*tiles, 64, 64, "assets/img/tileset.png");
	tiles->AddComponent(tileset);
	tiles->AddComponent(new TileMap(*tiles, "assets/map/tileMap.txt", tileset));
	tiles->box.x = 0;
	tiles->box.y = 0;
	this->objectArray.push_back(std::move(tiles));
}

State::~State(void) {
	this->objectArray.clear();
}

bool State::QuitRequested (void) {
	return this->quitRequested;
}

void State::LoadAssets (void) {
	throw std::runtime_error("not implemented");
}

void State::Update (float dt) {
	this->Input();
	for(std::unique_ptr<GameObject> & obj : this->objectArray) {
		obj->Update(dt);
	}
	for (size_t i = 0; i < this->objectArray.size(); ++i) {
		if (this->objectArray[i]->IsDead()) {
			this->objectArray.erase(this->objectArray.begin() + i);
		}
	}
}

void State::Render (void) {
	for(std::unique_ptr<GameObject> & obj : this->objectArray) {
		obj->Render();
	}
}

void State::AddObject(int mouseX, int mouseY) {
	//std::unique_ptr<GameObject> obj(new GameObject());
	std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
	obj->AddComponent(new Sprite(*obj, "assets/img/penguinface.png"));
	obj->box.x = mouseX - obj->box.w / 2;
	obj->box.y = mouseY - obj->box.h / 2;

	obj->AddComponent(new Sound(*obj, "assets/audio/boom.wav"));
	obj->AddComponent(new Face(*obj));

	this->objectArray.push_back(std::move(obj));
}

#include "Vec2.h"
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

				if(go->box.Contains((float) mouseX, (float) mouseY) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( face != nullptr) {
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
				//Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				Vec2 objPos = Vec2( mouseX, mouseY ) + Vec2(200, 0).RotateBy(rand() % 360);
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}
