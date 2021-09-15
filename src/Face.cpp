#include "Face.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Sound.h"
#include <stdexcept>
#include <string>
#include <iostream>

Face::Face (GameObject& associated) : Component(associated) { }

void Face::Damage(int damage) {
	if (this->hitpoints <= 0) { return; }
	this->hitpoints -= damage;
	std::cout << "Object " << this << " damaged by " << damage << ". Remaining " << this->hitpoints << std::endl;
	
	if (this->hitpoints <= 0) {
		//std::string msg = std::string(__FILE__) + " missing play sound " + std::to_string(__LINE__);
		//throw std::logic_error(msg);
		
		std::cout << "object " << this << " destroyed" << std::endl;

		Sprite * sprite = (Sprite*) this->associated.GetComponent("Sprite");
		if (sprite != nullptr) {
			sprite->Reopen("assets/img/dedpeng.png");
		}
		
		Sound * sound = (Sound*) this->associated.GetComponent("Sound");
		if (sound != nullptr) {
			sound->Play(1);
		}
	}
}

void Face::Update (float dt) {
	(void) dt;
	if (this->hitpoints <= 0) {
		Sound * sound = (Sound *) this->associated.GetComponent("Sound");
		if (sound != nullptr && !sound->IsPlaying() ) {
			this->associated.RequestDelete();
		}
	}
}


void Face::Render (void) {}

bool Face::Is (const std::string & type) {
	return type.compare("Face") == 0;
}
