#include "errors.h"
#include "Resources.h"
#include "Game.h"
#include <iostream>


SharedTexture Resources::GetImage(const std::string & file) {
	if (!imageTable.contains(file)) {
		SDL_Texture * texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str()); ;
		if (texture == nullptr) {
			std::string error = IMG_GetError();
			throw std::runtime_error(error);
		}

		imageTable[file] = SharedTexture(texture, [file](SDL_Texture * tgt) {
			if (tgt != nullptr) {
				SDL_DestroyTexture(tgt);
				std::cout << "released texture " << file << "\n";
			}
		});
		
		std::cout << "loaded image: " << file << " as a resource\n";
	}
	return imageTable[file];
}

SharedMusic Resources::GetMusic(const std::string & file) {
	if (!musicTable.contains(file)) {
		Mix_Music * music =  Mix_LoadMUS(file.c_str());
		if (music == nullptr) {
			std::string error = Mix_GetError();
			throw std::runtime_error(error);
		}
	
		musicTable[file] = SharedMusic(music, [file](Mix_Music * tgt) {
			if (tgt != nullptr) {
				Mix_FreeMusic(tgt);
				std::cout << "released music " << file << "\n";
			}
		});

		std::cout << "loaded music: " << file << " as a resource\n";
	}
	return musicTable[file];
}

SharedChunk Resources::GetSound(const std::string & file) {
	if (!soundTable.contains(file)) {
		Mix_Chunk * chunk = Mix_LoadWAV(file.c_str());
		if (chunk == nullptr) {
			std::string error = Mix_GetError();
			throw std::runtime_error(error);
		}

		soundTable[file] = SharedChunk(chunk, [file](Mix_Chunk * tgt) {
			if (tgt != nullptr) {
				Mix_FreeChunk(tgt);
				std::cout << "released chunk " << file << "\n";
			}
		});

		std::cout << "loaded chunk: " << file << " as a resource\n";
	}
	return soundTable[file];
}

SharedFont Resources::GetFont(const std::string & fontfile, int fontsize) {
	std::string key = fontfile + ',' + std::to_string(fontsize);
	if (!fontTable.contains(key)) {
		TTF_Font * font = TTF_OpenFont(fontfile.c_str(), fontsize);
		if (font == nullptr) {
			std::string error = TTF_GetError();
			throw std::runtime_error(error);
		}

		fontTable[key] = SharedFont(font, [key](TTF_Font * tgt) {
			if (tgt != nullptr) {
				TTF_CloseFont(tgt);
				std::cout << "released font " << key << "\n";
			}
		});

		std::cout << "loaded font: " << key << " as a resource\n";
	}
	return fontTable[key];
}

template<class T>
void Resources::ClearTable(std::unordered_map<std::string, T> & table) {
	for (auto & [k,v] : table) {
		if (v.use_count() == 1) { table.erase(k); }
	}
}

void Resources::CleanUpResources(void) {
	std::cout << "clean up image resources" << std::endl;
	ClearTable<SharedTexture>(imageTable);
	std::cout << "clean up music resources" << std::endl;
	ClearTable<SharedMusic>(musicTable);
	std::cout << "clean up sound resources" << std::endl;
	ClearTable<SharedChunk>(soundTable);
	std::cout << "clean up font resources" << std::endl;
	ClearTable<SharedFont>(fontTable);
}