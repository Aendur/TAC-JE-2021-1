#include "Sprite.h"
#include "Game.h"
#include "GameObject.h"
#include "Resources.h"
#include "Camera.h"

#include <stdexcept>
#include <SDL2/SDL_image.h>

Sprite::Sprite (GameObject & associated) : Component(associated) { }

Sprite::Sprite (GameObject & associated, const std::string & file) : Sprite(associated) {
	this->Open(file);
}

Sprite::~Sprite (void) { }

void Sprite::Open (const std::string& file) {
	this->texture = Resources::GetImage(file);
	int status = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
	if (status != 0) {
		std::string error = IMG_GetError();
		throw std::runtime_error(error);
	}
	associated.box.x = 0;
	associated.box.y = 0;
	associated.box.w = (float) this->width;
	associated.box.h = (float) this->height;
	this->SetClip(0, 0, (int)associated.box.w, (int)associated.box.h);
}

void Sprite::Reopen (const std::string& file) {
	this->texture = Resources::GetImage(file);
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

void Sprite::Render (int x, int y) {
	SDL_Rect dstrect;
	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = clipRect.w;
	dstrect.h = clipRect.h;
	if (-0.1f < associated.GetRotation() && associated.GetRotation() < 0.0f) {
		SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstrect);
	} else {
		SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstrect, associated.GetRotation(), NULL, SDL_FLIP_NONE);
	}
}

// Inherited from Component
void Sprite::Update(float dt) { (void) dt; }

void Sprite::Render (void) {
	this->Render((int)(associated.box.x - Camera::pos.x), (int)(associated.box.y - Camera::pos.y));
}

bool Sprite::Is (const std::string & type) {
	return (type.compare("Sprite") == 0);
}