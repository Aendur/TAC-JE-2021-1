#include "PenguinBody.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "PenguinCannon.h"
#include "InputManager.h"
#include "Collider.h"
#include "errors.h"



PenguinBody::PenguinBody (GameObject& associated) : Component(associated) {
	this->speed = { 0, 0 };
	this->linearSpeed = 0.0f;
	this->angle = 0.0f;
	this->hp = 100;
	PenguinBody::player = this;
	associated.AddComponent(new Sprite(associated, "assets/img/penguin.png"));
	associated.AddComponent(new Collider(associated, {COLLISION_PENGB}));
}

PenguinBody::~PenguinBody (void) {
	PenguinBody::player = nullptr;
}

void PenguinBody::Start (void) {
	State & state = Game::GetInstance().GetState();
	GameObject * cannon = new GameObject();
	cannon->AddComponent(new PenguinCannon(*cannon, state.GetObjectPtr(&this->associated)));
	pcannon = state.AddObject(cannon);
}

void PenguinBody::Update (float dt) {
	#pragma message (MSG_INCOMPLETE_ERR)
	if (hp <= 0) {
		associated.RequestDelete();
		//pcannon.lock()->RequestDelete();
	}

	InputManager & inputManager = InputManager::GetInstance();
	static const float angularSpeed = 270.0f;
	static const float acceleration = 350.3f;
	static const float frictionFact =  0.50f;

	if      (inputManager.IsKeyDown(KEY_W)) { linearSpeed += acceleration * dt; }
	else if (inputManager.IsKeyDown(KEY_S)) { linearSpeed -= acceleration * dt; }
	linearSpeed -= linearSpeed * frictionFact * dt;

	//std::cout << linearSpeed << std::endl;
	
	if (inputManager.IsKeyDown(KEY_A)) { angle -= angularSpeed * dt; }
	if (inputManager.IsKeyDown(KEY_D)) { angle += angularSpeed * dt; }

	speed = Vec2(linearSpeed, 0.0f).RotateBy(angle);

	Vec2 currentPosition = associated.GetCenterPosition();
	associated.SetCenterPosition(currentPosition + dt * speed );
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

