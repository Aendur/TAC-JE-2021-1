#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "Rect.h"
class Component;

class GameObject {
private:
	std::vector<Component*> components;
	bool isDead = false;

public:
	GameObject (void);
	~GameObject (void);
	void Update(float dt);
	void Render(void);
	bool IsDead(void);
	void RequestDelete(void);
	void AddComponent(Component * cpt);
	void RemoveComponent(Component * cpt);
	Component * GetComponent(const std::string & type);

	Rect box;
};

#endif
