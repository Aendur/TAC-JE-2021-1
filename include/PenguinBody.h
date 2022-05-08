#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H

#include <string>
#include <queue>
#include <SDL2/SDL.h>

#include "Component.h"
#include "Vec2.h"

class PenguinBody : public Component {
private:
	std::weak_ptr<GameObject> pcannon;
	Vec2 speed;
	float linearSpeed;
	float angle;
	int hitpoints;


public:
	//
	PenguinBody (GameObject& associated);
	~PenguinBody (void);
	inline static PenguinBody * player = nullptr;
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
