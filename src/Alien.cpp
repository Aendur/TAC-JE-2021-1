#include "Alien.h"
#include "Sprite.h"
#include "Game.h"
#include "StageState.h"
#include "Minion.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"
#include "errors.h"
#include <iostream>

Alien::Alien (GameObject& associated, int nMinions) : Component(associated), nMinions(nMinions) {
	speed = { 0, 0 };
	hitpoints = 100;
	associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
	associated.AddComponent(new Collider(associated, {COLLISION_ALIEN}, {0.30f, 0.30f}, {-10.0f, 0.0f}));

	state = RESTING;
	restTimer.Restart();
	destination = associated.GetCenterPosition();

	++alienCount;
}

Alien::~Alien (void) {
	minionArray.clear();
	--alienCount;
}

void Alien::Start (void) {
	StageState & gameState = Game::GetInstance().GetState();

	float arc = 360.0f / nMinions;
	for (int i = 0; i < nMinions; ++i) {
		GameObject * minion = new GameObject();
		minion->AddComponent(new Minion(*minion, gameState.GetObjectPtr(&this->associated), i * arc));
		
		Sprite * spr = (Sprite*) minion->GetComponent("Sprite");
		if (spr != nullptr) {
			float newscale = (float)(10000 + rand() % 5000) / 10000.0f;
			spr->SetScale(newscale, newscale);
		}

		auto ptr = gameState.AddObject(minion);
		this->minionArray.push_back(ptr);
	}
}

void Alien::Update (float dt) {
	if (hitpoints <= 0) {
		hitpoints = INT_MAX;
		//associated.RequestDelete();
		Sound * sfx = new Sound(associated, "assets/audio/boom.wav");
		sfx->Play(1);
		associated.AddComponent(sfx);
		associated.AddComponent(new Sprite(associated, "assets/img/aliendeath.png", 4, 0.15f, 0.6f));
	}

	static const float angularSpeed = 60.0f;
	static const float restCooldown = 1.0f;
	associated.SetRotation(associated.GetRotation() + angularSpeed * dt);


	if (PenguinBody::player == nullptr) return;

	switch(state) {
	case RESTING: {
		restTimer.Update(dt);
		if(restTimer.Get() > restCooldown) {
			destination = PenguinBody::player->GetAssociated().GetCenterPosition();
			state = MOVING;
		}
	} break;
	
	case MOVING: {
		bool arrived = MoveTo(destination, dt);
		if (arrived) {
			destination = PenguinBody::player->GetAssociated().GetCenterPosition();
			ShootAt(destination);
			restTimer.Restart();
			state = RESTING;
		}
	} break;
	
	default: break;
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

