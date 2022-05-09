#include "TitleState.h"
#include "Game.h"
#include "GameObject.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include "StageState.h"
#include "Sprite.h"
#include "Camera.h"
#include "Text.h"
#include "errors.h"
#include <string>

void TitleState::LoadAssets (void) {
	GameObject * bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, "assets/img/title.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	bg->SetPosition({0, 0});
	this->AddObject(bg);

	FontStyle style;
	style.color = {30, 100, 150, 127};
	style.file = "assets/font/Call me maybe.ttf";
	style.size = 70;
	style.style = TextStyle::BLINKING;

	GameObject * text = new GameObject();
	text->AddComponent(new Text(*text, style, u8"Press SPACE to start"));
	text->AddComponent(new CameraFollower(*text, {((float)Camera::width - text->box.w) / 2.0f, (float)(Camera::height - 250)}));
	this->AddObject(text);
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

