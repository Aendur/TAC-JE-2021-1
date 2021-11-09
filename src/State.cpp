#include "State.h"

#include <stdexcept>
#include <string>
//#include <SDL2/SDL.h>
#include "InputManager.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Vec2.h"

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
	this->HandleInput();
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

void State::HandleInput(void) {
	InputManager & inputManager = InputManager::GetInstance();

	// Quit if requested or ESC was pressed
	this->quitRequested = (inputManager.IsKeyDown(KEY_ESC) || inputManager.QuitRequested());

	// Spawn faces on SPACE key press
	int mouseX = inputManager.GetMouseX();
	int mouseY = inputManager.GetMouseY();
	if (inputManager.KeyPress(KEY_SPACE)) {
		Vec2 objPos = Vec2(mouseX, mouseY) + Vec2(200, 0).RotateBy(rand() % 360);
		AddObject((int)objPos.x, (int)objPos.y);
	}

	// Damage faces on MOUSE click
	if (inputManager.MousePress(MOUSE_LEFT) || inputManager.MousePress(MOUSE_RIGHT)) {
		for(int i = objectArray.size() - 1; i >= 0; --i) {
			GameObject & obj = *objectArray[i];

			if(obj.box.Contains((float) mouseX, (float) mouseY)) {
				Face* face = (Face*)obj.GetComponent("Face");
				if (face != nullptr) {
					// Aplica dano
					face->Damage(std::rand() % 10 + 10);
					// Sai do loop (só queremos acertar um)
					break;
				}
			}
		}
	}
}
