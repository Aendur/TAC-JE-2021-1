#include "Music.h"
#include <stdexcept>

Music::Music(void) { }

Music::Music(const std::string & file) {
	this->Open(file);
}

Music::~Music(void) {
	if (this->IsOpen()) {
		Mix_FreeMusic(this->music);
		this->music = nullptr;
	}
}

void Music::Play (int times) { //= -1) {
	if (this->IsOpen()) {
		Mix_PlayMusic(this->music, times);
	}
}

void Music::Stop (int msToStop) { // = 1500) {
	if (Mix_PlayingMusic()) {
		Mix_FadeOutMusic(msToStop);
	}
}

void Music::Open (const std::string & file) {
	if (this->IsOpen()) {
		Mix_FreeMusic(this->music);
		this->music = nullptr;
	}

	this->music = Mix_LoadMUS(file.c_str());
	if (this->music == nullptr) {
		std::string error = Mix_GetError();
		throw std::runtime_error(error);
	}
}

bool Music::IsOpen (void) {
	return this->music != nullptr;
}

