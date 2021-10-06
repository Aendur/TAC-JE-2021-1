#include "errors.h"
#include "Resources.h"
#include "Game.h"

/*
class Resources {
private:
	std::unordered_map<std::string, SDL_Texture*> imageTable;
	std::unordered_map<std::string, Mix_Music*> musicTable;
	std::unordered_map<std::string, Mix_Chunk*> soundTable;
};
*/

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable = std::unordered_map<std::string, SDL_Texture*>();
std::unordered_map<std::string, Mix_Music*> Resources::musicTable = std::unordered_map<std::string, Mix_Music*>();
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable = std::unordered_map<std::string, Mix_Chunk*>();

SDL_Texture* Resources::GetImage(const std::string & file) {
	if (imageTable.find(file) == imageTable.end()) {
		imageTable[file] = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str()); 
		if (imageTable[file] == nullptr) {
			std::string error = IMG_GetError();
			throw std::runtime_error(error);
		}
	}
	return imageTable[file];
}

Mix_Music* Resources::GetMusic(const std::string & file) {
	if (musicTable.find(file) == musicTable.end()) {
		musicTable[file] = Mix_LoadMUS(file.c_str());
		if (musicTable[file] == nullptr) {
			std::string error = Mix_GetError();
			throw std::runtime_error(error);
		}
	}
	return musicTable[file];
}

Mix_Chunk* Resources::GetSound(const std::string & file) {
	if (soundTable.find(file) == soundTable.end()) {
		soundTable[file] = Mix_LoadWAV(file.c_str());
		if (soundTable[file] == nullptr) {
			std::string error = Mix_GetError();
			throw std::runtime_error(error);
		}
	}
	return soundTable[file];
}

void Resources::ClearImages(void) {
	for (auto & pair : imageTable) {
		SDL_Texture * texture = pair.second;
		if (texture != nullptr) {
			SDL_DestroyTexture(texture);
		}
	}
	imageTable.clear();
}

void Resources::ClearMusics(void) {
	for (auto & pair : musicTable) {
		Mix_Music * music = pair.second;
		if (music != nullptr) {
			Mix_FreeMusic(music);
		}
	}
	musicTable.clear();
}

void Resources::ClearSounds(void) {
	for (auto & pair : soundTable) {
		Mix_Chunk * sound = pair.second;
		if (sound != nullptr) {
			Mix_FreeChunk(sound);
		}
	}
	soundTable.clear();
}
