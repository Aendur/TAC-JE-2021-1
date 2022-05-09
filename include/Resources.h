#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <unordered_map>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>


typedef std::shared_ptr<SDL_Texture> SharedTexture;
typedef std::shared_ptr<Mix_Music>   SharedMusic;
typedef std::shared_ptr<Mix_Chunk>   SharedChunk;

class Resources {
private:
	typedef std::unordered_map<std::string, SharedTexture> ImageTable;
	typedef std::unordered_map<std::string, SharedMusic> MusicTable;
	typedef std::unordered_map<std::string, SharedChunk> SoundTable;

	inline static ImageTable imageTable = ImageTable();
	inline static MusicTable musicTable = MusicTable();
	inline static SoundTable soundTable = SoundTable();
	static void ClearImages(void);
	static void ClearMusics(void);
	static void ClearSounds(void);

public:
	static SharedTexture GetImage(const std::string & file);
	static SharedMusic GetMusic(const std::string & file);
	static SharedChunk GetSound(const std::string & file);
	static void CleanUpResources(void);
};

#endif
