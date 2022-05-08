#ifndef MINION_H
#define MINION_H

#include <string>
#include <SDL2/SDL.h>

#include "Component.h"
#include "Vec2.h"

class Minion : public Component {
private:
	std::weak_ptr<GameObject> alienCenter;
	float arc;

public:
	//
	Minion (GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
	~Minion (void);

	// inherited from component
	//void Start (void);
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;

	void Shoot(const Vec2 & target);
	void NotifyCollision(const GameObject & other);
};

#endif
