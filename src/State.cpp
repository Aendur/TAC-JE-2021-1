#include "State.h"

#include <stdexcept>
#include <string>
#include <SDL/SDL2-2.0.16/include/SDL.h>

State::State (void) {
	bg.Open("assets/img/ocean.jpg");
	music.Open("assets/audio/stageState.ogg");
}

bool State::QuitRequested (void) {
	return this->quitRequested;
}

void State::LoadAssets (void) {
	throw std::exception("not implemented");
}

void State::Update (float dt) {
	if (SDL_QuitRequested()) {
		this->quitRequested = true;
	}
}

void State::Render (void) {
	bg.Render(0, 0);
}

