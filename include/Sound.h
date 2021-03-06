#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <SDL2/SDL_mixer.h>
#include "Component.h"
#include "Resources.h"

class GameObject;

class Sound : public Component {
private:
	SharedChunk chunk;
	int channel = -1;

public:
	Sound (GameObject & associated);
	Sound (GameObject & associated, const std::string & file);
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
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
};

#endif
