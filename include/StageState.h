#ifndef STAGE_STATE_H
#define STAGE_STATE_H


#include "Music.h"
#include "State.h"
#include <memory>
#include <vector>

class GameObject;

class StageState : public State {
private:
	Music music;
	void HandleInput(void);
	void DetectCollisions(void);
	void EraseDeadObjects(void);
public:
	void LoadAssets (void);
	void Update (float);
	void Render (void);
	void Start(void);
	void Pause(void);
	void Resume(void);
};

#endif

