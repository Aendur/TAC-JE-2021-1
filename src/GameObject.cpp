#include "GameObject.h"
#include "Component.h"
#include "errors.h"
#include <stdexcept>

GameObject::GameObject (void) {
	isDead = false;
	started = false;
}

void GameObject::Start(void) {
	#pragma message (MSG_UNIMPLEMENTED_ERR)
	throw std::logic_error(MSG_UNIMPLEMENTED_ERR);
}

GameObject::~GameObject (void) {
	for (Component * component : this->components) {
		delete(component);
	}
	this->components.clear();
}

void GameObject::Update(float dt) {
	for (Component * component : this->components) {
		component->Update(dt);
	}
}

void GameObject::Render(void) {
	for (Component * component : this->components) {
		component->Render();
	}
}

bool GameObject::IsDead(void) {
	return this->isDead;
}

void GameObject::RequestDelete(void) {
	this->isDead = true;
}

void GameObject::AddComponent(Component * cpt) {
	components.push_back(cpt);
}

void GameObject::RemoveComponent(Component * cpt) {
	for(size_t i = 0; i < this->components.size(); ++i) {
		if (this->components[i] == cpt) {
			delete this->components[i];
			this->components.erase(this->components.begin() + i);
		}
	}
}

Component * GameObject::GetComponent(const std::string & type) {
	for (Component * component : this->components) {
		if (component->Is(type)) {
			return component;
		}
	}
	return nullptr;
}
