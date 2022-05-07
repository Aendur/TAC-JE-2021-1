#include "Alien.h"
//#include "Sprite.h"
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
Alien::Alien (GameObject& associated) : Component(associated) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}
Alien::~Alien (void) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
}
void Alien::Start (void) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}
void Alien::Update (float dt) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}
void Alien::Render (void) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}
bool Alien::Is (const std::string & type) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}
