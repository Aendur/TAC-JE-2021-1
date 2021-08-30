#include "Game.h"

#include <stdexcept>
#include <SDL/SDL2_image-2.0.5/include/SDL_image.h>
#include <SDL/SDL2_mixer-2.0.4/include/SDL_mixer.h>

Game::Game(std::string title, int width, int height) {
	if (Game::instance != nullptr) {
		throw std::logic_error("Cannot init singleton twice");
	}

	int status;
	status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	if (status != 0) {
		std::string error = SDL_GetError();
		throw std::runtime_error(error);
	}

	int imgflags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	status = IMG_Init(imgflags);
	if (status != imgflags) {
		std::string error = IMG_GetError();
		throw std::runtime_error(error);
	}

	int mixflags = MIX_INIT_OGG;
	status = Mix_Init(mixflags);
	if (status != mixflags) {
		std::string error = Mix_GetError();
		throw std::runtime_error(error);
	}

	status = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	if (status != 0) {
		std::string error = Mix_GetError();
		throw std::runtime_error(error);
	}

	int nchannels = 32;
	status = Mix_AllocateChannels(32);
	if (status != nchannels) {
		std::string error = Mix_GetError();
		throw std::runtime_error(error);
	}

	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (this->window == nullptr) {
		std::string error = SDL_GetError();
		throw std::runtime_error(error);
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if (this->renderer == nullptr) {
		std::string error = SDL_GetError();
		throw std::runtime_error(error);
	}

	throw std::exception("missing initialize state");
	this->state = new State();
}

Game::~Game() {
	SDL_DestroyRenderer(this->renderer);
	this->renderer = nullptr;
	
	SDL_DestroyWindow(this->window);
	this->window = nullptr;

	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::Run(void) {
	while (!this->state->QuitRequested()) {
		this->state->Update();
		this->state->Render();
		SDL_RenderPresent(this->renderer);
		SDL_Delay(33);
	}
}

SDL_Renderer * Game::GetRenderer (void) {
	return this->renderer;
}

State & Game::GetState (void) {
	return *this->state;
}

Game & Game::GetInstance (void) {
	if (Game::instance == nullptr) {
		Game::instance = new Game("Diogo Cesar Ferreira - 11/0027931", 1024, 600);
	}
	return *Game::instance;
}
