#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Resources {
private:
	std::unordered_map<std::string, SDL_Texture*> imageTable;
	std::unordered_map<std::string, Mix_Music*> musicTable;
	std::unordered_map<std::string, Mix_Chunk*> soundTable;

public:
	SDL_Texture* GetImage(const std::string & file);
	Mix_Music* GetMusic(const std::string & file);
	Mix_Chunk* GetSound(const std::string & file);
	void ClearImages(void);
	void ClearMusics(void);
	void ClearSounds(void);
};

#endif
