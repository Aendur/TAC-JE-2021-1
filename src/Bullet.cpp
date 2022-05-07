#include "Bullet.h"
#include "Sprite.h"
#include "GameObject.h"

#include "errors.h"
#include <iostream>

// class Bullet : public Component {
// private:

// 	Vec2 speed;
// 	float distanceLeft;
// 	int damage;

// public:
// 	//
// 	Bullet (GameObject& associated, float angle, float speed, int damage, float maxDistance, const std::string & sprite);
// 	~Bullet (void);

// 	// inherited from component
// 	//void Start (void);
// 	void Update (float dt);
// 	void Render (void);
// 	bool Is (const std::string & type);
// 	int GetDamage (void) const;
// };


Bullet::Bullet (GameObject& associated, float angle, float spd, int dmg, float maxDistance, const std::string & sprite) : Component(associated) {
	associated.SetRotation(angle);
	this->speedAbs = spd;
	this->speed = Vec2(spd, 0.0f).RotateBy(angle);
	this->damage = dmg;
	this->distanceLeft = maxDistance;
	associated.AddComponent(new Sprite(associated, sprite));
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
