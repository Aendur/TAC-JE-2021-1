#include "Text.h"
#include "Game.h"
#include "GameObject.h"
#include "Camera.h"
#include "errors.h"

Text::Text (GameObject& associated, const FontStyle & fstyle, const std::string & t) : Component(associated) {
	this->style = fstyle;
	this->text = t;
	this->texture = nullptr;
	RemakeTexture();
}

Text::~Text (void) {
	if (this->texture != nullptr) {
		SDL_DestroyTexture(this->texture);
	}
}

void Text::RemakeTexture(void) {
	if (this->texture != nullptr) {
		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
	}
	this->font = Resources::GetFont(style.file, style.size);

	SDL_Surface * textSurface = nullptr;
	switch(this->style.style) {
		case TextStyle::SOLID: textSurface = TTF_RenderText_Solid(this->font.get(), this->text.c_str(), this->style.color); break;
		case TextStyle::SHADED: textSurface = TTF_RenderText_Shaded(this->font.get(), this->text.c_str(), this->style.color, {0,0,0,255}); break;
		case TextStyle::BLENDED: textSurface = TTF_RenderText_Blended(this->font.get(), this->text.c_str(), this->style.color); break;
		default: break;
	}

	if (textSurface != nullptr) {
		this->texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), textSurface);

		if (this->texture == nullptr) {
			std::string error = SDL_GetError();
			throw std::runtime_error(error);
		}

		associated.box.h = (float) textSurface->h;
		associated.box.w = (float) textSurface->w;
		SDL_FreeSurface(textSurface);
		textSurface = nullptr;
	}
}

/*void Text::Render (int x, int y) {
	// SDL_Rect dstrect;
	// int scaledW = (int)(clipRect.w * scale.x);
	// int scaledH = (int)(clipRect.h * scale.y);
	// dstrect.x = x - (scaledW - clipRect.w) / 2;
	// dstrect.y = y - (scaledH - clipRect.h) / 2;
	// dstrect.w = scaledW;
	// dstrect.h = scaledH;
	// if (-0.1f < associated.GetRotation() && associated.GetRotation() < 0.0f) {
	// 	SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture.get(), &clipRect, &dstrect);
	// } else {
	// 	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture.get(), &clipRect, &dstrect, associated.GetRotation(), NULL, SDL_FLIP_NONE);
	// }
}*/

// Inherited from Component
void Text::Update(float dt) { (void) dt; }

void Text::Render (void) {
	SDL_Rect clipRect = { 0, 0, (int) associated.box.w, (int) associated.box.h };
	SDL_Rect destRect;
	destRect.x = (int)(associated.box.x + Camera::pos.x);
	destRect.y = (int)(associated.box.y + Camera::pos.y);
	destRect.w = (int)(associated.box.w);
	destRect.h = (int)(associated.box.h);
	if (this->texture != nullptr) {
		if (-0.1f < associated.GetRotation() && associated.GetRotation() < 0.0f) {
			SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &destRect);
		} else {
			SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &destRect, associated.GetRotation(), NULL, SDL_FLIP_NONE);
		}
	}
}

bool Text::Is (const std::string & type) const {
	return type.compare("Text") == 0;
}

const std::string Text::GetType(void) const {
	return "Text";
}
