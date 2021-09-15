#include "Sound.h"
#include <stdexcept>

void Sound::Update(float dt) { (void) dt; }
void Sound::Render(void) { }

bool Sound::Is(const std::string & type) {
	return (type.compare("Sound") == 0);
}


Sound::Sound (GameObject & associated) : Component(associated) {}

Sound::Sound (GameObject & associated, std::string file) : Sound(associated) {
	this->Open(file);
}

Sound::~Sound(void){
	if (this->IsOpen()) {
		Mix_FreeChunk(this->chunk);
		this->chunk = nullptr;
	}
}

void Sound::Play (int times) {
	if (this->IsOpen()) {
		// int Mix_PlayChannel(int channel, Mix_Chunk* chunk, int loops)
		this->channel = Mix_PlayChannel(-1, chunk, times-1);
	}
}

void Sound::Stop (void) {
	//int Mix_HaltChannel(int channel)
	if (this->IsOpen() && Mix_Playing(this->channel)) {
		Mix_HaltChannel(this->channel);
	}
}

void Sound::Open (const std::string & file) {
	if (this->IsOpen()) {
		Mix_FreeChunk(this->chunk);
		this->chunk = nullptr;
	}

	this->chunk = Mix_LoadWAV(file.c_str());
	if (this->chunk == nullptr) {
		std::string error = Mix_GetError();
		throw std::runtime_error(error);
	}
}

bool Sound::IsOpen (void) {
	return this->chunk != nullptr;
}

bool Sound::IsPlaying(void) {
	return Mix_Playing(this->channel);
}