#include "State.h"

#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>

State::State (void) {
	bg.Open("assets/img/ocean.jpg");
	music.Open("assets/audio/stageState.ogg");
}

bool State::QuitRequested (void) {
	return this->quitRequested;
}

void State::LoadAssets (void) {
	throw std::runtime_error("not implemented");
}

void State::Update (float dt) {
	(void) dt;
	if (SDL_QuitRequested()) {
		this->quitRequested = true;
	}
}

void State::Render (void) {
	bg.Render(0, 0);
}

