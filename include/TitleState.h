#ifndef TITLE_STATE_H
#define TITLE_STATE_H


#include "Music.h"
#include "State.h"
#include <memory>
#include <vector>

class TitleState : public State {
private:
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

