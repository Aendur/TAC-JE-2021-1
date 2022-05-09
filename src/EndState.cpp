#include "EndState.h"
#include "Game.h"
#include "GameObject.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include "StageState.h"
#include "Sprite.h"
#include "Camera.h"
#include "Text.h"
#include "GameData.h"
#include "errors.h"
#include <string>

void EndState::LoadAssets (void) {
	GameObject * bg = new GameObject();
	switch (GameData::playerVictory) {
	case GameData::VICTORY:
	bg->AddComponent(new Sprite(*bg, "assets/img/win.jpg"));
	bgm.Open("assets/audio/endStateWin.ogg");
	bgm.Play();
	break;
	
	case GameData::DEFEAT:
	bg->AddComponent(new Sprite(*bg, "assets/img/lose.jpg"));
	bgm.Open("assets/audio/endStateLose.ogg");
	bgm.Play();
	break;

	default:
	break;
	}
	bg->AddComponent(new CameraFollower(*bg));
	bg->SetPosition({0, 0});
	this->AddObject(bg);

	FontStyle style;
	style.color = {30, 100, 150, 127};
	style.file = "assets/font/Call me maybe.ttf";
	style.size = 50;
	style.style = TextStyle::BLINKING;

	GameObject * text = new GameObject();
	text->AddComponent(new Text(*text, style, u8"Press SPACE to return to title"));
	text->AddComponent(new CameraFollower(*text, {((float)Camera::width - text->box.w) / 2.0f, (float)(Camera::height - 250)}));
	this->AddObject(text);

}

void EndState::Update (float dt) {
	HandleInput();
	UpdateArray(dt);
}

void EndState::Render (void) {
	RenderArray();
}

void EndState::Start(void) {
	if (!started) {
		LoadAssets();
		StartArray();
		started = true;
	}
}

void EndState::Pause(void) { }
void EndState::Resume(void) {
	this->quitRequested = false;
}


void EndState::HandleInput(void) {
	InputManager & inputManager = InputManager::GetInstance();
	this->popRequested = inputManager.IsKeyDown(KEY_SPACE);
	this->quitRequested = inputManager.QuitRequested() || inputManager.IsKeyDown(KEY_ESC);
}

