#ifndef END_STATE_H
#define END_STATE_H

#include "State.h"
#include "Music.h"
#include <memory>
#include <vector>

class EndState : public State {
private:
	Music bgm;
	void HandleInput(void);
public:
	void LoadAssets (void);
	void Update (float);
	void Render (void);

	void Start(void);
	void Pause(void);
	void Resume(void);
};

#endif

