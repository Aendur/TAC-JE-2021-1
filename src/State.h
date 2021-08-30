#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"

class State {
private:
	Sprite bg;
	Music music;
	bool quitRequested = false;
public:
	State (void);
	bool QuitRequested (void);
	void LoadAssets (void);
	void Update (float);
	void Render (void);
};

#endif
