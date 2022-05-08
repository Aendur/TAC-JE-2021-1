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
	associated.AddComponent(new Collider(associated, {COLLISION_PENGC}, {0.325f, 0.325f}, {-30.0f, 0.0f}));
	cooldown.Restart();
}

void PenguinCannon::Update (float dt) {
	(void) dt;
	cooldown.Update(dt);

	if (PenguinBody::player == nullptr) {
		//associated.RequestDelete();
		if (!playerDead) {
			associated.AddComponent(new Sprite(associated, "assets/img/penguindeath.png", 5, 0.2f, 1.0f));
			playerDead = true;
		}
	} else {
		cooldown.Update(dt);
		associated.SetCenterPosition(pbody.lock()->GetCenterPosition());

		// Get camera-independent mouse position
		InputManager & inputManager = InputManager::GetInstance();
		Vec2 target = inputManager.GetMouseWorldPosition();
		Vec2 center = associated.GetCenterPosition();
		angle = (target - center).deg();
		associated.SetRotation(angle);

		if (inputManager.MousePress(MOUSE_LEFT) && cooldown.Get() > 1.0f) {
			Shoot();
			cooldown.Restart();
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
	Collider * bulletCollider = new Collider(*bullet,  {COLLISION_ALIEN,COLLISION_MINION}, {0.45f,0.45f}, {10.0f,0.0f});
	bullet->AddComponent(new Bullet(*bullet, angle, 400.0f, 20, 470.0f, bulletSprite, bulletCollider));
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

