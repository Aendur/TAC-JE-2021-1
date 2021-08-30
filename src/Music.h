#ifndef MUSIC_H
#define MUSIC_H

#include <SDL/SDL2_mixer-2.0.4/include/SDL_mixer.h>

class Music {
private:
	Mix_Music * music = nullptr;

public:
	Music(void);
	Music(std::string file);
	~Music(void);
	void Play (int times = -1);
	void Stop (int msToStop = 1500);
	void Open (std::string file);
	bool IsOpen (void);
};

#endif
