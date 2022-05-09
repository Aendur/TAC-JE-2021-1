#include "Music.h"
#include <stdexcept>

Music::Music(void) { }

Music::Music(const std::string & file) {
	this->Open(file);
}

Music::~Music(void) { }

void Music::Play (int times) { //= -1) {
	if (this->IsOpen()) {
		Mix_PlayMusic(this->music.get(), times);
	}
}

void Music::Stop (int msToStop) { // = 1500) {
	if (Mix_PlayingMusic()) {
		Mix_FadeOutMusic(msToStop);
	}
}

void Music::Open (const std::string & file) {
	this->music = Resources::GetMusic(file);
}

bool Music::IsOpen (void) {
	return this->music != nullptr;
}

