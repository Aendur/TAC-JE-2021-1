#include "PenguinCannon.h"
#include "GameObject.h"
#include "Sprite.h"
#include "PenguinBody.h"
#include "InputManager.h"
#include "errors.h"
#include <iostream>


PenguinCannon::PenguinCannon (GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated), pbody(penguinBody) {
	this->angle = 0.0f;
	associated.AddComponent(new Sprite(associated, "assets/img/cubngun.png"));
}

void PenguinCannon::Update (float dt) {
	#pragma message (MSG_INCOMPLETE_ERR)
	if (PenguinBody::player == nullptr) {
		associated.RequestDelete();
	} else {
		associated.SetCenterPosition(pbody.lock()->GetCenterPosition());

		// Get camera-independent mouse position
		InputManager & inputManager = InputManager::GetInstance();
		angle = (inputManager.GetMouseWorldPosition() - associated.GetCenterPosition()).deg();
		associated.SetRotation(angle);
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
	#pragma message (MSG_UNIMPLEMENTED_ERR)
}

