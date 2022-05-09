#include "TitleState.h"
#include "Game.h"
#include "GameObject.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include "StageState.h"
#include "Sprite.h"
#include "errors.h"
#include <string>

void TitleState::LoadAssets (void) {
	GameObject * bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, "assets/img/title.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	bg->SetPosition({0, 0});
	this->AddObject(bg);


}

void TitleState::Update (float dt) {
	HandleInput();
	UpdateArray(dt);
}

void TitleState::Render (void) {
	RenderArray();
}

void TitleState::Start(void) {
	if (!started) {
		LoadAssets();
		StartArray();
		started = true;
	}
}

void TitleState::Pause(void) { }
void TitleState::Resume(void) {
	this->quitRequested = false;
}


void TitleState::HandleInput(void) {
	InputManager & inputManager = InputManager::GetInstance();

	// Quit if requested or ESC was pressed
	if (inputManager.IsKeyDown(KEY_ESC) || inputManager.QuitRequested()) {
		this->quitRequested = true;
	} else if (inputManager.IsKeyDown(KEY_SPACE)) {
		Game::GetInstance().Push(new StageState());
	}


	// Get keyboard input for camera WASD / arrows
	// bool accelerateCameraU = inputManager.IsKeyDown(KEY_UP);
	// bool accelerateCameraD = inputManager.IsKeyDown(KEY_DOWN);
	// bool accelerateCameraL = inputManager.IsKeyDown(KEY_LEFT);
	// bool accelerateCameraR = inputManager.IsKeyDown(KEY_RIGHT);
}

