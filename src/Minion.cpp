#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"
#include "State.h"
#include "GameObject.h"
#include "errors.h"
#include <iostream>


Minion::Minion (GameObject& associated, std::weak_ptr<GameObject> alien, float arcOffsetDeg) : Component(associated), alienCenter(alien), arc(arcOffsetDeg) {
	associated.AddComponent(new Sprite(associated, "assets/img/Minion.png"));
}

Minion::~Minion(void) {
	std::cout << "minion deleted" << std::endl;
}

void Minion::Update (float dt) {
	static const Vec2 dist = { 200.0f, 0.0f };
	static const float angular_speed = -60.0f;
	auto ac = alienCenter.lock();

	if (ac.use_count() == 1) {
		associated.RequestDelete();
	} else {
		associated.SetCenterPosition(ac->GetCenterPosition() + dist.RotateBy(arc));
		associated.SetRotation(arc);
		arc += angular_speed * dt;
		while (arc < -360.0f) { arc += 360.0f; }
		while (arc >  360.0f) { arc -= 360.0f; }
	}


}

void Minion::Render (void) { }

bool Minion::Is (const std::string & type) const {
	return type.compare("Minion") == 0;
}

const std::string Minion::GetType(void) const {
	return "Minion";
}

void Minion::Shoot(const Vec2 & vec) {
	State & state = Game::GetInstance().GetState();
	Vec2 target = vec - associated.GetCenterPosition();

	GameObject * bullet = new GameObject();
	Sprite * bulletSprite = new Sprite(*bullet, "assets/img/minionbullet2.png", 3, 0.05f);
	bullet->AddComponent(new Bullet(*bullet, target.deg(), 500.0f, 20, 1000.0f, bulletSprite));
	bullet->SetCenterPosition(associated.GetCenterPosition());
	state.AddObject(bullet);
}
