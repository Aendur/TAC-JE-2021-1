#include "Collider.h"
#include "GameObject.h"
#include "errors.h"
#include "Camera.h"

GlobalColliderInfo Collider::globalColliders = {
	{ COLLISION_PENGB , std::set<const GameObject*>() },
	{ COLLISION_PENGC , std::set<const GameObject*>() },
	{ COLLISION_ALIEN , std::set<const GameObject*>() },
	{ COLLISION_MINION, std::set<const GameObject*>() },
};

Collider::Collider (GameObject& associated, std::vector<CollisionClass> cclass, const Vec2 & colliderScale, const Vec2 & colliderOffset) : Component(associated) {
	collisionClass = cclass;
	scale = colliderScale;
	offset = colliderOffset;
	radius = (associated.box.w + associated.box.h) / 2.0f;

	for (CollisionClass cc : collisionClass) {
		globalColliders[cc].insert(&this->associated);
	}
}

Collider::~Collider (void) {
	for (CollisionClass cc : collisionClass) {
		globalColliders[cc].erase(&this->associated);
	}
}

void Collider::Update (float dt) { (void) dt; }

#include "Utility.h"

void Collider::Render (void) {
	Utility::DrawCircumference(associated.GetCenterPosition() - Camera::pos, radius, {255, 0, 0});
}

bool Collider::Is (const std::string & type) const {
	return type.compare("Collider") == 0;
}

const std::string Collider::GetType(void) const {
	return "Collider";
}

bool Collider::IsCollidingWith(const Collider & other) const {
	Vec2 c1 = this->associated.GetCenterPosition();
	Vec2 c2 = other.associated.GetCenterPosition();
	return ((c2 - c1).mag() <= (this->radius + other.radius));
}


