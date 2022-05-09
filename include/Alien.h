#ifndef ALIEN_H
#define ALIEN_H

#include <string>
#include <queue>
#include <SDL2/SDL.h>

#include "Component.h"
#include "Timer.h"
#include "Vec2.h"

class Alien : public Component {
private:
	enum AlienState { MOVING, RESTING };
	AlienState state;
	Timer restTimer;
	Vec2 destination;

	Vec2 speed;
	int hitpoints;
	int nMinions;
	float maxRest;
	std::vector<std::weak_ptr<GameObject>> minionArray;

	bool MoveTo(const Vec2 & newpos, float dt);
	bool ShootAt(const Vec2 & newpos);

public:
	inline static int alienCount = 0;


	Alien (GameObject& associated, int nMinions, float maxRest);
	~Alien (void);
	inline int GetHitPoints(void) const { return hitpoints; }

	// inherited from component
	void Start (void);
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
	void NotifyCollision(const GameObject & other);
};

#endif
