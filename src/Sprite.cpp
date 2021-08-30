#include "Sprite.h"
#include "Game.h"

#include <stdexcept>
#include <SDL/SDL2-2.0.16/include/SDL.h>
#include <SDL/SDL2_image-2.0.5/include/SDL_image.h>

Sprite::Sprite (void) {
	throw std::exception("not implemented Sprite::Sprite (void)");
}

Sprite::Sprite (std::string file) {
	this->Open(file);
}

Sprite::~Sprite (void) {
	if (this->IsOpen()) {
		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
	}
}

void Sprite::Open (std::string file) {
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

void Sprite::SetClip (int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render (int x, int y) {
	SDL_Rect dstrect;
	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = this->width;
	dstrect.h = this->height;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstrect);
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
