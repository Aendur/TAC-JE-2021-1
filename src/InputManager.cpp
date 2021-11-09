#include "InputManager.h"
#include "errors.h"

#include <iostream>
#include <SDL2/SDL.h>

InputManager::InputManager(void) {
	std::cout << "creating new input manager instance" << std::endl;
	for(int i = 0; i < 6; ++i) {
		this->mouseState[i] = false;
		this->mouseUpdate[i] = -1;
	}
	this->quitRequested = false;
	this->updateCounter = -1;
	this->mouseX = -1;
	this->mouseY = -1;
}

InputManager::~InputManager(void) { }

InputManager & InputManager::GetInstance (void) {
	static InputManager * instance = nullptr;
	if (instance == nullptr) {
		instance = new InputManager();
	}
	return *instance;
}

void InputManager::Update(void) {
	++this->updateCounter;
	this->quitRequested = false;
	
	SDL_GetMouseState(&this->mouseX, &this->mouseY);
	
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_KEYDOWN:
			if (event.key.repeat) break;
			this->keyState[event.key.keysym.sym] = true;
			this->keyUpdate[event.key.keysym.sym] = this->updateCounter;
			break;
		case SDL_KEYUP:
			this->keyState[event.key.keysym.sym] = false;
			this->keyUpdate[event.key.keysym.sym] = this->updateCounter;
			break;
		case SDL_MOUSEBUTTONDOWN:
			this->mouseState[event.button.button] = true;
			this->mouseUpdate[event.button.button] = this->updateCounter;
			break;
		case SDL_MOUSEBUTTONUP:
			this->mouseState[event.button.button] = false;
			this->mouseUpdate[event.button.button] = this->updateCounter;
			break;
		case SDL_QUIT:
			this->quitRequested = true;
			break;
		default:
			//std::cout << "unhandled SDL event: " << event.type << std::endl;
			break;
		}
	}
}

bool InputManager::KeyPress(int key) {
	if (this->keyUpdate.find(key) == this->keyUpdate.end()) {
		std::cout << "unregistered key: " << key << std::endl;
	}
	return (this->keyUpdate[key] == this->updateCounter) && (this->keyState[key]);
}

bool InputManager::KeyRelease(int key) {
	if (this->keyUpdate.find(key) == this->keyUpdate.end()) {
		std::cout << "unregistered key: " << key << std::endl;
	}
	return (this->keyUpdate[key] == this->updateCounter) && (!this->keyState[key]);
}

bool InputManager::IsKeyDown(int key) {
	if (this->keyState.find(key) == this->keyState.end()) {
		std::cout << "unregistered key: " << key << std::endl;
	}
	return this->keyState[key];
}

bool InputManager::MousePress(int button) {
	if (button < 0 || button >= 6) {
		std::cout << "mouse button not in range: " << button << std::endl;
		return false;
	}
	return (this->mouseUpdate[button] == this->updateCounter) && (this->mouseState[button]);

}

bool InputManager::MouseRelease(int button) {
	if (button < 0 || button >= 6) {
		std::cout << "mouse button not in range: " << button << std::endl;
		return false;
	}
	return (this->mouseUpdate[button] == this->updateCounter) && (!this->mouseState[button]);
}

bool InputManager::IsMouseDown(int button) {
	if (button < 0 || button >= 6) {
		std::cout << "mouse button not in range: " << button << std::endl;
		return false;
	}
	return this->mouseState[button];
}

int InputManager::GetMouseX(void) {
	return this->mouseX;
}

int InputManager::GetMouseY(void) {
	return this->mouseY;
}

bool InputManager::QuitRequested(void) {
	return this->quitRequested;
}
