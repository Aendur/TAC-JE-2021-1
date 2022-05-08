#include "Alien.h"
#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "Minion.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Collider.h"
#include "Bullet.h"
#include "errors.h"
#include <iostream>

Alien::Alien (GameObject& associated, int nMinions) : Component(associated), nMinions(nMinions) {
	speed = { 0, 0 };
	hitpoints = 100;
	associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
	associated.AddComponent(new Collider(associated, {COLLISION_ALIEN}));
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
		
		Sprite * spr = (Sprite*) minion->GetComponent("Sprite");
		if (spr != nullptr) {
			float newscale = (float)(10000 + rand() % 5000) / 10000.0f;
			spr->SetScale(newscale, newscale);
		}

		auto ptr = state.AddObject(minion);
		this->minionArray.push_back(ptr);
	}
}

void Alien::Update (float dt) {
	if (hitpoints <= 0) { associated.RequestDelete(); }

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
	}
}

void Alien::Render (void) { }

bool Alien::Is (const std::string & type) const {
	return type.compare("Alien") == 0;
}

const std::string Alien::GetType(void) const {
	return "Alien";
}

void Alien::NotifyCollision(const GameObject & other) {
	std::cout << GetType() << " collided with " << &other << std::endl;
	
	Bullet * bullet = (Bullet*)other.GetComponent("Bullet");
	if (bullet != nullptr) {
		hitpoints -= bullet->GetDamage();
		std::cout << GetType() << " took " << bullet->GetDamage() << " damage. " << hitpoints << "  hitpoints remaining\n";
		if (hitpoints <= 0) {
			associated.RequestDelete();
		}
	}
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
		return false;
	}
}

bool Alien::ShootAt(const Vec2 & newpos) {
	//int N = rand() % minionArray.size();
	float min_dist = (newpos - minionArray[0].lock()->GetCenterPosition()).mag();
	int N = 0;

	for (int i = 1; i < minionArray.size(); ++i) {
		float d = (newpos - minionArray[i].lock()->GetCenterPosition()).mag();
		if (d < min_dist) {
			min_dist = d;
			N = i;
		}
	}
	std::cout << "alien minion " << N << " shoot at " << newpos << std::endl;

	Minion * minion = (Minion*) minionArray.at(N).lock()->GetComponent("Minion");
	if (minion != nullptr) { minion->Shoot(newpos); }

	return true;
}

