#include "PenguinCannon.h"
#include "GameObject.h"
#include "Game.h"
#include "State.h"
#include "Sprite.h"
#include "PenguinBody.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Collider.h"
#include "errors.h"



PenguinCannon::PenguinCannon (GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated), pbody(penguinBody) {
	this->angle = 0.0f;
	associated.AddComponent(new Sprite(associated, "assets/img/cubngun.png"));
	associated.AddComponent(new Collider(associated, {COLLISION_PENGC}));
}

void PenguinCannon::Update (float dt) {
	(void) dt;
	if (PenguinBody::player == nullptr) {
		associated.RequestDelete();
	} else {
		associated.SetCenterPosition(pbody.lock()->GetCenterPosition());

		// Get camera-independent mouse position
		InputManager & inputManager = InputManager::GetInstance();
		Vec2 target = inputManager.GetMouseWorldPosition();
		Vec2 center = associated.GetCenterPosition();
		angle = (target - center).deg();
		associated.SetRotation(angle);

		if (inputManager.MousePress(MOUSE_LEFT)) {
			Shoot();
		}
	}
}

void PenguinCannon::Render (void) { }

bool PenguinCannon::Is (const std::string & type) const {
	return type.compare("PenguinCannon") == 0;
}

const std::string PenguinCannon::GetType(void) const {
	return "PenguinCannon";
}

void PenguinCannon::Shoot(void) {
	State & state = Game::GetInstance().GetState();

	Vec2 bulletCenter = associated.GetCenterPosition() + Vec2(associated.box.w / 2, 0.0f).RotateBy(angle);

	GameObject * bullet = new GameObject();
	Sprite * bulletSprite = new Sprite(*bullet, "assets/img/penguinbullet.png", 4, 0.25f);
	bullet->AddComponent(new Bullet(*bullet, angle, 400.0f, 20, 470.0f, bulletSprite, {COLLISION_ALIEN,COLLISION_MINION}));
	bullet->SetCenterPosition(bulletCenter);
	state.AddObject(bullet);
}

void PenguinCannon::NotifyCollision(const GameObject & other) {
	std::cout << GetType() << " collided with " << &other << std::endl;

	Bullet * bullet = (Bullet*)other.GetComponent("Bullet");
	if (bullet != nullptr) {
		std::cout << GetType() << " soaked " << bullet->GetDamage() << " damage.\n";
	}
}

