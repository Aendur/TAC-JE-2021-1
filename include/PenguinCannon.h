#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H

#include <string>
#include <queue>
#include <SDL2/SDL.h>

#include "Component.h"
#include "Vec2.h"

class PenguinCannon : public Component {
private:
	std::weak_ptr<GameObject> pbody;
	float angle;
	
public:
	//
	PenguinCannon (GameObject& associated, std::weak_ptr<GameObject> penguinBody);
	//~PenguinCannon (void);

	// inherited from component
	//void Start (void);
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;

	//void Shoot(const Vec2 & target);
	void Shoot(void);
};

#endif
