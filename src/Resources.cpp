#include "errors.h"
#include "Resources.h"

/*
class Resources {
private:
	std::unordered_map<std::string, SDL_Texture*> imageTable;
	std::unordered_map<std::string, Mix_Music*> musicTable;
	std::unordered_map<std::string, Mix_Chunk*> soundTable;
};
*/

SDL_Texture* Resources::GetImage(const std::string & file) {
	(void) file;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

Mix_Music* Resources::GetMusic(const std::string & file) {
	(void) file;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

Mix_Chunk* Resources::GetSound(const std::string & file) {
	(void) file;
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

void Resources::ClearImages(void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

void Resources::ClearMusics(void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

void Resources::ClearSounds(void) {
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}
