#include "PenguinBody.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "PenguinCannon.h"
#include "InputManager.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"
#include "errors.h"



PenguinBody::PenguinBody (GameObject& associated) : Component(associated) {
	this->speed = { 0, 0 };
	this->linearSpeed = 0.0f;
	this->angle = 0.0f;
	this->hitpoints = 100;
	PenguinBody::player = this;
	associated.AddComponent(new Sprite(associated, "assets/img/penguin.png"));
	associated.AddComponent(new Collider(associated, {COLLISION_PENGB}, {0.4f, 0.4f}, {0.0f, 0.0f}));
}

PenguinBody::~PenguinBody (void) {
	PenguinBody::player = nullptr;
}

void PenguinBody::Start (void) {
	State & state = Game::GetInstance().GetCurrentState();
	GameObject * cannon = new GameObject();
	cannon->AddComponent(new PenguinCannon(*cannon, state.GetObjectPtr(&this->associated)));
	pcannon = state.AddObject(cannon);
}

void PenguinBody::Update (float dt) {
	if (hitpoints <= 0) {
		hitpoints = INT_MAX;
		Sound * sfx = new Sound(associated, "assets/audio/boom.wav");
		sfx->Play(1);
		associated.AddComponent(sfx);
		associated.AddComponent(new Sprite(associated, "assets/img/penguindeath.png", 5, 0.2f, 1.0f));
	}

	InputManager & inputManager = InputManager::GetInstance();
	static const float angularSpeed = 270.0f;
	static const float acceleration = 350.3f;
	static const float frictionFact =  0.50f;

	if      (inputManager.IsKeyDown(KEY_W)) { linearSpeed += acceleration * dt; }
	else if (inputManager.IsKeyDown(KEY_S)) { linearSpeed -= acceleration * dt; }
	linearSpeed -= linearSpeed * frictionFact * dt;

	if (inputManager.IsKeyDown(KEY_A)) { angle -= angularSpeed * dt; }
	if (inputManager.IsKeyDown(KEY_D)) { angle += angularSpeed * dt; }

	Vec2 currentPosition = associated.GetCenterPosition();

	Vec2 correctedPosition = currentPosition;
	if      (currentPosition.x < 50.0f)   { correctedPosition.x =   60.0f; angle = 180.0f - angle; }
	else if (currentPosition.x > 1358.0f) {	correctedPosition.x = 1348.0f; angle = 180.0f - angle; }
	if      (currentPosition.y < 50.0f)   { correctedPosition.y =   60.0f; angle = -angle; }
	else if (currentPosition.y > 1230.0f) { correctedPosition.y = 1220.0f; angle = -angle; }

	speed = Vec2(linearSpeed, 0.0f).RotateBy(angle);
	associated.SetCenterPosition(correctedPosition + dt * speed );
	associated.SetRotation(angle);

	//std::cout << (--hp) << std::endl;
}

void PenguinBody::Render (void) { }

bool PenguinBody::Is (const std::string & type) const {
	return type.compare("PenguinBody") == 0;
}

const std::string PenguinBody::GetType(void) const {
	return "PenguinBody";
}

void PenguinBody::NotifyCollision(const GameObject & other) {
	std::cout << GetType() << " collided with " << &other << std::endl;
	
	Bullet * bullet = (Bullet*)other.GetComponent("Bullet");
	if (bullet != nullptr) {
		hitpoints -= bullet->GetDamage();
		std::cout << GetType() << " took " << bullet->GetDamage() << " damage. " << hitpoints << "  hitpoints remaining\n";
	}
}

