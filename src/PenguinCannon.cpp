#include "PenguinCannon.h"
#include "GameObject.h"
#include "Sprite.h"
// #include "Game.h"
// #include "State.h"
// #include "Minion.h"
// #include "InputManager.h"
#include "errors.h"
#include <iostream>


PenguinCannon::PenguinCannon (GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated), pbody(penguinBody) {
	this->angle = 0.0f;
	associated.AddComponent(new Sprite(associated, "assets/img/cubngun.png"));
}

void PenguinCannon::Update (float dt) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
	// if (hp <= 0) { associated.RequestDelete(); }

	// static const float angularSpeed = 60.0f;
	// associated.SetRotation(associated.GetRotation() + angularSpeed * dt);

	// // Get camera-independent mouse position
	// InputManager & inputManager = InputManager::GetInstance();
	// Vec2 newpos = inputManager.GetMouseWorldPosition();
	
	// // Enqueue actions if applicable
	// if (inputManager.MousePress(MOUSE_LEFT)) {
	// 	taskQueue.push({Action::SHOOT, newpos.x, newpos.y});
	// }
	// if (inputManager.MousePress(MOUSE_RIGHT)) {
	// 	taskQueue.push({Action::MOVE, newpos.x, newpos.y});
	// }

	// // Axecute actions, if any
	// if (!taskQueue.empty()) {
	// 	Action nextAction = taskQueue.front();
	// 	bool complete = false;
	// 	switch(nextAction.type) {
	// 		case Action::MOVE:  complete = MoveTo(nextAction.pos, dt); break;
	// 		case Action::SHOOT: complete = ShootAt(nextAction.pos); break;
	// 		default: break;
	// 	}
	// 	if (complete) {
	// 		taskQueue.pop();
	// 	}
	// }
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

