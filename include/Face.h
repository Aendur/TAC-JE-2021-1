#ifndef FACE_H
#define FACE_H

#include <string>
#include <SDL2/SDL.h>

#include "Component.h"

class Face : public Component {
private:
	int hitpoints = 30;

public:
	// inherited from component
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type);

	//
	Face (GameObject& associated);
	void Damage(int damage);
};

#endif
