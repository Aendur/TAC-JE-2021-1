#include "Sprite.h"
#include "Game.h"
#include "GameObject.h"

#include <stdexcept>
#include <SDL2/SDL_image.h>

Sprite::Sprite (GameObject & associated) : Component(associated) { }

Sprite::Sprite (GameObject & associated, const std::string & file) : Sprite(associated) {
	this->Open(file);
}

Sprite::~Sprite (void) {
	if (this->IsOpen()) {
		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
	}
}

void Sprite::Open (const std::string& file) {
	if (this->IsOpen()) {
		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
	}
	
	this->texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
	if (this->texture == nullptr) {
		std::string error = IMG_GetError();
		throw std::runtime_error(error);
	}
	
	int status = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
	if (status != 0) {
		std::string error = IMG_GetError();
		throw std::runtime_error(error);
	}

	this->SetClip(0, 0, this->width, this->height);
}

void Sprite::Reopen (const std::string& file) {
	if (this->IsOpen()) {
		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
	}
	
	this->texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
	if (this->texture == nullptr) {
		std::string error = IMG_GetError();
		throw std::runtime_error(error);
	}
	
	int newW, newH;
	int status = SDL_QueryTexture(this->texture, nullptr, nullptr, &newW, &newH);
	if (status != 0) {
		std::string error = IMG_GetError();
		throw std::runtime_error(error);
	}
	
	if (newW != this->width || newH != this->height) {
		throw std::logic_error("new texture must have the same dimensions as the old one!");
	}
}

void Sprite::SetClip (int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
	associated.box.x = x;
	associated.box.y = y;
	associated.box.w = w;
	associated.box.h = h;
}

int Sprite::GetWidth (void) {
	return this->width;
}

int Sprite::GetHeight (void) {
	return this->height;
}

bool Sprite::IsOpen (void) {
	return (this->texture != nullptr);
}


// Inherited from Component
void Sprite::Update(float dt) { (void) dt; }

void Sprite::Render (void) { //int x, int y) {
	SDL_Rect dstrect;
	dstrect.x = associated.box.x;
	dstrect.y = associated.box.y;
	dstrect.w = associated.box.w;
	dstrect.h = associated.box.h;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstrect);
}

bool Sprite::Is (const std::string & type) {
	return (type.compare("Sprite") == 0);
}