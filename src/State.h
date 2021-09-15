#ifndef STATE_H
#define STATE_H


#include "Music.h"
#include <memory>
#include <vector>

class GameObject;

class State {
private:
	Music music;
	bool quitRequested = false;
	std::vector<std::unique_ptr<GameObject>> objectArray;

	void Input(void);
	void AddObject(int mouseX, int mouseY);
public:
	State (void);
	~State(void);
	bool QuitRequested (void);
	void LoadAssets (void);
	void Update (float);
	void Render (void);
};

#endif
