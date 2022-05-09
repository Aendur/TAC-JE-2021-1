#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <unordered_map>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef std::shared_ptr<SDL_Texture> SharedTexture;
typedef std::shared_ptr<Mix_Music>   SharedMusic;
typedef std::shared_ptr<Mix_Chunk>   SharedChunk;
typedef std::shared_ptr<TTF_Font>    SharedFont;

class Resources {
private:
	typedef std::unordered_map<std::string, SharedTexture> ImageTable;
	typedef std::unordered_map<std::string, SharedMusic>   MusicTable;
	typedef std::unordered_map<std::string, SharedChunk>   SoundTable;
	typedef std::unordered_map<std::string, SharedFont>    FontTable;

	inline static ImageTable imageTable = ImageTable();
	inline static MusicTable musicTable = MusicTable();
	inline static SoundTable soundTable = SoundTable();
	inline static FontTable  fontTable  = FontTable();

	template<class T>
	static void ClearTable(std::unordered_map<std::string, T> & table);

public:
	static SharedTexture GetImage(const std::string & file);
	static SharedMusic GetMusic(const std::string & file);
	static SharedChunk GetSound(const std::string & file);
	static SharedFont GetFont(const std::string & fontfile, int fontsize);
	static void CleanUpResources(void);
};

#endif
