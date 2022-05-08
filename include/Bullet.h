#ifndef BULLET_H
#define BULLET_H

#include <string>
#include <SDL2/SDL.h>

#include "Component.h"
#include "Collider.h"
#include "Vec2.h"

class Sprite;
class Bullet : public Component {
private:

	Vec2 speed;
	float speedAbs;
	float distanceLeft;
	int damage;

public:
	//
	Bullet (GameObject& associated, float angle, float speed, int damage, float maxDistance, Sprite * sprite, const std::vector<CollisionClass>& cclass);
	~Bullet (void);

	// inherited from component
	//void Start (void);
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
	int GetDamage (void) const;

	void NotifyCollision(const GameObject & other) const;
};

#endif
