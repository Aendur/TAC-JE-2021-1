#include "Game.h"
#include "State.h"

#include <stdexcept>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

Game::Game(std::string title, int width, int height) {
	if (Game::instance != nullptr) {
		throw std::logic_error("Cannot init singleton twice");
	}

	Game::instance = this;

	std::cout << "initializing SDL..." << std::endl;
	int status;
	status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	if (status != 0) {
		std::string error = SDL_GetError();
		throw std::runtime_error(error);
	}

	std::cout << "initializing IMG..." << std::endl;
	int imgflags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	status = IMG_Init(imgflags);
	if (status != imgflags) {
		std::string error = IMG_GetError();
		throw std::runtime_error(error);
	}

	std::cout << "initializing MIX..." << std::endl;
	int mixflags = MIX_INIT_OGG;
	status = Mix_Init(mixflags);
	if (status != mixflags) {
		std::string error = Mix_GetError();
		throw std::runtime_error(error);
	}

	std::cout << "opening audio out..." << std::endl;
	status = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	if (status != 0) {
		std::string error = Mix_GetError();
		throw std::runtime_error(error);
	}

	std::cout << "opening audio channels..." << std::endl;
	int nchannels = 32;
	status = Mix_AllocateChannels(32);
	if (status != nchannels) {
		std::string error = Mix_GetError();
		throw std::runtime_error(error);
	}

	std::cout << "creating SDL window..." << std::endl;
	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (this->window == nullptr) {
		std::string error = SDL_GetError();
		throw std::runtime_error(error);
	}

	std::cout << "creating SDL renderer..." << std::endl;
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if (this->renderer == nullptr) {
		std::string error = SDL_GetError();
		throw std::runtime_error(error);
	}

	std::cout << "init game state..." << std::endl;
	this->state = new State();
	
	std::cout << "done." << std::endl;
}

Game::~Game() {
	std::cout << "deallocating renderer..." << std::endl;
	SDL_DestroyRenderer(this->renderer);
	this->renderer = nullptr;
	
	std::cout << "deallocating window..." << std::endl;
	SDL_DestroyWindow(this->window);
	this->window = nullptr;

	std::cout << "closing audio output..." << std::endl;
	Mix_CloseAudio();
	
	std::cout << "cleanup MIX..." << std::endl;
	Mix_Quit();
	
	std::cout << "cleanup IMG..." << std::endl;
	IMG_Quit();
	
	std::cout << "cleanup SDL..." << std::endl;
	SDL_Quit();
	
	std::cout << "done." << std::endl;
}

void Game::Run(void) {
	while (!this->state->QuitRequested()) {
		this->state->Update(0.0f);
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
		std::cout << "instance is null. Creating singleton" << std::endl;
		new Game("Diogo Cesar Ferreira - 11/0027931", 1024, 600);
	}
	return *Game::instance;
}
