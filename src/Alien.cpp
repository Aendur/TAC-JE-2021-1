#include "Alien.h"
#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "Minion.h"
#include "GameObject.h"
#include "InputManager.h"
#include "errors.h"
#include <iostream>

Alien::Alien (GameObject& associated, int nMinions) : Component(associated), nMinions(nMinions) {
	speed = { 0, 0 };
	hp = 100;
	associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
}

Alien::~Alien (void) {
	minionArray.clear();
}

void Alien::Start (void) {
	State & state = Game::GetInstance().GetState();

	float arc = 360.0f / nMinions;
	for (int i = 0; i < nMinions; ++i) {
		GameObject * minion = new GameObject();
		minion->AddComponent(new Minion(*minion, state.GetObjectPtr(&this->associated), i * arc));
		this->minionArray.push_back(state.AddObject(minion));
	}
}

void Alien::Update (float dt) {
	if (hp <= 0) { associated.RequestDelete(); }

	static const float angularSpeed = 60.0f;
	associated.SetRotation(associated.GetRotation() + angularSpeed * dt);

	// Get camera-independent mouse position
	InputManager & inputManager = InputManager::GetInstance();
	Vec2 newpos = inputManager.GetMouseWorldPosition();
	
	// Enqueue actions if applicable
	if (inputManager.MousePress(MOUSE_LEFT)) {
		taskQueue.push({Action::SHOOT, newpos.x, newpos.y});
	}
	if (inputManager.MousePress(MOUSE_RIGHT)) {
		taskQueue.push({Action::MOVE, newpos.x, newpos.y});
	}

	// Axecute actions, if any
	if (!taskQueue.empty()) {
		Action nextAction = taskQueue.front();
		bool complete = false;
		switch(nextAction.type) {
			case Action::MOVE:  complete = MoveTo(nextAction.pos, dt); break;
			case Action::SHOOT: complete = ShootAt(nextAction.pos); break;
			default: break;
		}
		if (complete) {
			taskQueue.pop();
		}
		//taskQueue.pop();
		//if (!complete) {
		//	taskQueue.push(nextAction);
		//}
	}
}

void Alien::Render (void) { }

bool Alien::Is (const std::string & type) {
	return type.compare("Alien") == 0;
}

bool Alien::MoveTo(const Vec2 & newpos, float dt) {
	static const float Vmax = 200.0f;
	Vec2 oldpos = associated.GetCenterPosition();
	Vec2 dif = (newpos - oldpos);
	if (dif < Vmax * dt) {
		associated.SetCenterPosition(newpos);
		speed = { 0, 0 };
		std::cout << "alien " << oldpos << " arrived at " << newpos << std::endl;
		return true;
	} else {
		speed = dif * (Vmax / dif.mag());
		associated.SetCenterPosition(oldpos + speed * dt);
		//std::cout << "alien " << oldpos << " is moving to " << newpos << " with speed " << speed << std::endl;
		return false;
	}
}

bool Alien::ShootAt(const Vec2 & newpos) {
	//Vec2 oldpos = associated.GetCenterPosition();
	//std::cout << "alien @ " << oldpos << " would SHOOT @ " << newpos << std::endl;
	Minion * minion = (Minion*) minionArray.at(0).lock()->GetComponent("Minion");
	if (minion != nullptr) { minion->Shoot(newpos); }
	return true;
}

