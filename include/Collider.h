#ifndef COLLIDER_H
#define COLLIDER_H

#include <string>
#include <unordered_map>
#include <set>
#include <SDL2/SDL.h>

#include "Component.h"
#include "Vec2.h"
#include "Rect.h"

class Collider;
enum CollisionClass {
	COLLISION_PENGB,
	COLLISION_PENGC,
	COLLISION_ALIEN,
	COLLISION_MINION,
};

typedef std::unordered_map<CollisionClass, std::set<const GameObject*>> GlobalColliderInfo;

class Collider : public Component {
private:
	static GlobalColliderInfo globalColliders;
	Vec2 scale;
	Vec2 offset;
	Vec2 center;
	float radius;
	std::vector<CollisionClass> collisionClass;

public:
	Collider (GameObject& associated, std::vector<CollisionClass> cclass, const Vec2 & scale = {1,1}, const Vec2 & offset = {0,0});
	~Collider (void);
	
	inline static const GlobalColliderInfo & GetGlobalColliders(void) { return globalColliders; }
	bool IsCollidingWith(const Collider & other) const;

	// inherited from component
	//void Start (void);
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;

	inline void SetScale(const Vec2 & value) { this->scale = value; }
	inline void SetOffset(const Vec2 & value) { this->offset = value; }

};

#endif
