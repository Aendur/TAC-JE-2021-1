#include "StageState.h"

#include <stdexcept>
#include <string>
#include "InputManager.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "PenguinBody.h"
#include "Alien.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Vec2.h"
#include "Collider.h"
#include "PenguinBody.h"
#include "GameData.h"
#include "EndState.h"
#include "errors.h"

void StageState::LoadAssets (void) {
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


	GameObject * penguin = new GameObject();
	penguin->AddComponent(new PenguinBody(*penguin));
	penguin->SetCenterPosition({704,640});
	this->AddObject(penguin);


	//int nAliens = 1;
	//for (int i = 0; i < nAliens; ++i) {
	//	GameObject * alien = new GameObject();
	//	int nMinions = 3 + rand() % 7;
	//	alien->AddComponent(new Alien(*alien, nMinions, (float) i));
	//	alien->SetCenterPosition({512, 300});
	//	this->AddObject(alien);
	//}

	int N;
	float T;
	T = (float)(10 + rand() % 41) / 10.0f;
	N = 3 + rand() % 7;
	GameObject * alien = new GameObject();
	alien->AddComponent(new Alien(*alien, N, T));
	alien->SetCenterPosition({0, 0});
	this->AddObject(alien);

	T = (float)(10 + rand() % 41) / 10.0f;
	N = 3 + rand() % 7;
	alien = new GameObject();
	alien->AddComponent(new Alien(*alien, N, T));
	alien->SetCenterPosition({0, 1280});
	this->AddObject(alien);

	T = (float)(10 + rand() % 41) / 10.0f;
	N = 3 + rand() % 7;
	alien = new GameObject();
	alien->AddComponent(new Alien(*alien, N, T));
	alien->SetCenterPosition({1408, 0});
	this->AddObject(alien);

	T = (float)(10 + rand() % 41) / 10.0f;
	N = 3 + rand() % 7;
	alien = new GameObject();
	alien->AddComponent(new Alien(*alien, N, T));
	alien->SetCenterPosition({1408, 1280});
	this->AddObject(alien);

	Camera::Follow(penguin);
}

void StageState::Update (float dt) {
	this->HandleInput();
	if (PenguinBody::player == nullptr) {
		Camera::Unfollow();
		GameData::playerVictory = GameData::DEFEAT;
		Game::GetInstance().Push(new EndState());
		popRequested = true;
	}
	Camera::Update(dt);
	UpdateArray(dt);
	DetectCollisions();
	EraseDeadObjects();

	if (Alien::alienCount == 0) {
		Camera::Unfollow();
		GameData::playerVictory = GameData::VICTORY;
		Game::GetInstance().Push(new EndState());
		popRequested = true;
	}

}

void StageState::Render (void) {
	RenderArray();
}

void StageState::Start(void) {
	if (!started) {
		LoadAssets();
		StartArray();
		started = true;
	}
}

void StageState::Pause(void) { }
void StageState::Resume(void) { }


void StageState::HandleInput(void) {
	InputManager & inputManager = InputManager::GetInstance();

	// Quit if requested or ESC was pressed
	this->popRequested = inputManager.IsKeyDown(KEY_ESC);
	this->quitRequested = inputManager.QuitRequested();
	if (this->popRequested || this->quitRequested) return;

	// Get keyboard input for camera WASD / arrows
	bool accelerateCameraU = inputManager.IsKeyDown(KEY_UP);
	bool accelerateCameraD = inputManager.IsKeyDown(KEY_DOWN);
	bool accelerateCameraL = inputManager.IsKeyDown(KEY_LEFT);
	bool accelerateCameraR = inputManager.IsKeyDown(KEY_RIGHT);
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

void StageState::DetectCollisions(void) {
	for (const auto & [_, objects] : Collider::GetGlobalColliders()) {
		auto obj1 = objects.begin();
		auto end   = objects.end();
		while (obj1 != end) {
			auto obj2 = obj1;
			++obj2;
			while (obj2 != end) {
				const Collider * c1 = (Collider*)(*obj1)->GetComponent("Collider");
				const Collider * c2 = (Collider*)(*obj2)->GetComponent("Collider");
				if (c1 != nullptr && c2 != nullptr && c1->IsCollidingWith(*c2)) {
					(*obj1)->NotifyCollision(**obj2);
					(*obj2)->NotifyCollision(**obj1);
					//std::cout << (*obj1) << " collided with " << (*obj2) << std::endl;
				}
				++obj2;
			}
			++obj1;
		}
	}
}

void StageState::EraseDeadObjects(void) {
	for (size_t i = 0; i < this->objectArray.size(); ++i) {
		if (this->objectArray[i]->IsDead()) {
			this->objectArray.erase(this->objectArray.begin() + i);
		}
	}
}
