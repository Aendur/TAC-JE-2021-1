#include "State.h"

#include <stdexcept>
#include <string>
#include "InputManager.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "Alien.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Vec2.h"
#include "errors.h"

State::State (void) {
	this->started = false;
	this->quitRequested = false;
}

State::~State(void) {
	this->objectArray.clear();
}

void State::Start(void) {
	if (!started) {
		LoadAssets();
		for (auto & i : objectArray) { i->Start(); }
		started = true;
	}
}

bool State::QuitRequested (void) {
	return this->quitRequested;
}

void State::LoadAssets (void) {
	GameObject * bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	bg->SetPosition({0, 0});
	this->AddObject(bg);

	music.Open("assets/audio/stageState.ogg");
	music.Play();

	GameObject * tiles = new GameObject();
	TileSet * tileset = new TileSet(*tiles, 64, 64, "assets/img/tileset.png");
	tiles->AddComponent(tileset);
	tiles->AddComponent(new TileMap(*tiles, "assets/map/tileMap.txt", tileset));
	tiles->SetPosition({0, 0});
	this->AddObject(tiles);

	GameObject * alien = new GameObject();
	alien->AddComponent(new Alien(*alien, 5));
	alien->SetCenterPosition({512, 300});
	this->AddObject(alien);
}

void State::Update (float dt) {
	this->HandleInput();
	Camera::Update(dt);

	for (size_t i = 0; i < this->objectArray.size(); ++i) {
		this->objectArray[i]->Update(dt);
	}
	for (size_t i = 0; i < this->objectArray.size(); ++i) {
		if (this->objectArray[i]->IsDead()) {
			this->objectArray.erase(this->objectArray.begin() + i);
		}
	}
}

void State::Render (void) {
	for(auto & obj : this->objectArray) {
		obj->Render();
	}
}

std::weak_ptr<GameObject> State::AddObject(GameObject * go) {
	auto obj_ptr = std::shared_ptr<GameObject>(go);
	if (started) { obj_ptr->Start(); }
	objectArray.push_back(obj_ptr);
	return std::weak_ptr<GameObject>(obj_ptr);

}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject * go) const {
	for (auto & shared : objectArray) {
		if (go == shared.get()) {
			return std::weak_ptr<GameObject>(shared);
		}
	}
	return std::weak_ptr<GameObject>();
}

void State::HandleInput(void) {
	InputManager & inputManager = InputManager::GetInstance();

	// Quit if requested or ESC was pressed
	this->quitRequested = (inputManager.IsKeyDown(KEY_ESC) || inputManager.QuitRequested());

	// Get keyboard input for camera WASD / arrows
	bool accelerateCameraU = (inputManager.IsKeyDown(KEY_W) || inputManager.IsKeyDown(KEY_UP));
	bool accelerateCameraD = (inputManager.IsKeyDown(KEY_S) || inputManager.IsKeyDown(KEY_DOWN));
	bool accelerateCameraL = (inputManager.IsKeyDown(KEY_A) || inputManager.IsKeyDown(KEY_LEFT));
	bool accelerateCameraR = (inputManager.IsKeyDown(KEY_D) || inputManager.IsKeyDown(KEY_RIGHT));
	float cameraAcceleration = 50.0f;
	float cameraDecceleration = 0.80f;
	if (!(accelerateCameraU || accelerateCameraD) ) {
		// deccelerate vertical
		Camera::speed.y = std::abs(Camera::speed.y) < 1.0f ? 0.0f : Camera::speed.y * cameraDecceleration;
	} else {
		if (accelerateCameraU) { Camera::speed.y -= cameraAcceleration; }
		if (accelerateCameraD) { Camera::speed.y += cameraAcceleration; }
	}
	if (!(accelerateCameraL || accelerateCameraR) ) {
		// deccelerate horizontal
		Camera::speed.x = std::abs(Camera::speed.x) < 1.0f ? 0.0f : Camera::speed.x * cameraDecceleration;
	} else {
		if (accelerateCameraL) { Camera::speed.x -= cameraAcceleration; }
		if (accelerateCameraR) { Camera::speed.x += cameraAcceleration; }
	}
}
