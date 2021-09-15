#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <SDL2/SDL_mixer.h>
#include "Component.h"

class GameObject;

class Sound : public Component {
private:
	//Mix_Music * music = nullptr;
	Mix_Chunk * chunk = nullptr;
	int channel = -1;

public:
	Sound (GameObject & associated);
	Sound (GameObject & associated, std::string file);
	~Sound(void);
	
	void Play (int times = 1);
	void Stop (void);
	void Open (const std::string & file);
	bool IsOpen (void);

	//	
	bool IsPlaying(void);

	// inherited from Component
	void Update(float dt);
	void Render(void);
	bool Is(const std::string & type);
};

#endif
