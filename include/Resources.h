#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

class Resources {
private:
	static std::unordered_map<std::string, SDL_Texture*> imageTable;
	static std::unordered_map<std::string, Mix_Music*> musicTable;
	static std::unordered_map<std::string, Mix_Chunk*> soundTable;

public:
	static SDL_Texture* GetImage(const std::string & file);
	static Mix_Music* GetMusic(const std::string & file);
	static Mix_Chunk* GetSound(const std::string & file);
	static void ClearImages(void);
	static void ClearMusics(void);
	static void ClearSounds(void);
};

#endif
