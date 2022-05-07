#include "Alien.h"
#include "Sprite.h"
#include "GameObject.h"
#include "InputManager.h"
//#include "Sound.h"
#include "errors.h"
//#include <stdexcept>
//#include <string>
#include <iostream>

Alien::Alien (GameObject& associated, int nMinions) : Component(associated) {
	speed = { 0, 0 };
	hp = 100;
	associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
}

Alien::~Alien (void) {
	minionArray.clear();
}

void Alien::Start (void) {
	#pragma message (MSG_INCOMPLETE_ERR)
}

void Alien::Update (float dt) {
	InputManager & inputManager = InputManager::GetInstance();

	associated.SetRotation(associated.GetRotation() + 6);

	// Get camera-independent mouse position
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
		speed = dif * (Vmax / dif.abs());
		associated.SetCenterPosition(oldpos + speed * dt);
		//std::cout << "alien " << oldpos << " is moving to " << newpos << " with speed " << speed << std::endl;
		return false;
	}
}

bool Alien::ShootAt(const Vec2 & newpos) {
	Vec2 oldpos = associated.GetCenterPosition();
	std::cout << "alien @ " << oldpos << " would SHOOT @ " << newpos << std::endl;
	return true;
}

