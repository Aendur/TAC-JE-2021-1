#include "Collider.h"
#include "GameObject.h"
#include "errors.h"

Collider::Collider (GameObject& associated, std::vector<CollisionClass> cclass, const Vec2 & colliderScale, const Vec2 & colliderOffset) : Component(associated) {
	#pragma message (MSG_INCOMPLETE_ERR)
	#pragma message ("missing add to global colliders")
	collisionClass = cclass;
	scale = colliderScale;
	offset = colliderOffset;
	radius = (associated.box.w + associated.box.h) / 2.0f;
}

Collider::~Collider (void) {
	#pragma message (MSG_INCOMPLETE_ERR)
	#pragma message ("missing remove from global colliders")
}

void Collider::Update (float dt) { (void) dt; }

void Collider::Render (void) { }

bool Collider::Is (const std::string & type) const {
	return type.compare("Collider") == 0;
}

const std::string Collider::GetType(void) const {
	return "Collider";
}
