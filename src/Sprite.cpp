#include "Sprite.h"
#include "Game.h"
#include "GameObject.h"
#include "Resources.h"
#include "Camera.h"
#include <SDL2/SDL_image.h>

Sprite::Sprite (GameObject & associated) : Component(associated) {
	this->scale = { 1.0f, 1.0f };
	this->frameCount = 1;
	this->currentFrame = 0;
	this->timeElapsed = 0.0f;
	this->frameTime = 0.0f;
}

Sprite::Sprite (GameObject & associated, const std::string & file, int fCount, float fTime, float maxLifeTime) : Sprite(associated) {
	this->scale = { 1.0f, 1.0f };
	this->frameCount = fCount;
	this->currentFrame = 0;
	this->timeElapsed = 0.0f;
	this->frameTime = fTime;
	this->secondsToSelfDestruct = maxLifeTime;
	this->selfDestructCount.Restart();
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

	this->width /= frameCount;

	if (associated.box.w == 0 && associated.box.h == 0) {
		associated.box.x = 0;
		associated.box.y = 0;
		associated.box.w = (float) this->width;
		associated.box.h = (float) this->height;
	}
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

	int scaledW = (int)(clipRect.w * scale.x);
	int scaledH = (int)(clipRect.h * scale.y);
	dstrect.x = x - (scaledW - clipRect.w) / 2;
	dstrect.y = y - (scaledH - clipRect.h) / 2;
	dstrect.w = scaledW;
	dstrect.h = scaledH;
	if (-0.1f < associated.GetRotation() && associated.GetRotation() < 0.0f) {
		SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstrect);
	} else {
		SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstrect, associated.GetRotation(), NULL, SDL_FLIP_NONE);
	}
}

// Inherited from Component
void Sprite::Update(float dt) { 
	if (frameCount > 1) {
		timeElapsed += dt;
		if (timeElapsed > frameTime) {
			timeElapsed = 0.0f;
			SetFrame(currentFrame + 1);
		}
	}
	if (secondsToSelfDestruct > 0.0f) {
		selfDestructCount.Update(dt);
		if (selfDestructCount.Get() > secondsToSelfDestruct) {
			associated.RequestDelete();
		}
	}
}

void Sprite::Render (void) {
	this->Render((int)(associated.box.x - Camera::pos.x), (int)(associated.box.y - Camera::pos.y));
}

bool Sprite::Is (const std::string & type) const {
	return type.compare("Sprite") == 0;
}

const std::string Sprite::GetType(void) const {
	return "Sprite";
}

void Sprite::SetScale(float scaleX, float scaleY) {
	if (scaleX > 0.01f) { scale.x = scaleX; }
	if (scaleY > 0.01f) { scale.y = scaleY; }
}


const Vec2 & Sprite::GetScale(void) const {
	return this->scale;
}

void Sprite::SetFrame(int frame) {
	currentFrame = frame % frameCount;
	SetClip(width * currentFrame, 0, width, height);
}

void Sprite::SetFrameCount(int fCount) {
	(void) fCount;
	//this->frameCount = fCount;
}

void Sprite::SetFrameTime(float fTime) {
	this->frameTime = fTime;
}
