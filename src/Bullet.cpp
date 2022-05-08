#include "Bullet.h"
#include "Sprite.h"
#include "GameObject.h"

#include "errors.h"
#include <iostream>


Bullet::Bullet (GameObject& associated, float angle, float spd, int dmg, float maxDistance, Sprite * sprite) : Component(associated) {
	associated.SetRotation(angle);
	this->speedAbs = spd;
	this->speed = Vec2(spd, 0.0f).RotateBy(angle);
	this->damage = dmg;
	this->distanceLeft = maxDistance;
	associated.AddComponent(sprite);
}

Bullet::~Bullet(void) {
	std::cout << "bullet deleted\n";
}

void Bullet::Update (float dt) {
	associated.SetCenterPosition(associated.GetCenterPosition() + speed * dt);

	float travelled = speedAbs * dt;
	distanceLeft -= travelled;
	if (distanceLeft <= travelled) { associated.RequestDelete(); }
}

void Bullet::Render (void) { }

bool Bullet::Is (const std::string & type) const {
	return type.compare("Bullet") == 0;
}

const std::string Bullet::GetType(void) const {
	return "Bullet";
}

int Bullet::GetDamage(void) const {
	return this->damage;
}
