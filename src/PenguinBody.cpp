#include "PenguinBody.h"
#include "GameObject.h"
#include "Sprite.h"
// #include "Game.h"
// #include "State.h"
// #include "Minion.h"
// #include "InputManager.h"
#include "errors.h"
#include <iostream>

/*
class PenguinBody : public Component {
private:
	std::weak_ptr<GameObject> pcannon;
};
*/

PenguinBody::PenguinBody (GameObject& associated) : Component(associated) {
	this->speed = { 0, 0 };
	this->linearSpeed = 0.0f;
	this->angle = 0.0f;
	this->hp = 100;
	this->player = nullptr;
	associated.AddComponent(new Sprite(associated, "assets/img/penguin.png"));
}

PenguinBody::~PenguinBody (void) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
	// minionArray.clear();
}

void PenguinBody::Start (void) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
	//
	// State & state = Game::GetInstance().GetState();

	// float arc = 360.0f / nMinions;
	// for (int i = 0; i < nMinions; ++i) {
	// 	GameObject * minion = new GameObject();
	// 	minion->AddComponent(new Minion(*minion, state.GetObjectPtr(&this->associated), i * arc));
		
	// 	Sprite * spr = (Sprite*) minion->GetComponent("Sprite");
	// 	if (spr != nullptr) {
	// 		float newscale = (float)(10000 + rand() % 5000) / 10000.0f;
	// 		spr->SetScale(newscale, newscale);
	// 	}

	// 	auto ptr = state.AddObject(minion);
	// 	this->minionArray.push_back(ptr);
	// }
}

void PenguinBody::Update (float dt) {
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

void PenguinBody::Render (void) { }

bool PenguinBody::Is (const std::string & type) const {
	return type.compare("PenguinBody") == 0;
}

const std::string PenguinBody::GetType(void) const {
	return "PenguinBody";
}

