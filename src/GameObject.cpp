#include "GameObject.h"
#include "Component.h"
#include "errors.h"
#include <stdexcept>

GameObject::GameObject (void) {
	isDead = false;
	started = false;
	angleDeg = 0.0f;
}

GameObject::~GameObject (void) {
	for (Component * component : this->components) {
		delete(component);
	}
	this->components.clear();
}

void GameObject::Start(void) {
	if (!started) {
		for (Component * comp : components) {
			comp->Start();
		}
		started = true;
	}
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
	if (started) { cpt->Start(); }
}

void GameObject::RemoveComponent(Component * cpt) {
	for(size_t i = 0; i < this->components.size(); ++i) {
		if (this->components[i] == cpt) {
			delete this->components[i];
			this->components.erase(this->components.begin() + i);
		}
	}
}

Component * GameObject::GetComponent(const std::string & type) const {
	for (Component * component : this->components) {
		if (component->Is(type)) {
			return component;
		}
	}
	return nullptr;
}

Vec2 GameObject::GetPosition(void) const {
	return Vec2(box.x, box.y);
}

Vec2 GameObject::GetCenterPosition(void) const {
	return Vec2(box.x + box.w/2, box.y + box.h/2);
}

void GameObject::SetPosition(const Vec2 & pos) {
	box.x = pos.x;
	box.y = pos.y;
}

void GameObject::SetCenterPosition(const Vec2 & pos) {
	box.x = pos.x - box.w/2;
	box.y = pos.y - box.h/2;
}

float GameObject::GetRotation(void) {
	return angleDeg;
}

void GameObject::SetRotation(float angle) {
	while (angle > 360.0f) { angle -= 360.0f; }
	while (angle < 360.0f) { angle += 360.0f; }
	angleDeg = angle;
}

void GameObject::NotifyCollision(const GameObject & other) const {
	std::cout << this << " collided with " << (&other) << std::endl;
	for (Component * component : components) {
		std::cout << "notifying component: " << component->GetType() << std::endl;
		component->NotifyCollision(other);
	}
}
