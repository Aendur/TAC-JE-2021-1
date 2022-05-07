#include "Alien.h"
#include "Sprite.h"
#include "GameObject.h"
//#include "Sound.h"
#include "errors.h"
//#include <stdexcept>
//#include <string>
//#include <iostream>

Alien::Action::Action(ActionType type, float x, float y) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

Alien::Alien (GameObject& associated, int nMinions) : Component(associated) {
	#pragma message (MSG_INCOMPLETE_ERR)
	associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
}

Alien::~Alien (void) {
	minionArray.clear();
}

void Alien::Start (void) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
}

void Alien::Update (float dt) {
	#pragma message (MSG_INCOMPLETE_ERR)
}

void Alien::Render (void) { }

bool Alien::Is (const std::string & type) {
	return type.compare("Alien") == 0;
}
