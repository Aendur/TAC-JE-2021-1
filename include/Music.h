#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <SDL2/SDL_mixer.h>
#include "Resources.h"

class Music {
private:
	SharedMusic music;

public:
	Music(void);
	Music(const std::string & file);
	~Music(void);
	void Play (int times = -1);
	void Stop (int msToStop = 1500);
	void Open (const std::string & file);
	bool IsOpen (void);
};

#endif
