#include "Sound.h"
#include <stdexcept>

void Sound::Update(float dt) { (void) dt; }
void Sound::Render(void) { }

bool Sound::Is (const std::string & type) const {
	return type.compare("Sound") == 0;
}

const std::string Sound::GetType(void) const {
	return "Sound";
}

Sound::Sound (GameObject & associated) : Component(associated) {}

Sound::Sound (GameObject & associated, const std::string & file) : Sound(associated) {
	this->Open(file);
}

Sound::~Sound(void){ }

void Sound::Play (int times) {
	if (this->IsOpen()) {
		// int Mix_PlayChannel(int channel, Mix_Chunk* chunk, int loops)
		this->channel = Mix_PlayChannel(-1, this->chunk.get(), times-1);
	}
}

void Sound::Stop (void) {
	//int Mix_HaltChannel(int channel)
	if (this->IsOpen() && Mix_Playing(this->channel)) {
		Mix_HaltChannel(this->channel);
	}
}

void Sound::Open (const std::string & file) {
	this->chunk = Resources::GetSound(file);
}

bool Sound::IsOpen (void) {
	return this->chunk != nullptr;
}

bool Sound::IsPlaying(void) {
	return Mix_Playing(this->channel);
}