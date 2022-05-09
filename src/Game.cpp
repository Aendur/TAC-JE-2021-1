#include "Game.h"
#include "State.h"
#include "Camera.h"
#include "Resources.h"
#include "InputManager.h"
#include "errors.h"

#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

Game::Game(const std::string & title, int width, int height) {
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


	std::cout << "init camera properties..." << std::endl;
	Camera::width = width;
	Camera::height = height;
	
	//std::cout << "init game state..." << std::endl;
	//this->state = new StageState();
	
	std::cout << "done." << std::endl;
}

Game::~Game() {
	std::cout << "clearing game states..." << std::endl;
	if (this->storedState != nullptr) { delete this->storedState; }
	while (!stateStack.empty()) { stateStack.pop(); }

	std::cout << "clearing resources..." << std::endl;
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();

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

Game & Game::GetInstance (void) {
	if (Game::instance == nullptr) {
		std::cout << "instance is null. Creating singleton" << std::endl;
		new Game("Diogo Cesar Ferreira - 11/0027931", 1024, 600);
	}
	return *Game::instance;
}

SDL_Renderer * Game::GetRenderer (void) const {
	return this->renderer;
}

State & Game::GetCurrentState (void) const {
	//return *this->state;
	return *this->stateStack.top();
}

void Game::Push(State * state) {
	#pragma message (MSG_INCOMPLETE_ERR)
	this->storedState = state;
}

void Game::Run(void) {
	while (this->ManageStates() && !this->stateStack.top()->QuitRequested()) {
		const std::unique_ptr<State> & currentState = this->stateStack.top();

		this->CalculateDeltaTime();
		InputManager::GetInstance().Update();
		currentState->Update(this->dt);
		currentState->Render();

		SDL_RenderPresent(this->renderer);
		SDL_Delay(32);
	}
}

bool Game::ManageStates(void) {
	PopAndResumeState();
	StartStoredState();
	return (!this->stateStack.empty());
}

void Game::PopAndResumeState(void) {
	if (!this->stateStack.empty()) {
		if (this->stateStack.top()->PopRequested()) { this->stateStack.pop(); }
		if (!this->stateStack.empty()) { this->stateStack.top()->Resume(); }
	}
}

void Game::StartStoredState(void) {
	if (this->storedState != nullptr) {
		if (!this->stateStack.empty()) { this->stateStack.top()->Pause(); }
		this->stateStack.push(std::unique_ptr<State>(this->storedState));
		this->stateStack.top()->Start();
		this->storedState = nullptr;
	}
}

////////////////////

void Game::CalculateDeltaTime(void) {
	int lastFrame = this->frameStart;
	this->frameStart = SDL_GetTicks();
	this->dt = (float) (this->frameStart - lastFrame) * 0.001f;
	//std::cout << this->dt << std::endl;
}

float Game::GetDeltaTime(void) {
	return this->dt;
}

