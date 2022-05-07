#include "Minion.h"
#include "Sprite.h"
#include "GameObject.h"
//#include "InputManager.h"
//#include "Sound.h"
#include "errors.h"
//#include <stdexcept>
//#include <string>
#include <iostream>


Minion::Minion (GameObject& associated, std::weak_ptr<GameObject> alien, float arcOffsetDeg) : Component(associated), alienCenter(alien), arc(arcOffsetDeg) {
	associated.AddComponent(new Sprite(associated, "assets/img/Minion.png"));
}

// void Minion::Start (void) {
// 	#pragma message (MSG_INCOMPLETE_ERR)
// 	if (!started) {
// 		started = true;
// 	}
// }

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

bool Minion::Is (const std::string & type) {
	return type.compare("Minion") == 0;
}

void Minion::Shoot(const Vec2 & vec) {
	#pragma message (MSG_INCOMPLETE_ERR)
}
